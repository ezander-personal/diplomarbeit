#include "General.h"
#include "Functions.h"
#include "Create.h"


int main( int argc, char** argv )
{
  String filename;
  String type_name;
  int  points = 10000;
  int dimension=3;
  double delay=-1;
  int type=-1;
  int nDiff=1;

  boolean view=FALSE;

  ExtGetOpt getopt( argc, argv );
  getopt.descr( "integrate or iterate the desired system" );
  getopt.value( 't', &type_name, "type", "roessler, lorenz, henon, torus, noise", TRUE );
  getopt.value( 'o', &filename, "filename", NULL, TRUE );
  getopt.value( 'p', &points, "points", "the number of points to compute [10000]" );
  getopt.value( 'd', &delay, "delay", "if delay is chosen too large, a floating point exception may occur" );
  getopt.value( 'n', &nDiff, "diff", "save only every diff'th points" );
  getopt.option( 'v', &view, "", "view output" );
  
  if( getopt.evaluate() ) return 1;


  type = GetType( type_name );
  if (type==-1)
  {
    cerr << "Error: type not found: " << type_name << endl;
    exit( 1 );
  }


  create( filename, points, dimension, delay, type, nDiff );

	getopt.writeInfo( filename );
 
  if( view ) ViewGpFile( filename, FALSE );
  

  return 0;
}







