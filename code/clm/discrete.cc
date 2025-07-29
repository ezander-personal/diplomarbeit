#include "General.h"
#include "Discrete.h"

int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  double  level = 5.0;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "discretize time-series");
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'l', &level, "level", "discretization level in percent [5%]" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;


  discretize( ifilename, ofilename, level );

  getopt.writeInfo( ofilename );
  
  if( view ) ViewGpFile( ofilename, FALSE );


  return 0;
}







