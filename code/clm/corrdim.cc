#include "General.h"
#include "Corrdim.h"


int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  double  begin = -1;
  double  end = -1;
  boolean units = 0;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "calculates the dimension (slope) from the correlation integral over the specified range" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'b', &begin, "begin", "start of slope calculation", TRUE );
  getopt.value( 'e', &end, "end", "end of slope calculation#if begin and/or end are equal to -1, they are chosen#so, that the correlation-coefficient is minimal", TRUE );
  getopt.option( 'u', &units, "", "use real units" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;


  corrdim( ifilename, ofilename, begin, end, units );

  getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, TRUE );


  return 0;
}








