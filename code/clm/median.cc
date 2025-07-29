#include "General.h"
#include "Median.h"


int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  int     order = 5;
  int     passes = 1;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'r', &order, "order", "filter order [5]", FALSE );
  getopt.value( 'p', &passes, "passes", "[1]", FALSE );
  getopt.option( 'v', &view, "", "view output" );

  if( getopt.evaluate( FALSE ) ) return 1;
 

  median( ifilename, ofilename, order, passes );

	getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, FALSE );  


  return 0;
}







