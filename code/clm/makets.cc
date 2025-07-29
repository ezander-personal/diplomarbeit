#include "General.h"
#include "Makets.h"

int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  int     points = -1;
  int     nDiff = 1;
  int     axis = -1;
  double  time = 0.01;
  boolean normalize = FALSE;
  boolean ignore = FALSE;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "make 2-column time-series-file from input file");
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'x', &axis, "column", "use column 1,2,3,... for creating the time series [1 or 2]" );
  getopt.value( 'n', &nDiff, "n'th", "use only every n'th points" );
  getopt.value( 'p', &points, "points", "limit output to max. p points" );
  getopt.value( 't', &time, "sampling time", "specify sampling time, when not included in input file [0.01]" );
  getopt.option( 'g', &ignore, "", "ignore first column for time spec" );
  getopt.option( 'r', &normalize, "", "normalize time series to mean zero and variance one" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;


  makets( ifilename, ofilename, axis-1, nDiff, points, time, ignore, normalize );

	getopt.writeInfo( ofilename );
  
  if( view ) ViewGpFile( ofilename, FALSE );


  return 0;
}







