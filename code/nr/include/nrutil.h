#ifndef __NRUTIL_H__
#define __NRUTIL_H__

float *vector(int nl, int nh);
float **matrix(int nrl, int nrh, int ncl, int nch);
float **convert_matrix(float* a,int nrl,int nrh,int ncl,int nch);
double *dvector(int nl, int nh);
double **dmatrix(int nrl, int nrh, int ncl, int nch);
int *ivector(int nl, int nh);
int **imatrix(int nrl, int nrh, int ncl, int nch);
float **submatrix(float** a,int oldrl,int oldrh,int oldcl,int oldch,int newrl,int newcl);
void free_vector(float* v,int nl,int nh);
void free_dvector(double* v,int nl,int nh);
void free_ivector(int* v,int nl,int nh);
void free_matrix(float** m,int nrl,int nrh,int ncl,int nch);
void free_dmatrix(double** m,int nrl,int nrh,int ncl,int nch);
void free_imatrix(int** m,int nrl,int nrh,int ncl,int nch);
void free_submatrix(float** b,int nrl,int nrh,int ncl,int nch);
void free_convert_matrix(float** b,int nrl,int nrh,int ncl,int nch);
void nrerror( char error_text[] );


class dVector
{
	int nl, nh;
	double* x;
	
public:
	dVector( ) { x=(double*)0L; }
	dVector( int _nl, int _nh ) { nl=_nl; nh=_nh; x=dvector( nl, nh ); }
	dVector( int _n ) { nl=0; nh=_n-1; x=dvector( nl, nh ); }

	~dVector( ) { if( x ) free_dvector(x, nl, nh); }

	void clear() { for( int i=nl; i<=nh; i++ ) x[i]=0.0; }

	void size( int _nl, int _nh ) { if( !x ) { nl=_nl; nh=_nh; x=dvector( nl, nh ); } }
	void size( int _n ) { if( !x ) { nl=0; nh=_n-1; x=dvector( nl, nh ); } }

	int getnh() const { return nh; }
	int getnl() const { return nl; }
	int getsize() const { return nh-nl+1; }

	double* operator()() { return x+nl; }
	const double* operator()() const { return x+nl; }
	
	double* nrvec() { return operator()()-1; }
	const double* nrvec() const { return operator()()-1; }
	
	double& operator[](int n) { return x[n]; }
	const double& operator[](int n) const { return x[n]; }
};

class dMatrix
{
	int nrl, nrh, ncl, nch;
	double** x;
	
public:
	dMatrix( ) { x=(double**)0L; }
	dMatrix( int _nrl, int _nrh, int _ncl, int _nch ) { nrl=_nrl; nrh=_nrh; ncl=_ncl; nch=_nch; x=dmatrix( nrl, nrh ,ncl, nch ); }
	~dMatrix( ) { if( x ) free_dmatrix(x, nrl, nrh, ncl, nch); }
		
	void clear() { for( int i=nrl; i<=nrh; i++ ) for( int j=ncl; j<=nch; j++ )  x[i][j]=0.0; }

	void size( int _nrl, int _nrh, int _ncl, int _nch ) { if( !x ) { nrl=_nrl; nrh=_nrh; ncl=_ncl; nch=_nch; x=dmatrix( nrl, nrh ,ncl, nch ); } }

	double** operator()(){ return x; }
	const double* const * operator()() const { return x; }

	double** nrmat(){ return operator()(); }
	const double* const * nrmat() const{ return operator()(); }
	double* operator[](int n) { return x[n]; }
};

class iVector
{
	int nl, nh;
	int* x;
	
public:
	iVector( ) { x=(int*)0L; }
	iVector( int _nl, int _nh ) { nl=_nl; nh=_nh; x=ivector( nl, nh ); }
	iVector( int _n ) { nl=0; nh=_n-1; x=ivector( nl, nh ); }
	~iVector( ) { if( x ) free_ivector(x, nl, nh); }
		
	void clear() { for( int i=nl; i<=nh; i++ ) x[i]=0; }

	void size( int _nl, int _nh ) { if( !x )  { nl=_nl; nh=_nh; x=ivector( nl, nh ); } }
	void size( int _n ) { if( !x ) { nl=0; nh=_n-1; x=ivector( nl, nh ); } }

	int getnh() const { return nh; }
	int getnl() const { return nl; }
	int getsize() const { return nh-nl+1; }

	int* operator()() { return x+nl; }
	const int* operator()() const { return x+nl; }
	
	int* nrvec() { return operator()()-1; }
	const int* nrvec() const { return operator()()-1; }
	
	int& operator[](int n) { return x[n]; }
};

class iMatrix
{
	int nrl, nrh, ncl, nch;
	int** x;
	
public:
	iMatrix( ) { x=(int**)0L; }
	iMatrix( int _nrl, int _nrh, int _ncl, int _nch ) { nrl=_nrl; nrh=_nrh; ncl=_ncl; nch=_nch; x=imatrix( nrl, nrh ,ncl, nch ); }
	~iMatrix( ) { if( x ) free_imatrix(x, nrl, nrh, ncl, nch); }
		
	void clear() { for( int i=nrl; i<=nrh; i++ ) for( int j=ncl; j<=nch; j++ )  x[i][j]=0; }

	void size( int _nrl, int _nrh, int _ncl, int _nch ) { if( !x ) { nrl=_nrl; nrh=_nrh; ncl=_ncl; nch=_nch; x=imatrix( nrl, nrh ,ncl, nch ); } }

	operator int**() { return x; }
	operator const int* const*() const { return x; }

	int* operator[](int n) { return x[n]; }
};

#endif //__NRUTIL_H__







