#include "General.h"
#include "Fourier.h"



int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  int     n=0;
  boolean view = FALSE;

  ExtGetOpt getopt( argc, argv );
  getopt.descr( "computes the power spectrum of the specified file" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'n', &n, "n", "number of points to use for fourier transform #must be a power of two#default is tzhe biggest power of two less than the number of points" );
  getopt.option( 'v', &view, "", "view output" );

  if( getopt.evaluate() ) return 1;

  fourier( ifilename, ofilename, n );

	getopt.writeInfo( ofilename );
  
  if( view ) ViewGpFile( ofilename, FALSE );


  return 0;
}








