#include "General.h"
#include "Rects.h"

int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  int     lag = -1;
  int     dimension = -1;
  boolean lines = FALSE;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "reconstructs an attractor-portrait using delay-coordinates" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 't', &lag, "lag_time", "lag time between delay coordinates", TRUE );
  getopt.value( 'd', &dimension, "dimension", "embedding dimension", TRUE );
  getopt.option( 'l', &lines, "", "connect with lines (only for output)" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;


  rects( ifilename, ofilename, lag, dimension, lines );

	getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, TRUE );  


  return 0;
}










