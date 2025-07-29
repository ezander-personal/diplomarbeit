// ;-*-C++-*-
// tells emacs to use C++-mode instead of C-mode


#ifndef __GPFILE_H__
#define __GPFILE_H__

#define MAX_DATA_FILES 2

#define LOGSCALE_X 1
#define LOGSCALE_Y 2


#define ERRORBARS    1
#define LINES        2
#define POINTS       4
#define LINESPOINTS  8
#define IMPULSES    16

#define LATEX_OUTPUT 1
#define PS_OUTPUT    2
#define SET_X_RANGE  4
#define SET_Y_RANGE  8
#define SET_Z_RANGE 16
#define PLOT3D      32
#define PAUSE       64

#include <iostream.h>

class gpInfo
{
  String gpfilename;
  String datafilename[ MAX_DATA_FILES ];
  String outputfile;
  String title;
  String xtitle;
  String ytitle;

  
  int plotStyle;
  int axisStyle;
  int options;

  int plotColor;

  int axis[6];

  double xrange[2];
  double yrange[2];
  double zrange[2];


  void writeGpTitle( ofstream& gpout );
  void writeGpTerminal( ofstream& gpout );
  void writeGpScaleRange( ofstream& gpout );
  void writeGpParametric( ofstream& gpout );
  void writeGpPlottingStuff( ofstream& gpout );


public:
  gpInfo( const char* _filename);
  void reset();


  gpInfo& dataFile( const String& filename, int n=0 ) { datafilename[n] = filename; return *this; }

  gpInfo& using1( int n ) { return using1( n, n ); }
  gpInfo& using2( int n ) { return using2( n, n ); }
  gpInfo& using3( int n ) { return using3( n, n ); }
  gpInfo& using1( int n1, int n2 ) { axis[0]=n1; axis[3]=n2; return *this; }
  gpInfo& using2( int n1, int n2 ) { axis[1]=n1; axis[4]=n2; return *this; }
  gpInfo& using3( int n1, int n2 ) { axis[2]=n1; axis[5]=n2; return *this; }
  
  gpInfo& xRange( double min, double max ) { xrange[0]=min; xrange[1]=max; return* this; }
  gpInfo& yRange( double min, double max ) { yrange[0]=min; yrange[1]=max; return* this; }
  gpInfo& zRange( double min, double max ) { zrange[0]=min; zrange[1]=max; return* this; }

  gpInfo& pause() { options |= PAUSE; return* this; }

  gpInfo& color( int _color ) { plotColor = _color; return *this; }

  gpInfo& setXRange() { options |= SET_X_RANGE; return* this; }
  gpInfo& setYRange() { options |= SET_Y_RANGE; return* this; }
  gpInfo& setZRange() { options |= SET_Z_RANGE; return* this; }

  gpInfo& setPlotStyle( int style ) { plotStyle = style; return *this; }
  gpInfo& addPlotStyle( int style ) { plotStyle |= style; return *this; }

  gpInfo& setOptions( int option ) { options = option; return *this; }
  gpInfo& addOption( int option ) { options |= option; return *this; }

  gpInfo& logScale() { axisStyle |= LOGSCALE_X | LOGSCALE_Y; return *this; }
  gpInfo& logScaleX() { axisStyle |= LOGSCALE_X; return *this; }
  gpInfo& logScaleY() { axisStyle |= LOGSCALE_Y; return *this; }
  gpInfo& noLogScale() { axisStyle &= ~(LOGSCALE_X | LOGSCALE_Y); return *this; }

  gpInfo& Title( const char* str ) { title = str; return* this; }
  gpInfo& xTitle( const char* str ) { xtitle = str; return* this; }
  gpInfo& yTitle( const char* str ) { ytitle = str; return* this; }


  int NewFile();
  int AppendToFile();
};




int WriteGpFile( const char* filename, const char* title, const char* xlabel, const char* ylabel, int dimension, int isDiscrete );

int ViewGpFile( const char* filename, boolean smallPoints );



#endif //  __GPFILE_H__







