#include "General.h"

#include "Voss.h"
#include <stdio.h>


void voss( const String& ifilename, const String& ofilename, boolean useheartbeat )
{
  FILE* fp = fopen( (const char*)ifilename, "r" );
  if( !fp )
  {
  	cerr << "Error opening file " << ifilename << endl;
	  exit(1);
  }

  long start, dauer;
  fscanf( fp,"%ld\n %ld\n", &start, &dauer );
  
  int channels = 2;
  int channel = 0;
  if( useheartbeat )
  	channel = 1;
  	
  double sf = 100.0; // sampling frequency
  
  
  long laenge = dauer / (channels*2);
  double time = start / (2.0 * channels* sf * 60.0 );
  
  ofstream fout( ofilename, ios::out | ios::trunc );
  
  for( int i=0; i<laenge; i++ )
    {
      for( int j=0; j<channels; j++ )
	{
	  unsigned int byte1 = fgetc( fp );
	  unsigned int byte2 = fgetc( fp );
	  
	  if( j==channel )
	    {
	      double sig = byte1*16.0 + byte2/16.0 - 2048.0;
	      fout << time << tab << sig << endl;
	      time += 1.0 / sf;
	    }
	}
    }
  
  fout.close();
  fclose( fp );

  
  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "vossschulte-data" ).xTitle( "t" ).yTitle("x");
  gpi.setPlotStyle( LINES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
}












