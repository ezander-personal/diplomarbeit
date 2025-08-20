#include <math.h>

#include "General.h"
#include "Statistical.h"
#include "nr.h"


void mirrorV( double** x, int n )
{
  for( int i=1; i<=n/2; i++ )
    {
      double* v=x[i];
      x[i] = x[n-(i-1)];
      x[n-(i-1)]=v;
    }
}

void mirrorH( double** x, int n )
{
  for( int i=1; i<=n; i++ )
    {
      double* v=x[i];
      for( int j=1; j<=n/2; j++ )
	{
	  double b=v[j];
	  v[j] = v[n-(j-1)];
	  v[n-(j-1)]=b;
	}
    }
}

void transpose( double** x, int n )
{
  for( int i=1; i<=n-1; i++ )
    {
      for( int j=i+1; j<=n; j++ )
	{
	  double b=x[i][j];
	  x[i][j] = x[j][i];
	  x[j][i]=b;
	}
    }
}

void normalize( double** x, int n )
{
  for( int i=1; i<=n; i++ )
    {
      double sum=0.0;
      for( int j=1; j<=n; j++ ) sum+=x[i][j]*x[i][j];
      sum=1.0/sqrt(sum);
      for( int j=1; j<=n; j++ ) x[i][j]*=sum;
    }
}


void matrixOut( double** x, int n )
{
  cout << "{" << endl;
  for( int i=1; i<=n; i++ )
    {
      cout << tab << "{";
      for( int j=1; j<=n; j++ )
	{
	  if( j<n )
	    cout << x[i][j] << "," << tab;
	  else
	    cout << x[i][j];
	}
      if( i<n )
	cout << "}, " << endl;
      else
	cout << "} " << endl;
    }
  cout << "}" << endl;
}

void vectorOut( double* v, int n )
{
  return;
  for( int i=1; i<=n; i++ )
    {
      cout << v[i] << tab;
    }
  cout << endl;
}

 
void svd( const String& ifilename, const String& ofilename, int window, boolean nosort )
{
  cout.precision( 10 );
  int rows = getFileRows( ifilename );
  if( rows<1 ) exit( 1 );

  dVector v(rows);
  if( readFileCol( ifilename, 1, v() ) ) exit( 1 );

  int n=rows-(window-1);

  dMatrix x(1,window,1,window);

#ifndef BerechneEinzeln
  // calculate the first row of the covariance matrix
  for( int c=1; c<=window; c++ )
    {
      double& xp = x[c][1];
      double *vp1 = v(), *vp2 = v()+c-1;
      xp = 0;
      for( int i=0; i<n; i++ ) // { xp += *vp1++ * *vp2++; }
	{ xp += (*vp1) * (*vp2); vp1++; vp2++; }
      // xp /= n;
    }

  // calculate row 2 to 'window' of the cov matrix
  for( int r=2; r<=window; r++ )
    {
      for( int c=1; c<r; c++ ) x[c][r] = x[r][c];
	
      for( int c=r; c<=window; c++ ) // x[c][r] = x[c-1][r-1] + (v[n+r-1]*v[n+c-1]-v[r-2]*v[c-2] ); // /n;
	x[c][r] =( x[c-1][r-1] - v[r-2]*v[c-2]) + v[n+r-1]*v[n+c-1];
    }
  for( int c=1; c<=window; c++)
    for( int r=1; r<=window; r++) 
      x[c][r]/=n;

#else

  for( int r=1; r<=window; r++ )
    {
      for( int c=1; c<=window; c++ )
	{
	  double xp=0.0;

	  for( int i=0; i<n; i++ ) 
	    xp += v[r+i-1]*v[c+i-1];

	  x[r][c]=xp/n;
	}
    }

#endif


  dVector d(window), e(window);

  // do svd


  // matrixOut( x, window );


  tred2( x, window, d, e );
  tqli( d, e, window, x );


  transpose( x(), window );
  mirrorV( x(), window );
  normalize( x(), window );

  // write output

  double tr=0.0;
  for( int i=1; i<=window; i++){
      d[window-i]=fabs(d[window-i]);
      tr+=d[window-i];
  }

  // sort
  if( !nosort ){
		for( int i=0; i<window; i++ ){
			boolean changed=FALSE;
			for( int j=0; j<window-i-1; j++ ){
				if( d[j]>d[j+1] ){
					double d2=d[j]; d[j]=d[j+1]; d[j+1]=d2;
					double* x2=x[j+1]; x[j+1]=x[j+2]; x[j+2]=x2;
					changed=TRUE;
      	}
    	}
    	if( !changed ) break;
  	}
	}
	
  //trace ist schlecht für vergleichbarkeit besser auf ersten wert normieren
  tr=d[window-1];

  ofstream foutw( ofilename+".w", ios::out | ios::trunc );
  for( int i=1; i<=window; i++ ) foutw << i << tab << d[window-i] << tab << log( fabs(d[window-i])/tr) << tab << double(i)/double(window) << endl;

  double min=x[1][1], max=x[1][1]; 
  ofstream foutv( ofilename+".v", ios::out | ios::trunc );
  for( int i=1; i<=window; i++ )
    {
      foutv << i << tab;
      for( int j=1; j<=window; j++ )
	{
	  double v=x[j][i];
	  foutv << v;
	  if( v<min ) min=v;
	  if( v>max ) max=v;
	  if( j<window ) foutv << tab;
	}
      foutv << endl;
    }


  // write gp-files

  minmaxRound( min, max, 1.0 );

  gpInfo gpi( ofilename );
  gpi.NewFile();


  gpi.dataFile( ofilename+".w" );
  gpi.Title( "singular values" ).xTitle( "i" ).yTitle( "ln( s_i/s_1 )" );
  gpi.setPlotStyle( LINESPOINTS );
  gpi.pause();
  gpi.setXRange().xRange( 0, window+1 );
  gpi.using1( 1 ).using2( 3 );
  gpi.AppendToFile();

  for( int i=0; i<window; i++ )
    {
      gpi.dataFile( ofilename+".v" );
      gpi.Title( "singular vectors" ).xTitle( "i" ).yTitle( "c" );
      gpi.setPlotStyle( LINESPOINTS );
      gpi.pause();
      gpi.setXRange().xRange( 0, window+1 );
      gpi.setYRange().yRange( min, max );
      gpi.using1( 1 ).using2( i+2 );
      gpi.AppendToFile();
    }
}


void svdrec( const String& ifilename, const string& _vfilename, const String& ofilename, int dimension, int components, boolean scale, boolean lines )
{
  String vfilename = _vfilename + ".v";
  String wfilename = _vfilename + ".w";

  int rows=getFileRows( vfilename );
  int cols=getFileCols( vfilename );

  if( dimension > cols-1 ) exit( 1 );

  dMatrix c(0, dimension, 0, rows-1 );
  // dVector s(1, rows );
  dVector s( 1, rows );

  readFileCols( vfilename, dimension+1, c() );
  readFileCol( wfilename, 1, s() );

  //cout << "s()      " << s()  << endl;
  //cout << "s(0)     " << s(0) << endl;
  //cout << "s(1)     " << s(1) << endl;
  //cout << "&(s[0])  " << &(s[0]) << endl;
  //cout << "&(s[1])  " << &(s[1]) << endl;

  int nt = getFileRows( ifilename );
  dVector v(nt), t(nt);

  readFileColsInc( ifilename, 0, t(), v(), NULL );

  ofstream fout( ofilename, ios::out | ios::trunc );


  for( int i=0; i<nt-rows; i++ )
    {
      fout << t[i];
      for( int d=1; d<=dimension; d++ )
	{
	  int comp = (components==-1) ? d : ((d-1)%components)+1;
	  double sum=0.0;
	  for( int k=0; k<rows; k++ )
	    {
	      sum += c[comp][k]*v[i+k];
	    }
	  if( scale )
	    fout << tab << sum/sqrt(s[d]);
	  else
	    fout << tab << sum;
	}
      fout << endl;
    }

  gpInfo gpi( ofilename );

  gpi.NewFile();

  if( dimension>1 ){
    for( int x=1; x<=dimension; x++ )
      for( int y=x+1; y<=dimension; y++ ) {
	gpi.Title( "SVD reconstruction" ).xTitle( "x"+toString(x) ).yTitle( "x"+toString(y) );
	gpi.setPlotStyle( lines ? LINES : POINTS );
	gpi.pause();
	gpi.using1( x+1 ).using2( y+1 );
	gpi.AppendToFile();
      }
  } else {
	gpi.Title( "SVD-filtered timeseries" ).xTitle( "t").yTitle( "x" );
	gpi.setPlotStyle( LINES );
	gpi.pause();
	gpi.using1( 1 ).using2( 2 );
	gpi.AppendToFile();
    
  }
}







