function amp = EnergySpectrumPositionSmearing(N,E,a,x0,sigx,y0,sigy)
  % Produces an energy spectrum affected by attenuation at different angles
  % in a liquid xenon detector. We're only looking at the 0 < theta < pi
  % region, since it should be symmetric in the pi < theta < 2*pi
  % hemisphere.
  
  mxe = 131.293;
  mn  = 1.;
  En = 2.54*1000;
  
  M = En * (2 * mn * mxe)/(mn + mxe)^2;
  lambda = 11.3;
  
  x = [x0-5*sigx:sigx/100:x0+5*sigx];
  dx = x(2) - x(1);
  y = [y0-5*sigy:sigy/100:y0+5*sigy];
  dy = y(2) - y(1);
  amp = 0;
  iter = 0;
  for i=[x0-5*sigx:sigx/100:x0+5*sigx]
    for j=[y0-5*sigy:sigy/100:y0+5*sigy]
        iter = iter +1;
        if rem(iter,1000)==0
            str = sprintf('On record %d...',iter);
            disp(str);
        end
     b = sqrt(i.^2 + j.^2);
     theta = acos(i./b);
    
     if a < b
       disp('b > a, error')
     else
  
     alpha = acos( ( a + b*cos(theta) )/sqrt( a.^2 + b.^2 + 2*a*b*cos(theta) ) );
  
     d = b* cos(acos(1 - E./M) + alpha + pi - theta) + ...
         sqrt(b^2*cos( acos(1 - E./M) + alpha + pi - theta).^2 ...
         - (b^2 - 2*a*b) );
     d2 = b* cos(-acos(1 - E./M) + alpha + pi - theta) + ...
         sqrt(b^2*cos( -acos(1 - E./M) + alpha + pi - theta).^2 ...
         - (b^2 - 2*a*b) );
  
     amp = amp + N/74. * (exp( - d/lambda) + exp( - d2/lambda)) * 1/(2*pi*sigx*sigy) ...
         * exp( - (i-x0)^2/(2*sigx^2)) * exp( - (j-y0)^2/(2*sigy^2))*dx*dy;
     end
    end
  end

    % Let's implement the smearing below, and comment it out as we need to
  
  
end