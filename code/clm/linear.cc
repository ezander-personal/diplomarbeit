#include "General.h"
#include "Linear.h"

int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  int     maxLength = 10;
  int     points = -1;
  boolean view = FALSE;

  ExtGetOpt getopt( argc, argv );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'm', &maxLength, "max. length", "max. length of trajectories tested for linearity [10]" );
  getopt.value( 'p', &points, "points", "number of datapoints used for testing [all]" );
  getopt.option( 'v', &view, "", "view output" );

  
  if( getopt.evaluate() ) return 1;


  linear( ifilename, ofilename, maxLength, points );

	getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, FALSE );  


  return 0;
}









