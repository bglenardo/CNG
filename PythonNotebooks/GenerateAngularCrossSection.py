##########################################################################################
#
#  GenerateAngularCrossSection.py
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



def GenerateAngularCrossSection(coeffArray,nb_of_points=1000):

  nb_of_coeff = len(coeffArray)
  coeffArray = np.concatenate(([1],coeffArray))

  cos_theta_list = np.linspace(-1,1,nb_of_points);

  #######################################
  # Calculate the angular distribution for the given energy and angles
  ll_list = np.linspace(0,nb_of_coeff,nb_of_coeff+1)
  ll_multiplier = (ll_list*2 + 1)/2
  Pl_cos_theta = np.zeros((len(ll_list),nb_of_points))
  for ii_ll in range(0,len(ll_list)):
    Pl_cos_theta[ii_ll,:] = sp.special.lpmv(0,ii_ll,cos_theta_list)

  AngDist_Prob_over_Cos = np.zeros(nb_of_points)

  for i in range(0,nb_of_coeff+1):
    AngDist_Prob_over_Cos = AngDist_Prob_over_Cos + coeffArray[i]*ll_multiplier[i]*Pl_cos_theta[i,:]

  return AngDist_Prob_over_Cos
