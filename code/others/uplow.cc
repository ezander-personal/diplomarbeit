#include <stream.h>
#include <stdio.h>
#include <ctype.h>

int main( int argc, char* argv[])
{
  if( argc==1)
    {
      cerr << "usage: uplow file [files ...]" << endl;
      exit(1);
    }

  char newName[128];
  for( int i=1;i<argc;i++)
    {
      const char* oldName = argv[i];
      strcpy( newName, oldName );
      
  for( unsigned int j=0; j<strlen(newName);j++ )
	{
		if( j==0 )
		  { if( islower( newName[j] ) ) newName[j]-=32; }
		else
		  { if( isupper( newName[j] ) ) newName[j]+=32; }
	}

      rename( oldName, newName );
    }
}
