#include "General.h"
#include "Corrdim.h"


int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  double  begin = -1;
  double  end = -1;
  boolean units = 0;
  double  scaleExp = 0;
  double radius = -1;
  int  minDiff = 40;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "calculates the dimension (slope) from the correlation integral over the specified range" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'b', &begin, "begin", "start of slope calculation [-1]" );
  getopt.value( 'e', &end, "end", "end of slope calculation [-1]#if begin and/or end are equal to -1, they are chosen#so, that the correlation-coefficient is minimal" );
  getopt.value( 's', &scaleExp, "scaleExp", "scale exponent for automatic range calculation [0]" );
  getopt.value( 'r', &radius, "radius", "use hypercube scaling with radius [-1=dont use]" );
  getopt.value( 'm', &minDiff, "minDiff", "minmum range [40]" );
  getopt.option( 'u', &units, "", "use real units" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;


  corrdim( ifilename, ofilename, begin, end, units, scaleExp, radius, minDiff );

  getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, FALSE );


  return 0;
}








