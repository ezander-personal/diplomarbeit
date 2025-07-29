#include "General.h"
#include "Fuell.h"




int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  int     tau_a = -1;
  int     tau_e = -1;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "computes the difference between fuell-factors for increasing embedding dimensions (s. Buzug)" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'a', &tau_a, "tau_a", NULL, TRUE );
  getopt.value( 'e', &tau_e, "tau_e", NULL, TRUE );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;


  fuelld( ifilename, ofilename, tau_a, tau_e );

	getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, FALSE );


  return 0;
}








