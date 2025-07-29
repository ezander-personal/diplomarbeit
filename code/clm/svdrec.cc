#include "General.h"
#include "Svd.h"



int main( int argc, char** argv)
{
  String  ifilename;
  String  vfilename;
  String  ofilename;
  int     dimension=-1;
  int     components=-1;
  boolean scale = FALSE;
  boolean lines = FALSE;
  boolean view = FALSE;

  ExtGetOpt getopt( argc, argv );
  getopt.descr( "reconstructs an attractor-portrait using singular vectors obtained from 'svd'" );
  getopt.value( 'i', &ifilename, "filename", "file containing the time series ", TRUE );
  getopt.value( 's', &vfilename, "filename", "file containing the svd vectors (without the extension '.v')", TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'd', &dimension, "dimension", "embedding dimension for the reconstruction", TRUE );
  getopt.value( 'c', &components, "components", "principal components to use for reembedding [-1=all] n.i.", FALSE );
  getopt.option( 'a', &scale, "", "scale direction i with sqrt(svd(i))" );
  getopt.option( 'l', &lines, "", "connect with lines (graph. output)" );
  getopt.option( 'v', &view, "", "view output" );

  if( getopt.evaluate() ) return 1;

  svdrec( ifilename, vfilename, ofilename, dimension, components, scale, lines );

	getopt.writeInfo( ofilename );
  
  if( view ) ViewGpFile( ofilename, TRUE );


  return 0;
}











