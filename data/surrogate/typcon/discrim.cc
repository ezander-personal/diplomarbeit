#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include <ACG.h>
#include <Normal.h>
#include <Uniform.h>

using namespace std;

ostream& tab( ostream& os ) { os << '\t'; return os; }
ostream& car( ostream& os ) { os << '\r'; return os; }


//
// Statistik
//

double mean( double* x, int n )
{
  double y=0.0;
  for( int i=0; i<n; i++ ) y+=x[i];
  return y/(double)n;
}

double standard( double* x, double xm, int n)
{
  double y=0.0;
  for( int i=0; i<n; i++ ) y+=(x[i]-xm)*(x[i]-xm);
  return sqrt(y/(double)(n-1));
}

double standard( double* x, int n )
{
  return standard( x, mean(x,n), n );
}

//
// random
//

ACG rng( (long)time(NULL) ); 

void create_uniform( double* x, int n)
{
  Uniform uniDist(-1, 1, &rng );
  //Uniform uniDist( -sqrt(3.0), sqrt(3.0), &rng );

  for( int i=0; i<n; i++ ) x[i] = uniDist();
}

void create_normal( double* x, int n, double xmp=0.0, double variance=1.0)
{
  Normal normDist( xmp, variance, &rng );
  
  for( int i=0; i<n; i++ ) x[i] = normDist();
}

void create_normal_standard( double* x, int n, double xmp=0.0, double xsp=1.0)
{
  Normal normDist( xmp, xsp*xsp, &rng );
  
  for( int i=0; i<n; i++ ) x[i] = normDist();
}

void create_normal_constrained( double* x, int n, double xmp=0.0, double xsp=1.0)
{
  Normal normDist( xmp, xsp*xsp, &rng );
  
  for( int i=0; i<n; i++ ) x[i] = normDist();

  double xm=mean(x,n);
  double xs=standard(x,xm,n);

  for( int i=0; i<n; i++ ) x[i]=xmp+(x[i]-xm)/xs*xsp;
}



//
// Diskriminatoren
//
typedef double discrim( double*, int );

double pivotal( double* x, int n )
{
  double y=0.0;
  double xm=mean(x,n);
  double xs=standard(x,xm,n);

  for( int i=0; i<n; i++ ){
    double z=(x[i]-xm)/xs;
    y+=z*z*z*z;
  }
  return y/(double)n;
}

double nonpivotal( double* x, int n )
{
  double y=0.0;
  for( int i=0; i<n; i++ ){
    double z=x[i];
    y+=z*z*z*z;
  }
  return y/(double)n;
}


//
// testen
//

inline int cmp_double( double a, double b) { if( a>b ) return 1; else if( a<b) return -1; else return 0; }
inline int cmp_int( int a, int b) { return a-b; };

int cmp_d( const double* a, const double* b ) { return cmp_double( *a, *b ); }
int cmp_i( const int* a, const int* b ) { return cmp_int( *a, *b ); }


int recect_null( double* t, int B )
{
  double t0=t[0];

  qsort( t, B+1, sizeof(double), (__compar_fn_t)cmp_d );
  double* pt0 = (double*)bsearch( &t0, t, B+1, sizeof(double), (__compar_fn_t)cmp_d );
  
  int k= pt0 - t;

  if( k>0 && k<B )
    return 0;
  else
    return 1;
}

int test( int n, discrim T, int B, int constrained, int uniform_data=1 )
{
  double *x=new double[n];
  double *t=new double[B+1];

  if( uniform_data )
    create_uniform( x,  n );
  else
    create_normal( x, n );

  double xm = mean( x, n );
  double xs = standard( x, xm, n);
  
  t[0]=T(x,n);

  for( int i=0; i<B; i++ ){
    if( constrained )
      create_normal_constrained( x,  n,  xm,  xs );
    else
      create_normal_standard( x,  n,  xm,  xs );
      
    t[i+1]=T( x, n );
  }

  /*for( int i=0; i<B+1; i++ )
    cout << t[i] << tab << (i ? 1 : 2) << endl;
    */
  int reject = recect_null( t, B );
  // cerr << reject << endl;

  delete [] t;
  delete [] x;

  return reject;
}


void repeat_test()
{
  ofstream fout("stat" );
  // int counts[]={ 5, 10, 21, 46, 100, 215, 464, 1000, 0, };
  int counts[]={ 6, 10, 18, 32, 56, 100, 178, 316, 562, 1000, 0, };

  int trials=10000;
  double fac=1.0/(double)trials;

  int* pcount=counts;
  while( *pcount ){
    int rejects[]={ 0, 0,  0, 0,  0, 0,  0, 0, };
    int n=*pcount;
    cerr << "                                                                                                  " << car;
    for( int i=0; i<trials; i++){
      // uniform -> 1-beta
      rejects[0] += test( n, nonpivotal, 39, 0, 0 );
      rejects[1] += test( n, pivotal, 39, 0, 0 );  
      rejects[2] += test( n, nonpivotal, 39, 1, 0 );
      rejects[3] += test( n, pivotal, 39, 1, 0 );
      //normal -> alpha
      rejects[4] += test( n, nonpivotal, 39, 0, 1 );
      rejects[5] += test( n, pivotal, 39, 0, 1 );  
      rejects[6] += test( n, nonpivotal, 39, 1, 1 );
      rejects[7] += test( n, pivotal, 39, 1, 1 );
      cerr << "Num:   " << tab << n << tab << i << car;
    }
    fout << *pcount << tab << fac*rejects[0] << tab << fac*rejects[1] << tab << fac*rejects[2] << tab << fac*rejects[3] 
	 << tab << fac*rejects[4] << tab << fac*rejects[5] << tab << fac*rejects[7] << tab << fac*rejects[7] << endl;
    pcount++;
  }

}

int main()
{
  repeat_test();

  if ( 0 ){
    int n=100;
    
    test( n, nonpivotal, 39, 0 );
    test( n, pivotal, 39, 0 );  
    test( n, nonpivotal, 39, 1 );
    test( n, pivotal, 39, 1 );
  }
  return 0;
}
