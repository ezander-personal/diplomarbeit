// ;-*-C++-*-
// tells emacs to use C++-mode instead of C-mode


#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

// class vector;

#ifdef __VECTOR_H__
typedef void (*vectorFunction)( const vector&, vector&, const vector& );

void Roessler( const vector& x, vector& dxdt, const vector& params );
void Lorenz( const vector& x, vector& dxdt, const vector& params );
void Henon( const vector& x, vector& x2, const vector& params );
void Torus( const vector& t, vector& x, const vector& params );
void Noise( const vector& x, vector& x2, const vector& params );
void Cantor( const vector& x, vector& x2, const vector& params );

void Lorenz3( const vector& x, vector& dxdt, const vector& params );
void Test( const vector& x, vector& dxdt, const vector& params );


extern vector vecRoesslerDefParams;
extern vector vecLorenzDefParams;
extern vector vecHenonDefParams;
extern vector vecTorusDefParams;
extern vector vecNoiseDefParams;
extern vector vecCantor7aDefParams;
extern vector vecCantor7bDefParams;


boolean initFunctionAndParams( int type, vectorFunction& f, vector& vecParams );
#endif

#define ROESSLER 1
#define LORENZ   2
#define HENON    3
#define TORUS    4
#define NOISE    5
#define CANTORA  6
#define CANTORB  7


int GetType( const char* name );
int IsParametric( int n );
int IsContinous( int n );
int IsDiscrete( int n );
int GetDimension( int n );
double GetDefStep( int n );
const char* GetName( int n );


#endif // __FUNCTIONS_H__












