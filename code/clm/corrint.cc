
#include "General.h"
#include "Corrint.h"



int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  int     lagTime = -1;
  int     maxDim = -1;
  int     refDist = 1;
  int     ignore = -1;
  int     points = -1;
  int     q = 2;
  int     expansionFac = 6;
  int     binScales = 10;
  boolean constWindow = FALSE;
  boolean euclidianNorm = FALSE;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "computes the correlation integral from the specified time-series" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 't', &lagTime, "lagtime", NULL, TRUE );
  getopt.value( 'd', &maxDim, "maxdim", "maximum embedding dimension #when maxdim is zero all columns are used#lagtime may be anything in this case", TRUE );
  getopt.value( 'r', &refDist, "dist", "(temporal) distance of points in the second sum" );
  getopt.value( 'l', &ignore, "ignore", "points to ignore because of temporal correlation" );
  getopt.value( 'p', &points, "refpoints", "max. number of points in the first sum" );
  getopt.value( 'q', &q, "gen. dimen.", "index of gen. dimension (not implemented) [2]" );
  getopt.value( 'e', &expansionFac, "expansion-fac", "expansion factor[6]" );
  getopt.value( 'b', &binScales, "bin-scales", "binary scales [10]" );
  getopt.option( 'w', &constWindow, "", "use 't' as window length instead of lad time (not imp.)" );
  getopt.option( 'n', &euclidianNorm, "", "use euclidian norm instead of maximums norm" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;


  corrint( ifilename, ofilename, maxDim, lagTime, refDist, ignore, points, q, expansionFac, binScales, constWindow, euclidianNorm );

	getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, FALSE );


  return 0;
}








