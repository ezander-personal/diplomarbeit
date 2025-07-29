#include "General.h"
#include "Corrslp.h"


int main( int argc, char** argv)
{
  String ifilename;
  String ofilename;
  double slope = 5;
  double min = -100;
  boolean units = FALSE;
  boolean view = FALSE;

  ExtGetOpt getopt( argc, argv );
  getopt.descr( "calculates the local slopes of the correlation integral" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'n', &slope, "slope-points", "specifies the number of points used to calculate the slope [5]" );
  getopt.value( 'm', &min, "min", "minimum radius to begin slope calculation with [-100]" );
  getopt.option( 'u', &units, "", "use real units" );
  getopt.option( 'v', &view, "", "view output" );

  if( getopt.evaluate() ) return 1;


  corrslp( ifilename, ofilename, slope, min, units );

	getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, FALSE );


  return 0;
}








