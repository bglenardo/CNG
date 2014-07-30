function CurvesAtDifferentAngles()
  a = 75;
  b = 70;

  close; hold off;
  theta = [0 pi/8 pi/4 3*pi/8 pi/2 5*pi/8 3*pi/2 7*pi/8 pi];
  cm = colormap(jet(length(theta)));

  [E_0 amp_0] = EnergySpectrum3D(a,b,0);
  
  for i=1:length(theta)
    [E amp] = EnergySpectrum3D(a,b,theta(i));
    
    plot(E,amp,'color',cm(i,:),'linewidth',2);
    hold on
    
  end
  grid on;
  xlabel('Energy (keV)','fontsize',14);
  ylabel('Amplitude (arbitrary units)','fontsize',14);
  legend('{\theta} = 0','{\theta} = {\pi}/8','{\theta} = {\pi}/4','{\theta} = 3{\pi}/8','{\theta} = {\pi}/2','{\theta} = 5{\pi}/8','{\theta} = 3{\pi}/4','{\theta} = 7{\pi}/8','{\theta} = {\pi}');




end