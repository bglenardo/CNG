##########################################################################################
#
#  read_g4ndl.py
#
#  This function is intended to translate Luiz deViveiros' MATLAB GEANT4 nuclear data
#  reader into Python for use in calculations.
#
#  2015-09-03 - Created. (Brian L.)
#
##########################################################################################

import numpy as np
from numpy import matlib as mat
import scipy as sp
import os

def read_g4ndl( G4NDL_path, element, isotope, E_neutron_eV, cos_theta_list):

  # Luiz assumes that the ENDF angular data is given in 
  # Legendre Polynomials Coefficients (P1,P2,..), I guess we'll do the same.

  # Check inputs
  CrossSection_b = np.zeros(1)
  AngDist_Prob_over_Cos = np.zeros(1)

  E_neutron_eV = np.array(E_neutron_eV)

  print('\n')
 
  if 'cos_theta_list' in locals(): # and not not cos_theta_list:
    flag_return_ang_dist = True
    if len(E_neutron_eV) != 1:
      print('cost_theta_list entered => E_neutron_eV must be a single value variable;')
      print('we can\' compute the angular distribution for many neutron energies.')
      return
  
  else:
    flag_return_ang_dist = False
   
  if not ('E_neutron_eV' in locals()) or not E_neutron_eV:
    print('Please specify E_neutron_eV or E_neutron_eV_list.')
    return

  if not os.path.isdir(G4NDL_path):
    print('ERROR: Data path does not exist, please specify another:')
    print('{} not found!'.format(G4NDL_path))

  CS_path = '%s/Elastic/CrossSection/' % G4NDL_path 
  FS_path = '%s/Elastic/FS/' % G4NDL_path

  if not os.path.isdir(FS_path):
    print('Warning: Angular distribution data does not exist.')
    print('{} not found!!'.format(FS_path))
    print('We will only load cross section data.')
    flag_return_ang_dist = False

  if not ('element' in locals()) or not element:
    print('Specify an element to read; i.e. element=\'Xe\';')
    
  if not ('isotope' in locals()) or not isotope:
    print('Specify an isotope to read; i.e. isotope=130;')

  # Figure out the element data
  AA = AtomicNumber(element)

  ###################################
  # Reads the Cross Section file
  if True:

    directory = '%s/Elastic/CrossSection/' % (G4NDL_path)
    filename_prefix = '%d_%d_' % (AA,isotope)
    files = os.listdir(directory)
    filename = ''
    for file in files:
      if file.startswith(filename_prefix):
        filename = directory+file
    if not filename:
      print('ERROR: Could not find the file for the specified element and isotope:')
      print('{}* NOT FOUND'.format(filename))
      return

    # Load the data from the G4NDL file into data_matrix
    print('Reading {}'.format(filename))
    # Skip first 3 lines, and append any trailing lines.
    data = np.genfromtxt(filename,skip_header=3,skip_footer=1)
    data2 = np.genfromtxt(filename,skip_header=len(data[:,0])+3)
    
    data = np.reshape(data,(len(data)*3,2))
    data2 = np.reshape(data2,(len(data2)/2,2))
    data = np.concatenate((data,data2),axis=0)

    idx = np.unique(data[:,0],return_index=True)
    g4_ee = data[idx[1],0]
    g4_cs = data[idx[1],1]

    CrossSection_b = np.interp(E_neutron_eV,g4_ee,g4_cs)

  ##################################
  # Reads the Angular Distribution file
  if flag_return_ang_dist:

    directory = '%s/Elastic/FS/' % (G4NDL_path)
    filename_prefix = '%d_%d_' % (AA,isotope)
    files = os.listdir(directory)
    filename = ''
    for file in files:
      if file.startswith(filename_prefix):
        filename = directory+file
    if not filename:
      print('ERROR: Could not find the file for the specified element and isotope:')
      print('{} * NOT FOUND'.format(filename))
      return
   
    # load the data from the G4NDL file into data_matrix
    print('Reading {}'.format(filename))
    f = open(filename,'r');
    content = f.readlines()

    nb_entries = np.fromstring(content[2],dtype=int,sep=' ')

    energy_list = np.zeros(nb_entries)
    data_coeffs = np.zeros((nb_entries,30))
    max_nb_of_coeff = 0
    nb_of_coeff = np.zeros(nb_entries)
    entry = 0
    current_entry = 0
    ii = 0
   
    for i in range(5,len(content)):
      a = np.fromstring(content[i],dtype=float,sep=' ')
#      print('Content[{}]'.format(i))
#      print(content[i])
      #print(a)
      current_entry = entry
      # If it's one of the energy rows
      if len(a) == 4 and a[0] == 0 and a[2] == 0:
        energy_list[entry] = a[1]
        nb_of_coeff[entry] = a[3]
        entry = entry + 1
        ii = 0
      # If it's one of the coefficient rows
      else:
        if len(a) != content[i].count('E'):
          a = splitDataRow(content[i])
        data_coeffs[entry-1,ii:(ii+len(a))] = a
        ii = ii + len(a)

  np.set_printoptions(threshold=np.nan)
#  print(data_coeffs)

  #######################################
  # Calculate the angular distribution for the given energy and angles
  ll_list = np.linspace(0,np.amax(nb_of_coeff),np.amax(nb_of_coeff)+1)
  Pl_cos_theta = np.zeros((len(ll_list),len(cos_theta_list)))
  for ii_ll in range(0,len(ll_list)):
    Pl_cos_theta[ii_ll,:] = sp.special.lpmv(0,ii_ll,cos_theta_list)
  
  func_ll = np.zeros((len(energy_list),len(cos_theta_list)))

  for ie in range(0,len(energy_list)):
  
    nb_of_coeff = np.sum(np.abs(data_coeffs[ie,:])>0)
    ll_list = np.linspace(0,nb_of_coeff,nb_of_coeff+1)
    ll_multiplier = [(2*ll_list+1)/2]
    al = np.concatenate(([1],data_coeffs[ie,0:nb_of_coeff]))
    coeff = np.transpose(mat.repmat(ll_multiplier*al, len(cos_theta_list),1))  # Possible transposing error here
    func_ll[ie,:] = np.sum(coeff*Pl_cos_theta[0:len(ll_list),:],0)

  xx = energy_list
  yy = cos_theta_list
  zz = np.transpose(func_ll) # Possible transposing error here
  xxi = E_neutron_eV
  yyi = cos_theta_list
  f = sp.interpolate.interp2d(xx,yy,zz)
  zzi = f(xxi,yyi)

  AngDist_Prob_over_Cos = zzi
          
  return AngDist_Prob_over_Cos  
      



######################################################################
# 
#  Split one of the data lines into an array of floating point values.
#
######################################################################
def splitDataRow( data_str ):  

  data_array = np.zeros(10)

  substrings = data_str.split()

  k = 0

  for i in range(0,len(substrings)):
    temp = np.fromstring(substrings[i],dtype=float,sep='-')
    for j in range(0,len(temp)):
      if len(temp) > 1:
        if j > 0:
          data_array[k] = -temp[j]
        else:
          data_array[k] = temp[j]
      else:
        data_array[k] = temp[j]
      k = k+1

  mask = data_array != 0.

  return data_array[mask]

    
 

######################################################################
# 
#  Get the atomic number of an element given the symbol
#
######################################################################

def AtomicNumber( AtomicSymbol ):

  Symbol = []

  Symbol.append('H')
  Symbol.append('He')
  Symbol.append('Li')
  Symbol.append('Be')
  Symbol.append('B')
  Symbol.append('C')
  Symbol.append('N')
  Symbol.append('O')
  Symbol.append('F')
  Symbol.append('Ne')
  Symbol.append('Na')
  Symbol.append('Mg')
  Symbol.append('Al')
  Symbol.append('Si')
  Symbol.append('P')
  Symbol.append('S')
  Symbol.append('Cl')
  Symbol.append('Ar')
  Symbol.append('K')
  Symbol.append('Ca')
  Symbol.append('Sc')
  Symbol.append('Ti')
  Symbol.append('V')
  Symbol.append('Cr')
  Symbol.append('Mn')
  Symbol.append('Fe')
  Symbol.append('Co')
  Symbol.append('Ni')
  Symbol.append('Cu')
  Symbol.append('Zn')
  Symbol.append('Ga')
  Symbol.append('Ge')
  Symbol.append('As')
  Symbol.append('Se')
  Symbol.append('Br')
  Symbol.append('Kr')
  Symbol.append('Rb')
  Symbol.append('Sr')
  Symbol.append('Y')
  Symbol.append('Zr')
  Symbol.append('Nb')
  Symbol.append('Mo')
  Symbol.append('Tc')
  Symbol.append('Ru')
  Symbol.append('Rh')
  Symbol.append('Pd')
  Symbol.append('Ag')
  Symbol.append('Cd')
  Symbol.append('In')
  Symbol.append('Sn')
  Symbol.append('Sb')
  Symbol.append('Te')
  Symbol.append('I')
  Symbol.append('Xe')
  Symbol.append('Cs')
  Symbol.append('Ba')
  Symbol.append('La')
  Symbol.append('Ce')
  Symbol.append('Pr')
  Symbol.append('Nd')
  Symbol.append('Pm')
  Symbol.append('Sm')
  Symbol.append('Eu')
  Symbol.append('Gd')
  Symbol.append('Tb')
  Symbol.append('Dy')
  Symbol.append('Ho')
  Symbol.append('Er')
  Symbol.append('Tm')
  Symbol.append('Yb')
  Symbol.append('Lu')
  Symbol.append('Hf')
  Symbol.append('Ta')
  Symbol.append('W')
  Symbol.append('Re')
  Symbol.append('Os')
  Symbol.append('Ir')
  Symbol.append('Pt')
  Symbol.append('Au')
  Symbol.append('Hg')
  Symbol.append('Tl')
  Symbol.append('Pb')
  Symbol.append('Bi')
  Symbol.append('Po')
  Symbol.append('At')
  Symbol.append('Rn')
  Symbol.append('Fr')
  Symbol.append('Ra')
  Symbol.append('Ac')
  Symbol.append('Th')
  Symbol.append('Pa')
  Symbol.append('U')
  Symbol.append('Np')
  Symbol.append('Pu')
  Symbol.append('Am')
  Symbol.append('Cm')
  Symbol.append('Bk')
  Symbol.append('Cf')
  Symbol.append('Es')
  Symbol.append('Fm')
  Symbol.append('Md')
  Symbol.append('No')
  Symbol.append('Lr')
  Symbol.append('Uq')
  Symbol.append('Up')
  Symbol.append('Uh')

  i = Symbol.index(AtomicSymbol)
  if i < 0 or i > len(Symbol):
    print('Could not find element symbol - Make sure you wrote it correctly')
    print('{} NOT FOUND'.format(AtomicSymbol))
    return
  

  return i+1






