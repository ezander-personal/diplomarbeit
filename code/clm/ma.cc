#include "General.h"
#include "Ma.h"

#include "ExtFile.h"
#include <stream.h>

int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  int     width = -1;
  boolean gaussian = FALSE;
  boolean view = FALSE;

  ExtGetOpt getopt( argc, argv );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'w', &width, "width", NULL, TRUE );
  getopt.option( 'g', &gaussian, "(not implemented)", NULL );
  getopt.option( 'v', &view, "", "view output" );

  
  if( getopt.evaluate() ) return 1;


  ma( ifilename, ofilename, width, gaussian );

	getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, FALSE );  


  return 0;
}








