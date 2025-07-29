#include "General.h"
#include "Takdim.h"


int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  double  epsilon = -1;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "calculates the dimension (slope) from the correlation integral#via takens estiomator for the specified epsilon" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'e', &epsilon, "epsilon", "maximal relativ radius (logarithm)", TRUE );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;


  takdim( ifilename, ofilename, epsilon );

	getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, TRUE );


  return 0;
}








