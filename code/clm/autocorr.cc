#include "General.h"
#include "Autocorr.h"

int main( int argc, char** argv)
{
  String ifilename;
  String ofilename;
  int maxtau=-1;
  boolean correction=FALSE;
  boolean view = FALSE;

  ExtGetOpt getopt( argc, argv );
  getopt.descr( "computes the autocorrelation function for the specified time series" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 't', &maxtau, "maxtau", NULL, TRUE );
  getopt.option( 'c', &correction, "", "apply correction factor" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;

  autocorr( ifilename, ofilename, maxtau, correction );

	getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, FALSE );

  return 0;
}








