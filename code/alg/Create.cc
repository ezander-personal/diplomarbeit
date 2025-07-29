#define __NRUTIL_H__

#include "General.h"
#include "Vector.h"
#include "Functions.h"
#include "Runge.h"


void create( const String& filename, int points, int dimension, double delay, int type, int nDiff )
{
  int transPoints = 1000;

  ofstream fout( filename, ios::out | ios::trunc );
  
  vector vecParams;
  vectorFunction f=NULL;

  if( !initFunctionAndParams( type, f, vecParams ) )
    exit( 1 );
  
  if( delay==-1) delay=GetDefStep( type );
  dimension = GetDimension( type );
  
  if( IsParametric( type ) )
    {
      vector vecT( 1 );
      vector vecStart( dimension );
      
      vecT[0] = 0;
      
      for( int i=0; i<points; i++)
	{
	  
	  f( vecT, vecStart, vecParams );
	  if( i>=transPoints ) 
	    fout << vecT[0] << tab << vecStart << endl;
	  vecT[0] += nDiff*delay;
	}
      
    }
  else if( IsContinous( type ) )
    {
      // transPoints = 0;
      rkInitVectors( dimension );
      
      vector vecStart( dimension );
      
      for( int i=0; i<dimension; i++ ) vecStart[i]=1;
      
      vector vecNew = vecStart;
      
      for( int i=0; i<points+transPoints; i++)
	{
	  if( i>=transPoints )
	    fout << (i-transPoints)*delay*nDiff << tab << vecStart << endl;
	  
	  rkStep( vecStart, vecNew, vecParams, f, delay, nDiff );
	  vecStart = vecNew;
	}
      
    }
  else  // discrete
    {
      vector vecStart( dimension );
      
      for( int i=0; i<dimension; i++ ) vecStart[i]=1;
      
      vector vecNew=vecStart;
      
      for( int i=0; i<points+transPoints; i++ )
	{
	  if( i>=transPoints )
	    fout << i-transPoints << tab << vecStart << endl;

	  for( int j=0; j<nDiff; j++ )
	    {
	      f( vecStart, vecNew, vecParams );
	      vecStart = vecNew;
	    }
	}
    }

  fout.close();
  
  WriteGpFile( filename, GetName( type ), NULL, NULL, dimension, IsDiscrete( type ) );
}









