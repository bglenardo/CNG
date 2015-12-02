from read_g4ndl import read_g4ndl
import numpy as np
import scipy as sp
from matplotlib import pyplot as plt


isotopes = np.array([124,126,128,129,130,131,132,134,136]);

a = np.zeros((len(isotopes),1000))

for i in range(0,len(isotopes)):
  b = np.array(read_g4ndl('/Applications/geant4.9.4.p04/data/G4NDL3.14/','Xe',isotopes[i],[2.45e6],np.linspace(-1.,1,1000)))
  a[i,:] = np.transpose(b)[0]


theta = np.arccos(np.linspace(-1.,1,1000))


for i in range(0,len(isotopes)):
  leg_label = '%d' % int(isotopes[i])
  plt.plot(theta,a[i,:],label=leg_label)
  

plt.legend(loc=3,prop={'size':15})
plt.xlabel('Scattering angle')
plt.ylabel('Amplitude')
plt.grid()
plt.semilogy()
plt.show()



