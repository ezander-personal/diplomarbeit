#include "General.h"
#include "Surrogate.h"

int main( int argc, char** argv)
{
  String ifilename;
  String ofilename;
  char type='f';
  int number=1;
  boolean amplitudeAdj = FALSE;
  boolean view = FALSE;

  ExtGetOpt getopt( argc, argv );
  getopt.descr( "computes surrogates of the specified time series" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'n', &number, "number", "number of surrogate time series to create [1]#index is appended to the filename", FALSE );
  getopt.value( 't', &type, "{f|w}", "type of surrogate date: FT or WFT (windowed) [f]" );
  getopt.option( 'a', &amplitudeAdj, "", "amplitude adjusted FT resp. WFT (AAFT resp AAWFT)" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;

  surrogate( ifilename, ofilename, type, amplitudeAdj, number );

	getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, FALSE );

  return 0;
}








