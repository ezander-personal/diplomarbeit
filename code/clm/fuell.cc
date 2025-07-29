#include "General.h"
#include "Fuell.h"


int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  int     maxDim = -1;
  int     minDim = 2;
  int     maxTau = -1;
  int     count = 500;
  boolean view = FALSE;

  ExtGetOpt getopt( argc, argv );
  getopt.descr( "computes the fuell-factor (s. Buzug) for the time series" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 't', &maxTau, "maxtau", NULL, TRUE );
  getopt.value( 'd', &maxDim, "maxdim", "maximum embedding dimension", TRUE );
  getopt.value( 'p', &count, "par", "number of paralellepipeds [500]" );
  getopt.option( 'v', &view, "", "view output" );

  if( getopt.evaluate() ) return 1;


  fuell( ifilename, ofilename, maxDim, minDim, maxTau, count );

	getopt.writeInfo( ofilename );
  
  if( view ) ViewGpFile( ofilename, FALSE );


  return 0;
}








