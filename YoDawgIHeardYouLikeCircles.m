% YoDawgIHeardYouLikeCircles.m
% 
% This function is written to pack circles into a larger circle and return
% the number and coordinates of these. 


function [ncircles arrayXY] = YoDawgIHeardYouLikeCircles(rSmall, ...
    rBig, center)
  ncircles = 0;

  y = 0; 
  numInRow=0;
  xref = 0;
  if (center > 1 | center <= 0)
      error('Argument 3 must be a boolean, 1 or 0, whether or not we have a circle at the center.');
  else if (center == 1)
      numInRow = floor(rBig/rSmall);
     
      if ((numInRow+0.5)*rSmall > rBig)
          numInRow = numInRow-1;
      end
      xref = -2*rSmall*numInRow;
      for i=1:(2*numInRow + 1)
          ncircles = ncircles+1;
          x = 2*rSmall*(i-(1+numInRow));
          arrayXY(i,:) = [x 0]; 
      end
      end
  end
  ii = i;
  i=0;
  y = rSmall*sqrt(3);
  while (y <= sqrt(3)*numInRow*(2*rSmall))
      i = i+1;
      numInThisRow = (numInRow*2 + 1) - i;
      y = rSmall*sqrt(3)*i;
      for j=1:numInThisRow
          x = xref + rSmall*(i+2*(j-1));
          linIndex = (2*numInRow + 1 - i/2)*(i-1) + j + 2*numInRow+1;
          arrayXY(linIndex,:) = [x y];
          ncircles = ncircles+1;
      end
      

  y = y + rSmall*sqrt(3)*i; 
  end
  
  arrayXY = [arrayXY; -arrayXY(ii:end,:)];
  
      




end