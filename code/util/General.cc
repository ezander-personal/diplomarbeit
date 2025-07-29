#include "General.h"

#include <math.h>
#include <stdio.h>


string toString( int x)
{
  char buffer[10];
  snprintf( buffer, 10, "%d", x );
  return string(buffer);
}


double getPot10( double range )
{
  double pot10 = 1.0;
  while( range>pot10 ) pot10*=10;
  while( range<pot10 ) pot10/=10;
  return pot10;
}

double minRound( double min, double range, double add )
{
  ASSERT( range>0 );

  double pot10 = getPot10( range );
  double fac   = ceil( range/pot10 );

  return  floor( min / pot10 * 10.0 + add * fac * 0.5  ) * pot10 *0.1;
}

double maxRound( double max, double range, double add )
{
  ASSERT( range>0 );

  double pot10 = getPot10( range );
  double fac   = ceil( range/pot10 );

  return ceil( max / pot10 * 10.0 + add * fac * 0.5 ) * pot10 *0.1;
}

void minmaxRound( double& min, double& max, double add )
{
  ASSERT( max>min );

  double range=max-min;

  double pot10 = getPot10( range );
  double fac   = ceil( range/pot10 );

  max = ceil(  max / pot10 * 10.0 + add * fac * 0.5 ) * pot10 * 0.1;
  min = floor( min / pot10 * 10.0 - add * fac * 0.5 ) * pot10 * 0.1;
}






