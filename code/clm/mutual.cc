#include "General.h"
#include "Mutual.h"

int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  double  epsilon = 2.0;
  int     max_time = -1;
  int     min_time = 3;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "calculate mutual information");
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 't', &max_time, "max_time", "max time to calculate mutual information for [all]" );
  getopt.value( 'm', &min_time, "min_time", "min time to calculate mutual information for [5]" );
  getopt.value( 'e', &epsilon, "epsilon", "size of bins in percent of x-variance [2.0]" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;


  mutual( ifilename, ofilename, epsilon, min_time, max_time );


  getopt.writeInfo( ofilename );

  
  if( view ) ViewGpFile( ofilename, FALSE );

  return 0;
}







