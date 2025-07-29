#include <stream.h>




#define GET_BIASED_EXP(a,b) var.d = a; var.l[1] >>= 20; b = (var.l[1] & 2047)

/* Stores the biased exponent of 'a' into 'b' using the known structure
   of the IEEE format, so compatibility with machines other than the Sun
   Stations is not garaunteed.  A biased exponent is essentially 1023 plus
   the power of 2 that multiplies the mantissa of the number. */



union Var_Type
{
   double d;
   long int l[2];
};


Var_Type var;

#define tab "\t"

char bins1[36];
char bins2[36];
char* bin( long int l, char* bins )
{
	// cout << 0 << tab << l << tab << (l & 1L) << endl;
	int j=0;
	for( int i=0; i<32; i++ )
	{
		if( i!=0 && i%8==0 ) bins[j++] = '.';
		if( l & 1L ) bins[j] = '1'; else bins[j]='0';
		l >>= 1;
		j++;
		// cout << i+1 << tab << l << tab << (l & 1L) << endl;
	}
	bins[35] = 0;
	return bins;
}


void bla( double d )
{
	// long l;
	// GET_BIASED_EXP(d,l); var.d = d; cout << d << tab << l << tab << var.l[0] << tab << var.l[1] << tab << bin( var.l[0], bins1 ) << tab << bin( var.l[1], bins2 ) << tab << d << endl;
	var.d = d;
	long b=var.l[1];
	cout << d << tab;
	cout << b << tab << bin( b, bins1 ) << tab;
	b <<= 2;
  b >>= 22;
	cout << b << tab << bin( b, bins1 ) << tab;
	// b = (b & 2047 );
	// cout << b << tab << bin( b, bins1 ) << tab;
	cout << endl;
}



double intexp( double d, int n )
{
	double r=1.0;
	while( n )
	{
		if( n&1 ) r*=d;
		d*=d;
		n>>=1;
	}
	return r;
} 

int  main()
{
	bla( 0.125 );
	bla( 0.25 );
	bla( 0.5 );
	bla( 1.0 );
	bla( 2.0 );
	bla( 4.0 );
	bla( 8.0 );
	bla( 16.0 );
	bla( 32.0 );
	cout << endl;
	for( double d=3.0; d<=30.0; d+=1.0 ) bla( d );
	cout << endl;
	bla( 3.1 );
	bla( 4.1 );
	bla( 5.1 );
	bla( 6.1 );
	bla( 7.1 );
	bla( 8.1 );
	bla( 9.1 );
	cout << endl;
	bla( -0.25 );
	bla( -0.5 );
	bla( -1.0 );
	bla( -2.0 );
	bla( -4.0 );
	// bla( 1.234567890 );
	cout << endl << endl;
	for( int i=1; i<=10; i++ )
	{
		cout << i << tab << intexp( 2.0, i ) << endl;
	}
}