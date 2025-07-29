#include "General.h"
#include "Corrslp.h"


int main( int argc, char** argv)
{
  String ifilename;
  String ofilename;
  double slope = 5;
  double min = -100;
  double max = 0;
  double radius = -1;
  boolean units = FALSE;
  boolean nolog = FALSE;
  boolean view = FALSE;

  ExtGetOpt getopt( argc, argv );
  getopt.descr( "calculates the local slopes of the correlation integral" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'n', &slope, "slope-points", "specifies the number of points used to calculate the slope [5]" );
  getopt.value( 'm', &min, "min", "minimum radius to begin slope calculation with [-100]" );
  getopt.value( 'a', &max, "max", "maximum radius for slope calculation from end [0]" );
  getopt.value( 'r', &radius, "radius", "use hypercube scaling with radius [-1=dont use]" );
  getopt.option( 'u', &units, "", "use real units" );
  getopt.option( 'l', &nolog, "", "dont use logarithmic slope calculation" );
  getopt.option( 'v', &view, "", "view output" );

  if( getopt.evaluate() ) return 1;


  corrslp( ifilename, ofilename, slope, min, max, units, nolog, radius );

	getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, FALSE );


  return 0;
}












