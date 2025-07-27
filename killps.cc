#include<iostream.h>
#include<String.h>



#define BUFLEN 2048

void main()
{
	int modulo=0; // modulo=0 -> dont print
	int sincepage=0;
	bool eopfound=false;
	bool bopfound=false;
	bool printit = true;
	
	char buffer[BUFLEN];
	String line;
	
	while( !cin.eof() ){
		cin.getline( buffer, BUFLEN );
		line = buffer;
		if( line.at(0,7) == "%%Page:" ){
			sincepage=0;
			modulo=1-modulo;
			eopfound=false;
			bopfound=false;
			if( modulo==0 ) {
				cout << line << endl;

				cin.getline( buffer, BUFLEN );
				line=buffer;
				int nbop=line.index("bop");
				line=line.at(0,nbop+3 );
				cout << line << endl;
				cout << "eop" << endl;
				printit=false;
			}
			else
				printit=true;
		}
		if( line.at(0,9) == "%%Trailer" ){
			printit=true;
		}
		
		if( printit )
			cout << line << endl;

		sincepage++;
	}		
}