#include "General.h"
#include "Vector.h"
#include "Functions.h"


#include <math.h>
#include <string.h>
#include <time.h>

#include <ACG.h>
#include <Normal.h>
#include <Uniform.h>

#define a (params[0])
#define b (params[1])
#define c (params[2])
#define d (params[3])


static double roesslerDef[] = { 0.38, 0.3, 4.5 };
// static double roesslerDef[] = { 0.15, 0.2, 10 };
// static double roesslerDef[] = { 0.2, 0.2, 5.7 };
static double lorenzDef[]   = { 10.0, 28.0, 2.667 };
// static double lorenzDef[]   = { 0.25, 4.0, 8.0, 1.0 };
static double henonDef[]    = { 1.4, 0.3 };
static double torusDef[]    = { 1.0, 4.0, 15.379, 1.0 };
static double noiseDef[]    = { 0.0, 1.0, 0.9 }; // mean, variance, A(1)<1
static double cantor7aDef[] = {7,0,1,5,6};
static double cantor7bDef[] = {7,0,2,4,6};

vector vecRoesslerDefParams( 3, roesslerDef );
vector vecLorenzDefParams( 3, lorenzDef );
vector vecHenonDefParams( 2, henonDef );
vector vecTorusDefParams( 4, torusDef );
vector vecNoiseDefParams( 3, noiseDef );
vector vecCantor7aDefParams( 5, cantor7aDef );
vector vecCantor7bDefParams( 5, cantor7bDef );


void Roessler( const vector& x, vector& dxdt, const vector& params )
{
  dxdt[0] = - x[1] - x[2];
  dxdt[1] =   x[0] + a*x[1];
  //  dxdt[2] = b*x[0] - c*x[2] + x[0]*x[2];
  dxdt[2] = b - c*x[2] + x[0]*x[2];
}


void Lorenz( const vector& x, vector& dxdt, const vector& params )
{
  dxdt[0] =a*(x[1] - x[0]);
  dxdt[1] =b*x[0] -  x[1] - x[0]*x[2];
  dxdt[2] =-c*x[2] +  x[0]*x[1];
}


/*
thats the lorenz II model

void Lorenz( const vector& x, vector& dxdt, const vector& params )
{
  dxdt[0] =-x[1]*x[1]-x[2]*x[2]-a*(x[0]-c);
  dxdt[1] =x[0]*x[1]-b*x[0]*x[2]-x[1]+d;
  dxdt[2] =b*x[0]*x[1]+x[0]*x[2]-x[2];
}
*/

void Henon( const vector& x, vector& x2, const vector& params )
{
  x2[0] =1 - a*x[0]*x[0] + x[1];
  x2[1] =b*x[0];
}



void Torus( const vector& t, vector& x, const vector& params )
{
  double u=t[0];
  x[0] = (b+d*sin(u*c))*sin( u*a );
  x[1] = (b+d*sin(u*c))*cos( u*a );
  x[2] = d*cos(u*c);
}

// global variables

static ACG rng( (long)time(NULL) ); // ( seed, size);
static Normal normDist( 0, 1, &rng );
static Uniform uniDist( 1, 5, &rng );
static noise_init=FALSE;

void Noise( const vector& x, vector& x2, const vector& params )
{
  static double a0, a1, sigma;
  if( !noise_init )
    {
      a1 = params[2];
      a0 = params[0]*(1-a1);
      sigma = sqrt( fabs( params[1]*(1-a1*a1) ) );
      noise_init = TRUE;
    }
  // thats no true gaussian noise, but rather an Ornstein-Uhelenbeck process
  x2[0] = a0 + a1 * x[0] + sigma * normDist();
}

void Test( const vector& x, vector& dxdt, const vector& /* params */ )
{
  dxdt[0] = x[1];
  dxdt[0] = -x[0];
}

void Cantor( const vector& x, vector& x2, const vector& params )
{
  double y=x[0];
  
  int n=int(uniDist());

  y=(y+params[n])/params[0];

  x2[0] = y;
  x2[1] = 1;
}

#undef a
#undef b
#undef c
#undef d




int GetType( const char* name )
{
  if( !strcasecmp( name, "ROES" ) || !strcasecmp( name, "ROESSLER" ) ) return ROESSLER;  
  if( !strcasecmp( name, "LOR" )  || !strcasecmp( name, "LORENZ" ) )   return LORENZ;
  if( !strcasecmp( name, "HEN" )  || !strcasecmp( name,  "HENON" ) )   return HENON;
  if( !strcasecmp( name, "TOR" )  || !strcasecmp( name,  "TORUS" ) )   return TORUS;
  if( !strcasecmp( name, "NOI" )  || !strcasecmp( name,  "NOISE" ) )   return NOISE;
  if( !strcasecmp( name, "CANA" )  || !strcasecmp( name,  "CANTORA" ) )   return CANTORA;
  if( !strcasecmp( name, "CANB" )  || !strcasecmp( name,  "CANTORB" ) )   return CANTORB;

  return -1;
}


const char* GetName( int n )
{
  switch( n )
    {
    case ROESSLER: return "Roessler";
    case LORENZ: return "Lorenz";
    case HENON: return "Henon";
    case TORUS: return "Torus";
    case NOISE: return "Noise";
    case CANTORA: return "CantorA";
    case CANTORB: return "CantorB";
    default:
      ASSERT( FALSE );
      return NULL;
    }
}

int GetDimension( int n )
{
  switch( n )
    {
    case ROESSLER:
    case LORENZ:
    case TORUS:
      return 3;
    case HENON:
    case CANTORA:
    case CANTORB:
      return 2;
    case NOISE:
      return 1;
    default:
      ASSERT( FALSE );
      return -1;
    }
}

int IsParametric( int n )
{
  switch( n )
    {
    case ROESSLER:
    case LORENZ:
    case HENON:
    case CANTORA:
    case CANTORB:
    case NOISE:
      return FALSE;
    case TORUS:
      return TRUE;
    default:
      ASSERT( FALSE );
      return FALSE;
    }
}


int IsContinous( int n )
{
  switch( n )
    {
    case ROESSLER:
    case LORENZ:
    case TORUS:
      return TRUE;
    case HENON:
    case CANTORA:
    case CANTORB:
    case NOISE:
      return FALSE;
    default:
      ASSERT( FALSE );
      return FALSE;
    }
}

int IsDiscrete( int n )
{
  switch( n )
    {
    case ROESSLER:
    case LORENZ:
    case TORUS:
    case NOISE:
      return FALSE;
    case CANTORA:
    case CANTORB:
    case HENON:
      return TRUE;
    default:
      ASSERT( FALSE );
      return FALSE;
    }
}


double GetDefStep( int n )
{
  switch( n )
    {
    case ROESSLER:
      return 0.05;
    case LORENZ:
      return 0.009;
    case TORUS:
      return 0.01;
    case CANTORA:
    case CANTORB:
    case NOISE:
    case HENON:
      return 1;
    default:
      ASSERT( FALSE );
      return -1;
    }
}

boolean initFunctionAndParams( int type, vectorFunction &f, vector& vecParams )
{
  switch( type )
    {
    case ROESSLER:
      f=Roessler;
      vecParams = vecRoesslerDefParams;
      return TRUE;
    case LORENZ:
      f=Lorenz;
      vecParams = vecLorenzDefParams;
      return TRUE;
    case HENON:
      f=Henon;
      vecParams = vecHenonDefParams;
      return TRUE;
    case TORUS:
      f=Torus;
      vecParams = vecTorusDefParams;
      return TRUE;
    case NOISE:
      f=Noise;
      vecParams = vecNoiseDefParams;
      return TRUE;
    case CANTORA:
      f=Cantor;
      vecParams = vecCantor7aDefParams;
      return TRUE;
    case CANTORB:
      f=Cantor;
      vecParams = vecCantor7bDefParams;
      return TRUE;
    }
  return FALSE;
}


















