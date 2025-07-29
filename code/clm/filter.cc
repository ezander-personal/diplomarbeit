#include "General.h"
#include "Filter.h"


int main( int argc, char** argv)
{
  String  ifilename;
  String  ofilename;
  double  lowerFreq = 0.0;
  double  upperFreq = 1.5;
  int     order = 50;
  int     window = 0;
  String  strWindow = "hamming";
  String  strWindows[] = {"rect", "bessel", "hamming", "blackman" };
  boolean view = FALSE;


  ExtGetOpt getopt( argc, argv );
  getopt.value( 'i', &ifilename, "filename", NULL, TRUE );
  getopt.value( 'o', &ofilename, "filename", NULL, TRUE );
  getopt.value( 'l', &lowerFreq, "lower", "lower limiting frequency [0Hz]", FALSE );
  getopt.value( 'u', &upperFreq, "upper", "lower limiting frequency [1.5Hz]", FALSE );
  getopt.value( 'r', &order, "order", "filter order [50]", FALSE );
  getopt.value( 'w', &strWindow, "window", "Rect, Bessel, Hamming, Blackman [hamming]", FALSE );
  getopt.option( 'v', &view, "", "view output" );

  if( getopt.evaluate( FALSE ) ) return 1;
 
  strWindow.downcase();
  for( int i=0; i<4; i++ )
    {
      if( strWindows[i].index( strWindow ) == 0 )
	{
	  window = i+1;
	  break;
	}
    }

  if( window == 0 ) 
    {
      getopt.error( TRUE );
      return 1;
    }


  filter( ifilename, ofilename, lowerFreq, upperFreq, order, window );

	getopt.writeInfo( ofilename );

  if( view ) ViewGpFile( ofilename, FALSE );  


  return 0;
}







