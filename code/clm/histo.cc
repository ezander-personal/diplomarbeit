#include "General.h"
#include "Histo.h"

int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  double  resolution=1;
  int     column=2;
  int    delay=0;
  boolean isInteger=FALSE;
  boolean randomMode=FALSE;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "make histogram from input file");
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'r', &resolution, "resolution", "resolution for histogram in percent [1]" );
  getopt.value( 'x', &column, "column", "use column x [2]" );
  getopt.value( 't', &delay, "delay", "if not zero, create a 2-dim histogram with delay t [0]" );
  getopt.option( 'n', &isInteger, "", "column has only integer values" );
  getopt.option( 'm', &randomMode, "", "use random mode" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;

  if( !delay )
    histo( ifilename, ofilename, resolution, isInteger, column, randomMode );
  else
    histo2d( ifilename, ofilename, resolution, isInteger, column, delay );

  getopt.writeInfo( ofilename );
  
  if( view ) ViewGpFile( ofilename, FALSE );

  return 0;
}







