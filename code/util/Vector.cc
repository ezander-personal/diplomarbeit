#include <iostream.h>

#include "Vector.h"
#include "General.h"


double operator*( const vector& vec1, const vector& vec2 )
{
  ASSERT( vec1.size == vec2.size );
  double d = 0;
  for( int i=0; i<vec1.size; i++) d+=vec1.x[i]*vec2.x[i];
  return d;
}

vector operator*( const vector& vec, double d )
{
  vector v( vec.size );
  for( int i=0; i<vec.size; i++ ) v.x[i]=vec.x[i]*d;
  return v;
}

vector operator*( double d, const vector& vec )
{
  vector v( vec.size );
  for( int i=0; i<vec.size; i++ ) v.x[i]=vec.x[i]*d;
  return v;
}


vector operator/( const vector& vec, double d )
{
  ASSERT( d!=0 );
  vector v( vec.size );
  for( int i=0; i<vec.size; i++ ) v.x[i]=vec.x[i]/d;
  return v;
}

vector operator+( const vector& vec1, const vector& vec2 )
{
  ASSERT( vec1.size == vec2.size );
  vector v( vec1.size );
  for( int i=0; i<v.size; i++ ) v.x[i]=vec1.x[i]+vec2.x[i];
  return v;
}

vector operator-( const vector& vec1, const vector& vec2 )
{
  ASSERT( vec1.size == vec2.size );
  vector v( vec1.size );
  for( int i=0; i<v.size; i++ ) v.x[i]=vec1.x[i]-vec2.x[i];
  return v;
}


const vector& vector::operator=( const vector& vec )
{
  if( size == 0 )
    {
      size = vec.size;
      x = new double[ size ];
    }

  ASSERT( size == vec.size );
  for( int i=0; i<size; i++ ) x[i]=vec.x[i];
  return *this;
}

const vector& vector::operator+=( const vector& vec )
{
  ASSERT( size == vec.size );
  for( int i=0; i<size; i++ ) x[i]+=vec.x[i];
  return *this;
}

const vector& vector::operator-=( const vector& vec )
{
  ASSERT( size == vec.size );
  for( int i=0; i<size; i++ ) x[i]-=vec.x[i];
  return *this;
}

const vector& vector::operator*=( double d )
{
  for( int i=0; i<size; i++ ) x[i]*=d;
  return *this;
}

const vector& vector::operator/=( double d )
{
  ASSERT( d!=0.0 );
  for( int i=0; i<size; i++ ) x[i]/=d;
  return *this;
}


ostream& operator<<( ostream& os, const vector& vec )
{
  for( int i=0; i<vec.size; i++ )
    {
      os << vec.x[i] <<  tab;
    }

  return os;
}










