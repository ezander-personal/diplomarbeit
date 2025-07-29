#include "General.h"

#include "Vector.h"
#include "Functions.h"

#include <math.h>

static vector *pvec1=NULL, *pvec2=NULL, *pvec3=NULL, *pvec4=NULL;

void rkInitVectors( int dimension )
{
  if( pvec1 )
    {
      delete pvec1;
      delete pvec2;
      delete pvec3;
      delete pvec4;
    }
  pvec1 = new vector( dimension );
  pvec2 = new vector( dimension );
  pvec3 = new vector( dimension );
  pvec4 = new vector( dimension );
}

#define vec1 (*pvec1)
#define vec2 (*pvec2)
#define vec3 (*pvec3)
#define vec4 (*pvec4)



void rkStep4( vector& vec, const vector& params, vectorFunction f, double step )
{
  double step2 = step/2.0, step6 = step/6.0;
  
  f( vec,                vec1, params );
  f( vec + vec1 * step2, vec2, params );
  f( vec + vec2 * step2, vec3, params );
  f( vec + vec3 * step,  vec4, params );
  
  vec += ( vec1 + 2.0*( vec2 + vec3 ) + vec4 ) * step6;
}

void rkStep5( vector& vec, const vector& params, vectorFunction f, double step )
{
  vector vecA( (const vector&)vec);
  vector vecB = vec; 
  
  rkStep4( vecA, params, f, step );

  rkStep4( vecB, params, f, step/2.0 );
  rkStep4( vecB, params, f, step/2.0 );

  vector delta = vecB - vecA;

  vec = vecB + delta/15.0; 
}


void rkStep( const vector& vec, vector& newvec, const vector& params, vectorFunction f, double step, int stepCount )
{
  // double step2 = step/2.0, step6 = step/6.0;

  newvec = vec;

  for( int i=0; i<stepCount; i++ )
    {
      rkStep4( newvec, params, f, step );
      /*
      f( newvec,                vec1, params );
      f( newvec + vec1 * step2, vec2, params );
      f( newvec + vec2 * step2, vec3, params );
      f( newvec + vec3 * step,  vec4, params );
      */

      /*
      f( vec,                vec1, params );
      f( vec + vec1 * step2, vec2, params );
      f( vec + vec2 * step2, vec3, params );
      f( vec + vec3 * step,  vec4, params );

      // vector v( 3 );
      // v = ( vec1 + 2.0*( vec2 + vec3 ) + vec4 ) * step6;
      // cout << vec1 << vec2 << vec3 << vec4 <<  v << "\t" << step2 << "\t" << step6 << endl;

      newvec += ( vec1 + 2.0*( vec2 + vec3 ) + vec4 ) * step6;
      */
    }	
}








