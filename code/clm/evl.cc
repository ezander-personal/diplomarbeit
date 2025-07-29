#include "General.h"
#include "Evl.h"



int main( int argc, char** argv)
{
  String ifilename;
  char sortBy='t';
  int column=2;
  int compare=COMPARE_TYPE;
  boolean shortDisp=FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.descr( "computes several characteristics of the input file to standard output" );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'c', &column, "column", "specifies the column of the input file (1,2,...) [2]" );
  getopt.value( 's', &sortBy, "{p|t|v}", "sort by position (p), type (t), value(v) [unsorted-p]");
  getopt.option( 'h', &shortDisp, "", "short output" );
  
  if( getopt.evaluate() ) return 1;


  switch( sortBy )
    {
    case 't': compare = COMPARE_TYPE; break;
    case 'p': compare = COMPARE_POS; break;
    case 'v': compare = COMPARE_VALUE; break;
    default: return 1;
    }


  evl( ifilename, column-1, compare, shortDisp );


  return 0;
}









