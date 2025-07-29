#include <math.h>
#include <stdlib.h>

#include "General.h"
#include "Evl.h"

#include <iomanip.h>


#define ZERO_CROSSINGP  0
#define ZERO_CROSSINGN  1
#define REL_MINIMUM     2
#define REL_MAXIMUM     3
#define ABS_MINIMUM     4
#define ABS_MAXIMUM     5
#define INV_E           6
#define MEAN            7
#define DEVIATION       8

#define MAX_INFO     10000
 
struct evlInfo
{
  int type;
  int position;
  double value;
};


inline int cmp( int n1, int n2, int k) { return (n1>n2) ? k : ( (n1<n2) ? -k : 0 ); }
inline int cmp( double d1, double d2, int k) { return (d1>d2) ? k : ( (d1<d2) ? -k : 0 ); }


int CompareT( evlInfo* p1, evlInfo* p2) { return cmp( p1->type, p2->type, 2 ) + cmp( p1->position, p2->position, 1); }
int CompareP( evlInfo* p1, evlInfo* p2) { return cmp( p1->position, p2->position, 2 ) + cmp( p1->type, p2->type, 1); }
int CompareV( evlInfo* p1, evlInfo* p2) { return cmp( p1->value, p2->value, 2 ) + cmp( p1->type, p2->type, 1); }


void InsertInfo( evlInfo* info, int& count, int type, int position, double value )
{
  ASSERT( count < MAX_INFO );

  info[ count ].type = type;
  info[ count ].position = position;
  info[ count ].value = value;
  count++;
}


void evl( const String& ifilename, int column, int compare, boolean shortDisp )
{ 
  comparison_fn_t cmp_fn=NULL;
  switch( compare )
    {
    case COMPARE_TYPE: cmp_fn = CompareT; break;
    case COMPARE_POS: cmp_fn = CompareP; break;
    case COMPARE_VALUE: cmp_fn = CompareV; break;
    default: ASSERT( FALSE );
    }


  int cols = getFileCols( ifilename );
  int rows = getFileRows( ifilename );

  if( cols==-1 || rows==-1 || column>cols ) exit( 1 );

  
  dVector d(rows);
  readFileCol( ifilename, column, d(), cols );

  double dMin=d[0], dMax=d[0];
  int min=0, max=0, infoCount=0;
  
  boolean invEFound = FALSE;
  double  e=exp(1);
  
  evlInfo  info[ MAX_INFO ];
  
  double sum=0.0, sum2=0.0;

  for( int i=0; i<rows; i++ )
    {
      sum += d[i];
      sum2 += d[i]*d[i];

      if( d[i] < dMin )
	{
	  dMin = d[i];
	  min = i;
	}
      if( d[i] > dMax )
	{
	  dMax = d[i];
	  max = i;
	}
      
      if( !invEFound && d[i]*e<d[0] ) { InsertInfo( info, infoCount, INV_E, i, d[i] ); invEFound=TRUE; } 
      
      if( i>0 && i<rows-1 && d[i-1]>=d[i] && d[i]<=d[i+1] && !shortDisp ) InsertInfo( info, infoCount, REL_MINIMUM, i, d[i] );
      if( i>0 && i<rows-1 && d[i-1]<=d[i] && d[i]>=d[i+1] && !shortDisp ) InsertInfo( info, infoCount, REL_MAXIMUM, i, d[i] );
      
      if( i<rows-1 && d[i]>=0 && d[i+1]<0 && !shortDisp ) InsertInfo( info, infoCount, ZERO_CROSSINGN, i, d[i] );
      if( i<rows-1 && d[i]<=0 && d[i+1]>0 && !shortDisp ) InsertInfo( info, infoCount, ZERO_CROSSINGP, i, d[i] );
      
    }
  
  InsertInfo( info, infoCount, MEAN, 0, sum/rows );
  InsertInfo( info, infoCount, DEVIATION, 0, sqrt((sum2 - sum*sum/rows)/(rows-1)) );
  InsertInfo( info, infoCount, ABS_MINIMUM, min, dMin );
  InsertInfo( info, infoCount, ABS_MAXIMUM, max, dMax );
  
  if( cmp_fn != NULL ) qsort( info, infoCount, sizeof(evlInfo), cmp_fn );
  
  
  for( int i=0; i<infoCount; i++ )
    {
      switch( info[i].type )
	{
	case ZERO_CROSSINGP: cout << "zero crossing (+) \t"; break;
	case ZERO_CROSSINGN: cout << "zero crossing (-) \t"; break;
	case REL_MINIMUM:    cout << "rel minimum       \t"; break;
	case REL_MAXIMUM:    cout << "rel maximum       \t"; break;
	case ABS_MINIMUM:    cout << "abs minimum       \t"; break;
	case ABS_MAXIMUM:    cout << "abs maximum       \t"; break;
	case INV_E:          cout << "x/x0<e            \t"; break;
	case MEAN:           cout << "mean              \t"; break;
	case DEVIATION:      cout << "deviation         \t"; break;
	default: ASSERT( FALSE );
	}
      cout << "at " << setw( 7 ) << info[i].position << "\t (" << info[i].value << ")" << endl;
    }

}









