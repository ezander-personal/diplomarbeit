#include "General.h"
#include "Neural.h"


int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  int     inputs = 2;
  int     hidden = 4;
  int     samples = 16;
  int     max_training = 50;
  double  learning_rate = 0.3;
  double  momentum = 0.1;
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'm', &inputs, "inputs", "the number of input units" );
  getopt.value( 'h', &hidden, "hidden", "the number of hidden units" );
  getopt.value( 's', &samples, "samples", "the number of training samples" );
  getopt.value( 'l', &learning_rate, "learning_rate", "learning rate 0..1 [0.3]" );
  getopt.value( 'l', &momentum, "momentum", "momentum 0..1 [0.1]" );
  getopt.option( 'v', &view, "", "view output" );

  if( getopt.evaluate( FALSE ) ) return 1;
 
  neural( ifilename, ofilename, inputs, hidden, samples, max_training, learning_rate, momentum, FALSE);

  getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, FALSE );  

  return 0;
}









