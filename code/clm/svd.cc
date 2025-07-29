#include "General.h"
#include "Svd.h"



int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  int     window=25;
	boolean nosort = FALSE;
  boolean view = FALSE;

  ExtGetOpt getopt( argc, argv );
  getopt.descr( "computes singular values and singular vectors from the time series (s. Broomhead and King)" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'w', &window, "window", "window length for SVD [25]" );
  getopt.option( 'n', &nosort, "", "dont sort eigenvalues and eigenvectors" );  
  getopt.option( 'v', &view, "", "view output" );

  if( getopt.evaluate() ) return 1;

  svd( ifilename, ofilename, window, nosort );

	getopt.writeInfo( ofilename );
  
  if( view ) ViewGpFile( ofilename, FALSE );

  return 0;
}








