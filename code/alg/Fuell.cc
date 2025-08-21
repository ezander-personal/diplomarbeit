#include <stdlib.h>
#include <math.h>

#include "General.h"
#include "Statistical.h"


#include "nr.h"

  // für verschiedene Einbettungsdimensionen d und eine jeweils konstante Menge
  // Verzögerungszeiten t aus (t1, t2, ... tn ) wird jeweils n mal folgendes
  // gemacht
  //
  //   aus der Zeitreihe werden d Vektoren v1..vd zufällig ausgewählt und das Volumen
  //   das dieses Paralellepipeds aus det(v1,...,vd) bestimmt
  //   diese Volumina werden aufsummiert
  //
  // das Volumen wird durch das Volumen des den Attraktor umfassenden Hyperkubus
  // geteilt (und evtl. logarithmiert)


void fuell( const String& ifilename, const String& ofilename, int maxDim, int minDim, int maxTau, int count )
{
  int rows=getFileRows( ifilename );
  dVector x(rows);
  if( readFileCol( ifilename, 1, x() ) ) exit( 1 );

  double min,max, diff, ncube;
  getMinMax( x, min, max );
  diff=ncube=max-min;
  
  if( count<1 ) count=500;

  dMatrix fuellMat( minDim, maxDim, 1, maxTau );
  
  for( int dim=minDim; dim<=maxDim; dim++ )
    {
      dMatrix mat(1,dim,1,dim );
      

      int n=rows-(dim-1)*maxTau;
      
      dVector vol( 1,  maxTau );
      for( int tau=1; tau<=maxTau; tau++ ) vol[tau] =.0;

      for( int c=0; c<count; c++ )
	{
	  int k0 = rand() % n, k[dim]; 
	  for( int i=0; i<dim; i++ )
	    k[i]=rand() % n;

	  for( int tau=1; tau<=maxTau; tau++ )
	    {
	      for( int i=1; i<=dim; i++ )
		{
		  double *x1 = x()+k[i-1], *x0 = x()+k0;

		  for( int j=1; j<=dim; j++ )
		    {
		      mat[i][j]=*x1-*x0;
		      x1+=tau; x0+=tau;
		    }
		}
	      
	      vol[tau] += fabs( determ( mat, dim ) );
	    }
	  for( int tau=1; tau<=maxTau; tau++ )
	    fuellMat[dim][tau] = log( vol[tau]/ncube/count );

	  if( c % 100 == 0 )
	    cerr << car << dim << " - " << c << " / " << count << "       ";
	}
      
      ncube*=diff;
    }

  ofstream fout( ofilename, ios::out | ios::trunc );  
  for( int tau=1; tau<=maxTau; tau++ )
    {
      fout << tau;
      for( int dim=minDim; dim<=maxDim; dim++ )
	{
	  fout << tab << fuellMat[dim][tau];
	}
      fout << endl;
    }

  fout.close();
      
  
  gpInfo gpi( ofilename );


  gpi.Title( "fill-factor" ).xTitle( "d" ).yTitle( "F_d" );
  gpi.setPlotStyle( LINES );
  gpi.pause();
  gpi.using1( 1 ).using2( 2, maxDim-minDim+2 );

  gpi.NewFile();
  gpi.AppendToFile();
}


void fuelld( const String& ifilename, const String& ofilename, int tau_a, int tau_e )
{
  int rows = getFileRows( ifilename );
  int cols = getFileCols( ifilename );
  int maxDim = cols-1;
  
  dVector t(rows);
  if( readFileCol( ifilename, 0, t(), cols ) ) exit( 1 );


  dMatrix x(0, maxDim-1, 0, rows-1 );
  
  for( int d=0; d<maxDim; d++ )
    {
      if( readFileCol( ifilename, d+1, x[d], cols ) ) exit( 1 );
    }


  ofstream fout( ofilename, ios::out | ios::trunc );


  for( int d=0; d<maxDim-1; d++ )
    {
      double *px1 = x[d]+tau_a;
      double *px2 = x[d+1]+tau_a;
      
      fout << d+2 << tab;
      fout << difference( px1, px2, tau_e-tau_a ) << tab;
      fout << correlationCoefficient( px1, px2, tau_e-tau_a ) << endl;
    }
  
  fout.close();
  

  gpInfo gpi( ofilename );
  gpi.NewFile();

  gpi.Title( "fill-factor" ).xTitle( "d" ).yTitle( "f_d" );
  gpi.setPlotStyle( LINESPOINTS );
  gpi.pause();
  gpi.setXRange().xRange( 0, maxDim );
  gpi.using1( 1 ).using2( 2 );
  gpi.AppendToFile();

  gpi.Title( "correlation-coefficient" ).yTitle( "c_d" );
  gpi.using1( 1 ).using2( 3 );
  gpi.AppendToFile();
}








