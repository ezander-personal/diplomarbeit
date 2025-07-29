#include "General.h"
#include "Subtrend.h"

int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "subtracts a linear trend from a time series" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;


  subtrend( ifilename, ofilename );

  getopt.writeInfo( ofilename );
  
  if( view ) ViewGpFile( ofilename, FALSE );


  return 0;
}

