#include <math.h>
#include <stdlib.h>


#include "General.h"
#include "Statistical.h"


void histoNormal( const String& ifilename, const String& ofilename, double resolution, boolean isInteger, int col )
{
  int rows = getFileRows( ifilename );
  int cols = getFileCols( ifilename );

  dVector x( rows );

  readFileCol( ifilename, col-1, x(), cols, rows );

  if( isInteger )
    {
      ASSERT( 0 );
    }
  else
    {
      double min, max;
      getMinMax( x, min, max );

      int count=int(100.0/resolution)+1;
      double xres=(max-min)/(100.0/resolution);
      int n[count];
      for( int i=0; i<count; i++ ) n[i]=0;

      for( int i=0; i<rows; i++ )
	{
	  int index = int( (x[i]-min)/xres );
	  ASSERT( index>=0 );
	  if( index==count ) index=count-1;
	  ASSERT( index<count );
	  n[index]++;
	}
      
      
      ofstream fout( ofilename, ios::out | ios::trunc );
      for( int i=0; i<count; i++ )
	{
	  fout << i*xres+min << tab << n[i] << endl;
	  fout << (i+1)*xres+min << tab << n[i] << endl;
	}
      
      fout.close();
    }





  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "Histogramm" ).xTitle( "x" ).yTitle( "n" );
  gpi.setPlotStyle( LINES | IMPULSES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
}

static int compareDoubles( const double* d1, const double* d2 )
{
  if( *d1>*d2 )
    return 1;
  else if( *d1==*d2 )
    return 0;
  else
    return -1;
}

void histoRandom( const String& ifilename, const String& ofilename, double resolution, boolean isInteger, int col )
{
  int rows = getFileRows( ifilename );
  int cols = getFileCols( ifilename );

  dVector x( rows ), t( rows );

  readFileCol( ifilename, col-1, x(), cols, rows );

  if( isInteger )
    {
      ASSERT( 0 );
    }
  else
    {
      double min, max;
      getMinMax( x, min, max );

      qsort( x(), rows, sizeof(double), compareDoubles );
      for( int i=0; i<rows; i++ ) t[i]=double(i)/double(rows);

      int n=(int)(rows*resolution/100.0);
      dVector y(rows-n), r(rows-n);

      for( int i=0; i<rows-n; i++ )
	{
	  double offset,slope;
	  linReg( x()+i, t()+i, 0, n-1, slope, offset );
	  r[i]=slope;
	  y[i]=mean( x()+i, n );
	}

      
      ofstream fout( ofilename, ios::out | ios::trunc );
      double ly=y[0]-10000;
      double res=resolution/100;
      int count=int(1.0/res);
      int N=rows;
      for( int j=0; j<=count; j++ ) {
	int i1 = int(j*res*double(N));
	int i2 = int((j+1)*res*double(N));
	if(i2>=rows) i2=rows-1;
	if(i1>=rows) break;
	fout << x[i1] << tab << double(i2-i1)/(x[i2]-x[i1]) << endl;
	fout << x[i2] << tab << double(i2-i1)/(x[i2]-x[i1]) << endl;
      }
      fout.close();
    }
	  
	/*
	  double d;
	  for( int i=i1; i<i2; i++ ){

	  // fout << x[i] << tab << double(i)/double(rows) << endl;
	  if( y[i]-ly>resolution*(max-min)/100.0 ) {
	  fout << y[i] << tab << r[i] << tab << x[i] << tab << t[i] << endl;
	  ly=y[i];
	  }
	  }
	*/
      



  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "Histogramm Rand" ).xTitle( "x" ).yTitle( "n" );
  gpi.setPlotStyle( LINES | IMPULSES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
  
}

void histo( const String& ifilename, const String& ofilename, double resolution, boolean isInteger, int col, boolean randomMode )
{
  if( randomMode )
    histoRandom( ifilename, ofilename, resolution, isInteger, col );
  else
    histoNormal( ifilename, ofilename, resolution, isInteger, col );
}



void histo2d( const String& ifilename, const String& ofilename, double resolution, boolean isInteger, int col, int delay )
{
  int rows = getFileRows( ifilename );
  int cols = getFileCols( ifilename );

  dVector x( rows );

  readFileCol( ifilename, col-1, x(), cols, rows );

  if( isInteger )
    {
      ASSERT( 0 );
    }
  else
    {
      double min, max;
      getMinMax( x, min, max );

      int count=int(100.0/resolution)+1;
      double xres=(max-min)/(100.0/resolution);
      iMatrix n(0,count-1,0,count-1);

      for( int i=0; i<count; i++ )
	for( int j=0; j<count; j++ )
	  n[i][j]=0;

      for( int i=0; i<rows-delay; i++ )
	{
	  int index1 = int( (x[i]-min)/xres );
	  int index2 = int( (x[i+delay]-min)/xres );
	  ASSERT( index1>=0 && index2>=0 );
	  if( index1==count ) index1=count-1;
	  if( index2==count ) index2=count-1;
	  ASSERT( index1<count && index2<count );
	  n[index1][index2]++;
	}
      
      
      ofstream fout( ofilename, ios::out | ios::trunc );
      for( int i=0; i<count; i++ )
	{
	  for( int j=0; j<count; j++ )
	    {
	      fout << n[i][j] << tab;
	    }
	  fout << endl;
	}
      fout << endl;

      
      fout.close();
    }





  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "Histogramm" ).xTitle( "x" ).yTitle( "n" );
  gpi.setPlotStyle( POINTS ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
}













