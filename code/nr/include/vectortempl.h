template<class T>
void alloc_vector( T*& x, int nl, int nh )
{
  x = new T[nh-nl+1];
  if( !x ) nrerror("allocation failure in alloc_vector()");
  x -= nl;
}

template<class T>
void free_vector( T* x, int nl, int /* nh */ )
{
  if( !x ) return;
  delete [] (x+nl);
}

template <class T>
class Vector
{
	int nl, nh;
	T* x;
	
public:
	Vector( )
	  : nl(0), nh(0), x((T*)0L) {}

	Vector( int _nl, int _nh ) 
	  : nl(_nl), nh(_nh ), x((T*)0L)
	  { alloc_vector( x, nl, nh ); }
	
	Vector( int _n ) 
	  : nl(0), nh(_n-1 ), x((T*)0L)
	  { alloc_vector( x, nl, nh ); }

	~Vector( ) 
	  { free_vector(x, nl, nh); }

	void clear() { for( int i=nl; i<=nh; i++ ) x[i]=(T)0; }

	void size( int _nl, int _nh ) { if( !x ) { nl=_nl; nh=_nh; alloc_vector( x, nl, nh ); } }
	void size( int _n ) { if( !x ) { nl=0; nh=_n-1; alloc_vector( x, nl, nh ); } }

	int getnh() const { return nh; }
	int getnl() const { return nl; }
	int getsize() const { return nh-nl+1; }

	T* operator()() { return x+nl; }
	const T* operator()() const { return x+nl; }
	
	T* nrvec() { return operator()()-1; }
	const T* nrvec() const { return operator()()-1; }
	
	T& operator[](int n) { return x[n]; }
	const T& operator[](int n) const { return x[n]; }
};



