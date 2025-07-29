#include "General.h"
#include "Packdim.h"

int main( int argc, char** argv)
{
  String ifilename;
  String ofilename;
  int delay=-1;
  int dimension=4;
  int bins=200;
  double x1=0.0;
  double x2=0.495;
  boolean view = FALSE;

  ExtGetOpt getopt( argc, argv );
  getopt.descr( "computes conditional probability densities accroding to Packard et al." );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 't', &delay, "delay", "Delay time", TRUE );
  getopt.value( 'd', &dimension, "dimension", "Maximum dimension calculated.", FALSE );
  getopt.value( 'b', &bins, "bins", "Bins for probablity calculation.", FALSE );
  getopt.value( '1', &x1, "value", "x1 halt.", FALSE );
  getopt.value( '2', &x2, "value", "x2 halt.", FALSE );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;

  packdim( ifilename, ofilename, delay, dimension, bins, x1, x2 );

	getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, FALSE );

  return 0;
}








