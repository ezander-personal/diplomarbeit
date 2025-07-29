#include <math.h>
#define PI M_PI

#include "General.h"



double bessel( double x )
{ double y=0.5*x, sum=1.0, delta=1.0, iter=1.0, eps=1.0e-8;
  int i=1;
  while( sum*eps-iter<=0.0 && i<26 )
    {
      delta = delta*y/i;
      iter  = sqrt(delta);
      sum   = sum+iter;
      i++;
    }
  return sum;
  }



/* *******************************
   Filter Version 2
   ******************************* */
void filter( double *vector, int laenge, double ogf, double ugf, double sf, int ordnung, int window )
{ 

  // int N=ordnung+1;
  int alf=ordnung/2,m=ordnung;
  double bet=0.025;
  dVector vecopy( laenge+1 );
  dVector gk( ordnung+1 );
  // double omg=2.0*PI*(ogf-ugf)/sf;
  double onf=2.0*PI*(ogf/sf);
  double unf=2.0*PI*(ugf/sf);

  for( int k=0; k<=alf; k++ )
     {
       double x1, x2, wk, hk;
       switch( window )
	 {
	 case 1: // Rect
	   wk = 1.0;
	   break;
	 case 2:
	   x1 = bet*sqrt( alf*alf - (k-alf)*(k-alf) );
	   x2 = bet*alf;
	   wk=bessel( x1 ) / bessel( x2 ); // Bessel
	   break;
	 case 3:
	   // wk=0.235*2.0*cos((PI*k/m))+1.0-2.0*0.235; // Hamming
	   wk=0.54 - 0.46*cos((2*PI*k/(m))); // Hamming 
	   break;
	 case 4:
	   wk=0.42-0.5*cos(2.0*PI*k/m)+0.08*cos(4.0*PI*k/m); // Blackman
	   break;
	 default: // Rect
	   wk = 1;
	   break;
	 }
       
       if( k!=alf )
	 hk=1.0 / PI * (sin( (alf-k)*onf) -sin( (alf-k)*unf) ) / (alf-k); // Voßschulte
       else
	 hk = 1.0 / PI * (onf-unf);

       gk[k] = hk*wk;
       gk[m-k]=hk*wk;
     }

  // for( int n=0; n<=m; n++ )
  // cerr << n << tab << gk[n] << endl;

  
  for( int i=m+1; i<=laenge; i++ )
    {
      vecopy[i]=0.0;
      for( int k=0; k<=m; k++ )
	vecopy[i-m] += vector[i-k]*gk[k];
    }
  
  for( int i=0; i<laenge-m; i++ )
    vector[i]=vecopy[i];

  for( int i=laenge-m; i<laenge; i++)
    vector[i]=0.0;
    
  /*
  for( int i=0; i<laenge; i++ )
    {
      vecopy[i] = 0.0;
      for( int k=-alf; k<=alf; k++ )
	{
	  int n = i+k;
	  if( n<0 ) n=0;
	  if( n>=laenge ) n=laenge-1;

	  vecopy[i] +=  gk[k+alf] * vector[n];
	}
    }
    */
  // memcpy( vector, &(vector[0]), laenge*sizeof(double) ); 
}








double WeightedAvg( double* x, int nData, int i, double* weights, int start, int count, boolean logarithmic )
{
  int n=i+start; 
  double d=0.0, w=0.0, y=0.0; 

  for( int j=0; j<count; j++ )
    {
      if( n<0 )
	y = x[0];
      else if (n>=nData )
	y = x[ nData-1 ];
      else
	y = x[n];
      
      d += weights[j]*( logarithmic ? log( y ) : y );

      w=w+weights[j];
      n++;
    }
  return logarithmic ? exp(d/w) :  d/w;
}


void ffilter( const string& ifilename, const string& ofilename, int passes )
{
  int rows = getFileRows( ifilename );
  dVector x(rows), t(rows), y(rows);
  
  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );
  
  ofstream fout( ofilename, ios::out | ios::trunc );
  
  double weight[] = { 1, 1, 1, 1, 1, 2, 2, 2, 4, 4, 8, 4, 4, 2, 2, 2, 1, 1, 1 ,1 ,1 };
  int count = 21, start = -10;

  for( int p=0; p<passes; p++ )
    {
      for( int i=0; i<rows; i++ )
	y[i] = WeightedAvg( x(), rows, i, weight, start, count, FALSE );
      
      for( int i=0; i<rows; i++ )
	x[i] = y[i];
    }
  
  for( int i=0; i<rows; i++ )
    {
      fout << t[i] << tab << x[i] << endl;
    }

  fout.close();
  
  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "fourier spectrum" ).xTitle( "w" ).yTitle( "ln P(w)" );
  gpi.setXRange().xRange( 0.0, t[rows-1] );
  gpi.setPlotStyle( LINES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();

}





void filter( const String& ifilename, const String& ofilename, double lowerFreq, double upperFreq, int order, int window )
{
  if( order<0 ) // int this special case (filtering fourier spectra), very simple filter with -order passes
    {
      ffilter( ifilename, ofilename, -order );
      return;
    }

  int rows = getFileRows( ifilename );
  
  dVector x(rows), t(rows);

  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );

  filter( x(), rows, upperFreq, lowerFreq,  1.0/(t[1]-t[0]), order, window );


  ofstream fout( ofilename, ios::out | ios::trunc );

  for( int i=0; i<rows; i++ )
    fout << t[i] << tab << x[i] << endl;

  fout.close();


  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "filtered time series" ).xTitle( "t" );
  gpi.setPlotStyle( LINES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();

}































