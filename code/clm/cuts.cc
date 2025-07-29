#include "General.h"
#include "Cuts.h"

int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  int     length = -1;
  int     diff = -1;
  int     max = -1;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "cuts a time series in multiple shorter time series");
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'l', &length, "length", "the length of the new time series", TRUE );
  getopt.value( 'd', &diff, "diff", "the difference between [length/2]" );
  getopt.value( 'm', &diff, "max", "maximum number of produced time series " );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;

  cuts( ifilename, ofilename, length, diff, max );

  getopt.writeInfo( ofilename );
  
  if( view ) ViewGpFile( ofilename, FALSE );


  return 0;
}







