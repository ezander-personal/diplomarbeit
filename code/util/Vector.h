// ;-*-C++-*-
// tells emacs to use C++-mode instead of C-mode

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream.h>

class vector
{
  int size;
  double* x;

 public:
  inline vector();
  inline vector( int _size );
  inline vector( int _size, double* _x );
  inline vector( const vector& vec );
  inline ~vector();

  inline double& operator[](int i );
  inline const double& operator[](int i ) const;
  
  friend double operator*( const vector& vec1, const vector& vec2 );  
  friend vector operator*( const vector& vec, double d );
  friend vector operator*( double d, const vector& vec );

  friend vector operator/( const vector& vec, double d );

  friend vector operator+( const vector& vec1, const vector& vec2 );  
  friend vector operator-( const vector& vec1, const vector& vec2 );  

  const vector& operator=( const vector& vec );
  const vector& operator+=( const vector& vec );
  const vector& operator-=( const vector& vec );
  const vector& operator*=( double d );
  const vector& operator/=( double d );

  friend ostream& operator<<( ostream& os, const vector& vec );
};

vector::vector()
{
  size = 0;
  x = NULL;
}

vector::vector( int _size )
{
  size = _size;
  x = new double[ _size ];
}

vector::vector( int _size, double* _x )
{
  size = _size;
  x = new double[ _size ];
  for( int i=0; i<_size; i++ ) x[i]=_x[i];
}


vector::vector( const vector& vec )
{
  size = vec.size;
  x = new double[ size ];
  for( int i=0; i<size; i++ ) x[i] = vec.x[i];
}

vector::~vector()
{
  delete [] x;
}

inline double& vector::operator[](int i )
{
  return x[i];
}

inline const double& vector::operator[](int i ) const
{
  return x[i];
}

#endif // __VECTOR_H__





