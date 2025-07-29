#include <malloc.h>
#include <iostream>

#include "nrutil.h"

#include <cstdlib>

using std::cerr;
using std::endl;

void nrerror(const char error_text[] )
{
  std::cerr << "Numerical Recipes run-time error..." << endl;
  cerr << error_text << endl;
  cerr << "...now exitings to system..." << endl;
  
  exit(1);
}



float *vector(int nl,int nh)
{
  float* v = new float[nh-nl+1];
  if( !v ) nrerror("allocation failure in vector()");
  return v-nl;
}

int *ivector(int nl,int nh)
{
  int* v = new int[nh-nl+1];
  if( !v ) nrerror("allocation failure in ivector()");
  return v-nl;
}

double *dvector(int nl,int nh)
{
  double* v = new double[nh-nl+1];
  if( !v ) nrerror("allocation failure in dvector()");
  return v-nl;
}



float **matrix(int nrl,int nrh,int ncl,int nch)
{
  float** m = new float*[nrh-nrl+1];
  if( !m ) nrerror("allocation failure 1 in matrix()");
  m -= nrl;
  
  for( int i=nrl; i<=nrh; i++ ) 
    {
      m[i]= new float[nch-ncl+1];
      if( !m[i] ) nrerror("allocation failure 2 in matrix()");
      m[i] -= ncl;
    }
  return m;
}

double **dmatrix(int nrl,int nrh,int ncl,int nch)
{
  double** m = new double*[nrh-nrl+1];
  if( !m ) nrerror("allocation failure 1 in dmatrix()");
  m -= nrl;
  
  for( int i=nrl; i<=nrh; i++ ) 
    {
      m[i]= new double[nch-ncl+1];
      if( !m[i] ) nrerror("allocation failure 2 in dmatrix()");
      m[i] -= ncl;
    }
  return m;
}

int **imatrix(int nrl,int nrh,int ncl,int nch)
{
  int** m = new int*[nrh-nrl+1];
  if( !m ) nrerror("allocation failure 1 in imatrix()");
  m -= nrl;
  
  for( int i=nrl; i<=nrh; i++ ) 
    {
      m[i]= new int[nch-ncl+1];
      if( !m[i] ) nrerror("allocation failure 2 in imatrix()");
      m[i] -= ncl;
    }
  return m;
}



float **submatrix(float** a,int oldrl,int oldrh,int oldcl,int /* oldch */,int newrl,int newcl)
{
  float** m = new float*[oldrh-oldrl+1];
  if( !m ) nrerror("allocation failure in submatrix()");
  m -= newrl;

  for( int i=oldrl,j=newrl; i<=oldrh; i++, j++ ) 
    m[j]=a[i]+oldcl-newcl;
  
  return m;
}



void free_vector(float* v,int nl,int /* nh */ )
{
  delete [] (v+nl);
}

void free_ivector(int* v,int nl,int /* nh */ )
{
  delete [] (v+nl);
}

void free_dvector(double* v,int nl,int /* nh */ )
{
  delete [] (v+nl);
}



void free_matrix(float** m,int nrl,int nrh,int ncl,int /* nch */)
{
  for( int i=nrh; i>=nrl; i-- ) delete [] (m[i]+ncl);
  delete [] (m+nrl);
}

void free_dmatrix(double** m,int nrl,int nrh,int ncl,int /* nch */ )
{
  for( int i=nrh; i>=nrl; i-- ) delete [] (m[i]+ncl);
  delete [] (m+nrl);
}

void free_imatrix(int** m,int nrl,int nrh,int ncl,int /* nch */ )
{
  for( int i=nrh; i>=nrl; i-- ) delete [] (m[i]+ncl);
  delete [] (m+nrl);
}



void free_submatrix(float** b,int nrl,int /* nrh */,int /* ncl */ ,int /* nch */)
{
  delete [] (b+nrl);
}



float **convert_matrix(float* a,int nrl,int nrh,int ncl,int nch)
{
  int nrow=nrh-nrl+1;
  int ncol=nch-ncl+1;
  float** m = new float*[nrow];

  if( !m ) nrerror("allocation failure in convert_matrix()");
  m -= nrl;
  for( int i=0,j=nrl; i<=nrow-1; i++,j++ ) 
    m[j]=a+ncol*i-ncl;
  return m;
}



void free_convert_matrix(float** b,int nrl,int /* nrh */ ,int /* ncl */ ,int /* nch */)
{
  delete [] (b+nrl);
}




