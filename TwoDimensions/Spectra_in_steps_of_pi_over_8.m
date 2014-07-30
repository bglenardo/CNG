function Spectra_in_steps_of_pi_over_8(a,b,E)
  hold off
  hold on
  
  cm = colormap(jet(9));

  for i=0:8
     amp(:,i+1) = NewEnergySpectrum(1000,E,a,b,i*pi/8);
     plot(E,amp(:,i+1),'linewidth',2,'color',cm(i+1,:));
  end
  grid on
  set(gca,'fontsize',14);
  xlabel('Energy (keV)','fontsize',14);
  ylabel('Arbitrary units','fontsize',14);
  legend('{\theta} = 0','{\theta} = {\pi}/8','{\theta} = {\pi}/4','{\theta} = 3{\pi}/8','{\theta} = {\pi}/2','{\theta} = 5{\pi}/8','{\theta} = 3{\pi}/4','{\theta} = 7{\pi}/8','{\theta} = {\pi}');
  
end