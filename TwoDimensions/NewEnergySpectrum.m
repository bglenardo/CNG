function amp = NewEnergySpectrum(N,E,a,b,theta)
  % Produces an energy spectrum affected by attenuation at different angles
  % in a liquid xenon detector
  
  mxe = 131.293;
  mn  = 1.;
  En = 2.54*1000;
  
  M = En * (2 * mn * mxe)/(mn + mxe)^2;
  lambda = 11.3;
  
  
  if a < b
    disp('b > a, error');
  end
  
  alpha = acos( ( a + b*cos(theta) )/sqrt( a^2 + b^2 + 2*a*b*cos(theta) ) );
  
  d = -b*cos(acos(1 - E./M) + alpha - theta) + sqrt(b^2*cos( acos(1 - E./M) + alpha - theta).^2 - (b^2 - a^2) );
  d2 = -b*cos(-acos(1 - E./M) + alpha - theta) + sqrt(b^2*cos( -acos(1 - E./M) + alpha - theta).^2 - (b^2 - a^2) );
  
  amp = (N/74 * exp( - d/lambda) + N/74 * exp( - d2/lambda)) * ;
  distRatio = d./d2;
  % Let's implement the smearing below, and comment it out as we need to
  
  
end