#include "General.h"
#include "Poinc.h"

int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  int     axis = -1;
  double  crossVal = 0.0;
  char    cross='b';
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "make a poincare-plot of n-dimensional input-file");
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'x', &axis, "column", "use column 1,2,3,... for creating the plot [2]" );
  getopt.value( 'r', &crossVal, "value", "when 'axis' crosses this value a points is generated [0]" );
  getopt.value( 'c', &cross, "{p|n|b}", "points are only recorded, when the trajectory #crosses in positive, negative or both directions [b]" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;


  poinc( ifilename, ofilename, axis, crossVal, (cross=='b'||cross=='p'), (cross=='b'||cross=='n') );

	getopt.writeInfo( ofilename );
  
  if( view ) ViewGpFile( ofilename, FALSE );


  return 0;
}







