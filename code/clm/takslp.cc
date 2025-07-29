#include "General.h"
#include "Takslp.h"


int main( int argc, char** argv)
{
  String ifilename;
  String ofilename;
  int minimum = 1;
  boolean view = FALSE;

  ExtGetOpt getopt( argc, argv );
  getopt.descr( "calculates the Takens estimator for various upper epsilon" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'm', &minimum, "minimum", "minimum index value for dimension calculation"  );
  getopt.option( 'v', &view, "", "view output" );

  if( getopt.evaluate() ) return 1;


  takslp( ifilename, ofilename, minimum );

	getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, FALSE );


  return 0;
}















