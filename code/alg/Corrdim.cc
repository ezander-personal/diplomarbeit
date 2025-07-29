#include <math.h>

#include "General.h"
#include "Statistical.h"
#include "nr.h"

static int MIN_BEGIN_END_DIFF =10;
#define MIN_BEGIN_DIFF 1.0e-8

static int findMinBegin( double* x, int count )
{
  int minBegin = 0;
  while( TRUE )
    {
      if( fabs( x[minBegin+1]-x[minBegin] ) > MIN_BEGIN_DIFF ) return minBegin;
      minBegin++;
      if( minBegin+1 == count ) return 0;
    }
}

static void findMaxCC( double* x, double* y, int count, boolean calcBegin, boolean calcEnd, int* begin, int* end, double scaleExp )
{
  int _begin=*begin, _end=*end;
  double minCC;

  if( calcBegin && calcEnd )
    {
      _begin=0; _end=_begin+MIN_BEGIN_END_DIFF;
      minCC = correlationCoefficient2( x+_begin, y+_begin, _end-_begin, scaleExp ); 

      for( int i=0; i<count-MIN_BEGIN_END_DIFF; i++ )
	for( int j=i+MIN_BEGIN_END_DIFF; j<count; j++ )
	  {
	    double cc = correlationCoefficient2( x+i, y+i, j-i, scaleExp ); 

	    if( cc > minCC ) 
	      {
		minCC = cc;
		_begin = i; _end = j;
	      }
	  }
    }
  else if( calcBegin )
    {
      _begin=0; 
      minCC = correlationCoefficient2( x+_begin, y+_begin, _end-_begin, scaleExp ); 

      for( int i=0; i<_end-MIN_BEGIN_END_DIFF; i++ )
	{
	  double cc = correlationCoefficient2( x+i, y+i, _end-_begin, scaleExp ); 
	  if( cc > minCC ) 
	    {
	      minCC = cc;
	      _begin = i;
	    }
	  }
    }
  else if( calcEnd )
    {
      _end=_begin+MIN_BEGIN_END_DIFF; 
      minCC = correlationCoefficient2( x+_begin, y+_begin, _end-_begin, scaleExp ); 

      for( int j=0; j<count; j++ )
	{
	  double cc = correlationCoefficient2( x+_begin, y+_begin, j-_begin, scaleExp ); 
	  if( cc > minCC ) 
	    {
	      minCC = cc;
	      _end = j;
	    }
	  }
    }
  else
    ASSERT( FALSE );

  *begin = _begin; *end = _end;
}

void corrdim( const String& ifilename, const String& ofilename, double begin, double end, boolean units, double scaleExp, double radius, int minDiff )
{
  MIN_BEGIN_END_DIFF =minDiff;

  int rows = getFileRows( ifilename );
  int cols = getFileCols( ifilename );

  boolean calcBegin = (begin==-1);
  boolean calcEnd = (end==-1);

  int maxDim = cols-1;

  dVector r( rows );
  dMatrix C( 0, maxDim, 0, rows-1 );

  
  readFileCol( ifilename, 0, r(), cols );
  readFileCols( ifilename, cols, C() );

  if( radius>0 )
    {
      for( int i=0; i<rows; i++ )
	{
	  double x=exp(r[i])/radius;
	  r[i] = log(2*x-x*x);
	  if( x>1 ) 
	    {
	      rows=i;
	      break;
	    }
	}
    }



  ofstream fout( ofilename, ios::out | ios::trunc );

  int _end, _begin;
  if( !units )
    {
      _end = (int)end; _begin=(int)begin;
    }
  else
    {
      _begin=0; _end=rows-1;
      for( int i=0; i<rows; i++ )
	{
	  if( fabs( r[i]-begin ) < fabs( r[_begin]-begin ) ) _begin=i;
	  if( fabs( r[i]-end ) < fabs( r[_end]-end ) ) _end=i;
	}
    }

  for( int d=1; d<=maxDim; d++ )
    {

      double m,n,err_m=0, err_n=0;
      int minBegin = findMinBegin( C[d], rows ) + 3;

      if( calcBegin || calcEnd ) findMaxCC( r(), C[d], rows, calcBegin, calcEnd, &_begin, &_end, scaleExp );

      if( _begin < minBegin ) _begin = minBegin;
      if( _end < minBegin + MIN_BEGIN_END_DIFF ) _end = minBegin + MIN_BEGIN_END_DIFF;
      if( _end >= rows ) _end = rows-1;
      cerr << "hurps" << tab << _begin << tab << r[_begin] << tab  << _end << tab << r[_end] << endl;
      linReg( r(), C[d], _begin, _end, m, n, err_m, err_n, FALSE, FALSE );
      double m2=(C[d][_begin]-C[d][_end])/(r[_begin]-r[_end]);
      double rm1 = (r[_begin]+r[_end])/2;
      double m3=m/(1-exp(rm1)/2 );
      double rm2 = -sqrt(r[_begin]*r[_end]);
      double m4=m/(1-exp(rm2)/2 );
      double eps=0.001/2.0;
      double m5=(C[d][_begin]-C[d][_end])/(log(exp(r[_begin])+eps)-log(exp(r[_end])+eps));
      cerr << "Slope: " << m << tab << m2 << tab << m3 << tab << m4 << tab << m5 << endl;
	
      fout << d << tab << m << tab << err_m << tab << r[_begin] << tab << r[_end] << endl; 
    }
  
  fout.close();


  gpInfo gpi( ofilename );
  gpi.Title( "correlation-dimension" ).xTitle( "d" ).yTitle( "D2" );
  
  gpi.setPlotStyle( LINESPOINTS ).pause();
  
  gpi.using1( 1 ).using2( 2 );
  
  gpi.NewFile();
  gpi.AppendToFile();
}










