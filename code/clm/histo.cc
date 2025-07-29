#include "General.h"
#include "Histo.h"

int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  double  resolution=1;
  int     column=2;
  boolean isInteger=FALSE;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "make histogram from input file");
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'r', &resolution, "resolution", "resolution for histogram in percent [1]" );
  getopt.value( 'x', &column, "column", "use column x [2]" );
  getopt.option( 'n', &isInteger, "", "column has only integer values" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;

  histo( ifilename, ofilename, resolution, isInteger, column );

  getopt.writeInfo( ofilename );
  
  if( view ) ViewGpFile( ofilename, FALSE );

  return 0;
}







