#include "General.h"
#include "Stat.h"

int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  double  resolution=1.0;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "make stationarity test from input file");
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'r', &resolution, "resolution", "resolution for histogram in percent [1]" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;

  stat( ifilename, ofilename, resolution );

  getopt.writeInfo( ofilename );
  
  if( view ) ViewGpFile( ofilename, FALSE );

  return 0;
}







