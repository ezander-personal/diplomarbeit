#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

const char tab='\t';

int main(int argc, char* argv[] )
{
	
	if( argc!=3 )
	{
		cout << "usage: mkcantor max_level 1001010..." << endl;
		cout << "       Creates a series of subsets of [0,1] approaching the Cantor set with max_level+1 levels." << endl;
		cout << "       E.g. 101 would lead to the sets 1, 101, 101000101, etc, i.e. each 1 is replaced by 101" << endl;
		cout << "       and each 0 by 000, and the size of each interval is divided by 3 on each level." << endl;
		exit(1);
	}
	
	int level=atoi(argv[1]);
	const char* cnums=argv[2];
	int count=strlen(argv[2]);
	
	double d=1.0;
	for( int l=0; l<=level; l++ )
		{
			double start=0.0, end=start+d;
			if( l>0 )
				{
					int breakflag=0;
					int pos[l];
					for(int i=0; i<l;i++) pos[i]=0;
					while( 1 )
					{
						int flag=1;
						for( int i=0; i<l; i++ )
							if( cnums[pos[i]]=='0' ) { flag=0; break;}
						if( flag )
						{
							cout << start << tab << l+1 << endl;
							cout << end << tab << l+1 << endl;
							cout << endl;
						}
						
						int i=0;
						while( 1 )
						{
							pos[i]++;
							if( pos[i]==count )
							{
								pos[i]=0;
								i++;
								if( i==l)
								{
									breakflag=1;
									break;
								}
							}
							else
								break;
						}
						if( breakflag ) break;
						
						start+=d;
						end+=d;
					}
				}
			else
				{
					cout << start << tab << l+1 << endl;
					cout << end << tab << l+1 << endl;
					cout << endl;
				}
			d=d/double(count);
			
		}
	
	// cout << level << tab << count << tab << cnums << endl;
	
	return 0;
}