template <class T>
void alloc_matrix( T**& x, int nrl, int nrh, int ncl, int nch )
{
  x = new (T*)[nrh-nrl+1];
  if( !x ) nrerror("allocation failure 1 in alloc_matrix()");
  x -= nrl;
  
  for( int i=nrl; i<=nrh; i++ ) 
    {
      x[i]= new T[nch-ncl+1];
      if( !x[i] ) nrerror("allocation failure 2 in alloc_matrix()");
      x[i] -= ncl;
    }
}

template <class T>
void free_matrix( T** x, int nrl, int nrh, int ncl, int /* nch */ )
{
  if( !x ) return;
  for( int i=nrh; i>=nrl; i-- ) delete [] (x[i]+ncl);
  delete [] (x+nrl);
}




template <class T>
class Matrix
{
	int nrl, nrh, ncl, nch;
	T** x;
	
public:
	Matrix( ) : nrl(0), nrh(0), ncl(0), nch(0), x((T**)0L) { }

	Matrix( int _nrl, int _nrh, int _ncl, int _nch ) 
	  : nrl(_nrl), nrh(_nrh), ncl(_ncl), nch(_nch), x((T**)0L)
	  { alloc_matrix( x, nrl, nrh ,ncl, nch ); }

	~Matrix( )
	  { free_matrix(x, nrl, nrh, ncl, nch); }
		
	void clear() 
	  { for( int i=nrl; i<=nrh; i++ ) for( int j=ncl; j<=nch; j++ )  x[i][j]=(T)0; }

	void size( int _nrl, int _nrh, int _ncl, int _nch ) 
	  { if( !x ) { nrl=_nrl; nrh=_nrh; ncl=_ncl; nch=_nch; alloc_matrix( x, nrl, nrh ,ncl, nch ); } }

	T** operator()()
	  { return x; }
	const T* const * operator()() const 
	  { return x; }

	T** nrmat()
	  { return operator()(); }
	const T* const * nrmat() const
	  { return operator()(); }

	T*& operator[](int n) 
	  { return x[n]; }

	T* operator[](int n) const
	  { return x[n]; }
};

