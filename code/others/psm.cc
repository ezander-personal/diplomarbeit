#include <stream.h>
#include <fstream.h>
#include <String.h>

const char tab = '\t';

int page = 0;
char buffer[2048];

typedef int boolean;

const int TRUE=1;
const int FALSE=0;


void writeToPostScript( const char* file, boolean writeProlog, boolean writeTrailer )
{
  cerr << "(" << file << ") ";

  ifstream fin( file );
  String str;

  int isInProlog=TRUE;
  int isInTrailer=FALSE;

  while( !fin.eof() )
    {
      fin.getline( buffer, sizeof(buffer) );
      str=buffer;

      if( str.contains( "%%Trailer" ) ) 
	{
	  if( writeTrailer ) cerr << "[Trlr] " << endl;
	  isInTrailer=TRUE;
	}

      if( isInProlog )
	{
	  if( writeProlog ) cout << str << endl;
	  if( str.contains( "%%EndProlog" ) ) 
	    {
	      if( writeProlog ) cerr << "[Prlg] ";
	      isInProlog=FALSE;
	    }
	}
      else if( isInTrailer )
	{
	  if( !writeTrailer ) break;
	   
	  if( str.contains( "%%Pages" ) )
	    cout << "%%Pages: " << page << endl;
	  else
	    cout << str << endl;
	}
      else
	{
	  if( str.contains( "%%Page" ) )
	    {
	      page++;
	      cout << "%%Page: " << page << " " << page << endl;
	      cerr << "[" << page << "] ";
	    }
	  else
	    cout << str << endl;
	}

    }
}

int main( int argc, char* argv[])
{
  if( argc==1)
    {
      cerr << "usage: psm file [files ...]" << endl;
      exit(1);
    }

  for( int arg=1; arg<argc; arg++ )
    {
      writeToPostScript( argv[arg], arg==1, arg==argc-1 );
    }


}
