#include "General.h"
#include "Noise.h"

int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  double  level = 5.0;
  int     type = 0;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "add noise to time-series");
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'l', &level, "level", "noise level in percent [5%]" );
  // getopt.value( 't', &type, "{}", "type of noise to add (???)" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;


  noise( ifilename, ofilename, type , level );

	getopt.writeInfo( ofilename );
  
  if( view ) ViewGpFile( ofilename, FALSE );


  return 0;
}







