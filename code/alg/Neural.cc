#include "General.h"


/*
static dMatrix hiddenWeights;
static dVector hiddenBiases;
static dVector outputWeights;
static double  outputBias;

static dMatrix hiddenWeightsP;
static dVector hiddenBiasesP;
static dVector outputWeightsP;
static double  outputBiasP;

static double* input;
static double* hiddenIn;
static double* hiddenOut;
static double* outputs;
*/

/*
  1.)
  hiddenWeights.size(inputUnits, hiddenUnits);
  hiddenBiases.size( hiddenUnits );
  outputWeights.size( hiddenUnits );
  
  fill with random vars 
  
  2.) calculate outputs
  for output k (k=1..trainingSets)
    hiddenIn(j) = hiddenBiases(j) + SUM[i=1..inputUnits]{ hiddenWeights(i,j)*input(k+inputUnits-i) }
  #define O(x) = 0.5*(1.0+tanh(x))
    hiddenOut(j) = O(hiddenIn(j))

    outputs(k) = outputBias + SUM(j=1..hiddenUnits) { outputWeights(j) * hiddenOut(j) }

  3.) calculate error
    Q = SUM(1..trainingSets) { (input(k) - output(k))^2 }

  


  */


void neural( const String& ifilename, const String& ofilename, int inputUnits, int hidden, int trainingSets, int max_training,  double learning_rate, double momentum, bool random)
{
  return;



  int rows = getFileRows( ifilename );
  dVector x(rows), t(rows);
  
  if( readFileColsInc( ifilename, 0, t(), x(), NULL ) ) exit( 1 );
  

  


  
  ofstream fout( ofilename, ios::out | ios::trunc );
  /*
  for( int i=0; i<rows; i++ )
    fout << t[i] << tab << x[i] << tab << re[i] << tab << im[i] << tab << phi[i] << endl;
    */
  fout.close();
  
  gpInfo gpi( ofilename );
  gpi.using1( 1 ). using2( 2 );
  gpi.Title( "fourier spectrum" ).xTitle( "w" ).yTitle( "log P(w)" );
  gpi.setXRange().xRange( 0.0, t[rows-1] );
  gpi.setPlotStyle( LINES ).pause();
  gpi.NewFile();
  gpi.AppendToFile();
}























