function [E amplitude] = EnergySpectrum3D(a,b,theta)
  mxe = 131.293;
  mn  = 1.;
  En = 2.54*1000;

 alpha = acos( ( a + b*cos(theta) )/sqrt( a^2 + b^2 + 2*a*b*cos(theta) ) );
 
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Here's where we start the actual calculation of the energy spectrum.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %figure(1); clf;
 disp('Creating variables');
  beta = [0:0.1:2*pi]; 
  gamma = [0:0.1:pi];
  
  cyllinderSurface = [];
  
  for i=1:length(beta)

      if mod(i,20)==1
          disp('Beginning calculation...')
      end
      
      d = -b*cos(beta(i)) + sqrt(b^2*cos(beta(i)).^2 - (b^2 - a^2) );
      %d_str = sprintf('d = %f',d);
      %disp(d_str);
      
      for j=1:4%length(gamma)

          %condition_str=sprintf('d*tan(gamma(j)) = %f',d*tan(gamma(j)));
          %disp(condition_str);
          if abs( d*cos(gamma(j))/sqrt(cos(gamma(j))^2-1) ) < 25 
           
           D = d*sqrt(1 + cot(gamma(j))^2);      
           x_0 = D*sin(gamma(j))*cos(beta(i));
           y_0 = D*sin(gamma(j))*sin(beta(i));
           z = D*cos(gamma(j));
           
           x_1 = x_0*cos(theta) - y_0*sin(theta);
           y_1 = x_0*sin(theta) + y_0*cos(theta);
           
           x = x_1 + b*cos(theta);
           y = y_1 + b*sin(theta);
           
          
           %disp('Plotting point...');       
           plot3(x,y,z,'.','color',[0 0. 1],'markersize',15);
           grid on;
           hold on;
         
          end
      end
  end
  
  %cylinder(25,50);
  grid on; hold on; 
  
  xlabel('X','fontsize',16);
  ylabel('Y','fontsize',16);
  zlabel('Z','fontsize',16);
  
  clear x; clear y; clear d; clear z; clear gamma; clear beta;
  
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Here's where we start the actual calculation of the energy spectrum.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  
  M = En * (2 * mn * mxe)/(mn + mxe)^2;
  lambda = 11.3;

  crossSecData = sortrows(importdata('JENDFCrossSection.txt'),1);

  Theta = crossSecData(:,1)*pi/180; 
  %Theta = 3*pi/8;
  E = M*(1-cos(Theta));
  %crossSec = ones(length(Theta))*1000;
  crossSec = crossSecData(:,2);
  
  alpha = acos( ( a + b*cos(theta) )/sqrt( a^2 + b^2 + 2*a*b*cos(theta) ) );
  
  
  for i=1:length(Theta)
     Phi = [0:0.01/sin(Theta(i)):2*pi];
     amplitude(i)=0;
     for j=1:length(Phi)
         
      gamma = asin(sin(Theta(i))*sin(Phi(j)));

      if Phi(j)<pi/2 | Phi(j)>3*pi/2
       beta  = acos(cos(Theta(i))/cos(gamma)) - theta + alpha;
      else
       beta  = acos(cos(Theta(i))/cos(gamma)) - theta + alpha;
      end
      
      str = sprintf('Gamma: %f \t Beta: %f',gamma,beta);
      %disp(str);
      
      d = -b*cos(beta) + sqrt(b^2*cos(beta).^2 - (b^2 - a^2) );

      if abs(d*tan(gamma)) < 25
         % disp('Inside...');
        D = d*sqrt(1 + tan(gamma)^2);
      else
        D = abs(25/cos(gamma));
      end
      
      amplitude(i) = amplitude(i) + crossSec(i)*exp(-D/lambda);
      
      x_0 = D*sin(gamma)*cos(beta);
      y_0 = D*sin(gamma)*sin(beta);
      z = D*cos(gamma);
           
      x_1 = x_0*cos(theta) - y_0*sin(theta);
      y_1 = x_0*sin(theta) + y_0*cos(theta);
           
      x = x_1 + b*cos(theta);
      y = y_1 + b*sin(theta);
      
      
      
           
      %plot3(x,y,z,'*','color',[0.5 0 0]);
      if mod(j,10) == 1
       %line([b*cos(theta) x],[b*sin(theta) y], [0 z],'color', [0.5 0 0]);
      end
     
      %plot3(-(a+1),0,0,'*r','markersize',20);
      
      
     end 
     
  end
  
  %line([-(a+1) b*cos(theta)],[0 b*sin(theta)],[0 0],'color',[0.5 0 0],'linewidth',2);

  

end