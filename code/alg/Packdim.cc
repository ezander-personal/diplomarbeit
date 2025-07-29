#include "General.h"
#include "Statistical.h"

#include "nr.h"

int findMax(const dVector& x)
{
  int maxat=x.getnh();
  double max = x[maxat];

  for( int i=x.getnl(); i<=x.getnh(); i++ )
    {
      double xm=x[i];
      if( xm>max ) { max=xm; maxat=i; }
    }

  return maxat;
}

void packdim( const String& ifilename, const String& ofilename, int delay, int maxdim, int bins, double x1, double x2 )
{
  int rows = getFileRows( ifilename );
  
  dVector x(rows), t(rows);
  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );


  double xmin=0, xmax=0;
  getMinMax( x, xmin, xmax );

  ASSERT(xmax>xmin);
  double xfac = (double)bins/(xmax-xmin);
  double pfac = 1.0/(double)rows;

  dVector p0(bins), p1(bins), p2(bins);

  for( int i=0; i<bins; i++ ) { p0[i] = p1[i] = p2[i] = 0; }

  for( int i=0; i<rows; i++)
    {
      int bin = (int)((x[i]-xmin)*xfac);
      if( bin>=bins ) bin=bins-1;
      p0[bin]+=pfac;
    }

  // int sbin=findMax(p0)+20;
  int sbin = (int)((x1-xmin)*xfac);

  for( int i=0; i<rows-delay; i++ )
    {
      int bin1 = (int)((x[i]-xmin)*xfac);
      if( bin1==sbin )
	{
	  int bin2 = (int)((x[i+delay]-xmin)*xfac);
	  p1[bin2]+=pfac;
	}
      
    }

  int sbin2 = (int)((x2-xmin)*xfac);
  // int sbin2=findMax(p1);
  //sbin2-=10;

  for( int i=0; i<rows-2*delay; i++ )
    {
      int bin1 = (int)((x[i]-xmin)*xfac);
      int bin2 = (int)((x[i+delay]-xmin)*xfac);
      if( (bin1==sbin) && (bin2=sbin2)  )
	{
	  int bin3 = (int)((x[i+2*delay]-xmin)*xfac);
	  p2[bin3]+=pfac;
	}
      
    }

  cerr << sbin << tab << sbin2 << endl;

  ofstream fout( ofilename, ios::out | ios::trunc );
  
  for( int i=0; i<bins; i++ )
    {
      fout << (double(i)/xfac)+xmin << tab << p0[i] << tab << p1[i] << tab << p2[i] << endl;
    }

  fout.close();
  
  
  gpInfo gpi( ofilename );
  gpi.NewFile();

  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "packdim" ).xTitle( "x" ).yTitle("P");
  gpi.setPlotStyle( LINES ).pause();
  gpi.AppendToFile();

  gpi.using1( 1 ). using2( 3 );
  gpi.Title( "packdim" ).xTitle( "x" ).yTitle("P");
  gpi.setPlotStyle( LINES ).pause();
  gpi.AppendToFile();

  gpi.using1( 1 ). using2( 4 );
  gpi.Title( "packdim" ).xTitle( "x" ).yTitle("P");
  gpi.setPlotStyle( LINES ).pause();
  gpi.AppendToFile();
}






