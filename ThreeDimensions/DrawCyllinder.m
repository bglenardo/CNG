function DrawCyllinder(a,b)
  % This function just tests to make sure my equations are correct for a
  % cyllinder in spherical polar coordinates. The origin lies at the
  % hypothetical interaction point of a neutron in xenon.
  
  theta = pi;
  alpha = acos( ( a + b*cos(theta) )/sqrt( a^2 + b^2 + 2*a*b*cos(theta) ) );
  
  disp('Creating variables');
  beta = [0:0.1:2*pi];
  gamma = [0:0.1:pi];
  
  for i=1:length(beta)

      if mod(i,20)==1
          disp('Beginning calculation...')
      end
      
      d = -b*cos(beta(i)+theta-alpha) + sqrt(b^2*cos(beta(i)+theta-alpha).^2 - (b^2 - a^2) );
      %d_str = sprintf('d = %f',d);
      %disp(d_str);
      
      for j=1:length(gamma)

          %condition_str=sprintf('d*tan(gamma(j)) = %f',d*tan(gamma(j)));
          %disp(condition_str);
          if abs( d*cos(gamma(j))/sqrt(cos(gamma(j))^2-1) ) < 25; 
           
           D = d*sqrt(1 + cot(gamma(j))^2);      
           x = D*sin(gamma(j))*cos(beta(i));
           y = D*sin(gamma(j))*sin(beta(i));
           z = D*cos(gamma(j));
           
           plot3(x,y,z,'*r');
           grid on
           hold on;
         
         end
      end
  end
  xlabel('X','fontsize',16);
  ylabel('Y','fontsize',16);
  zlabel('Z','fontsize',16);
  


end
