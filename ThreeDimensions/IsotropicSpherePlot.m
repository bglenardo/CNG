function IsotropicSpherePlot()
  gamma = [0:0.05:pi];
  R = 1;
  hold off
  
  for i=1:length(gamma)
      beta = [0:(0.05/sin(gamma(i))):2*pi
          ];
      
      for j = 1:length(beta)
        if mod(i,100)==1
            str = sprintf('i = %d',i);
            disp(str);
        end
            
        x = R*sin(gamma(i))*cos(beta(j));
        y = R*sin(gamma(i))*sin(beta(j));
        z = R*cos(gamma(i));
      
        plot3(x,y,z,'.b');
        hold on
        
      end  
  end




end
