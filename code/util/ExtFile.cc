#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

#include "General.h"
#include "ExtFile.h"


boolean fileExists( const String& filename )
{
  if( access( filename, F_OK | R_OK ) )
    return FALSE;
  else
    return TRUE;
}


void skipWhitespace( FILE* file )
{
  int c;
  do 
    {
      c = getc( file ); 
    }
  while( isspace( c ) );
  ungetc( c, file );
}

void skipLine( FILE* file )
{
  while( getc( file ) != eol );
}

void skipComments( FILE* file )
{
  int c;
  do
    {
      skipWhitespace( file );
  
      c = getc( file );
      if( c != '%' ) break;

      skipLine( file );
    }
  while( TRUE );
  ungetc( c, file );
}

int peek( FILE* file )
{
  int c=getc( file );
  ungetc( c, file );
  return c;
}


int getFileCols( const String& filename )
{
 if( !fileExists( filename ) ) return -1;
 
 FILE* file = fopen( filename, "r" );
 if( !file ) return -1;

 skipComments( file );

 int c, colCount = 0;
 boolean whiteSpace=TRUE;

 do
   {
     c = getc( file );

     if( isspace( c ) )
       whiteSpace = TRUE;
     else if( whiteSpace )
       {
	 colCount++;
	 whiteSpace = FALSE;
       }

   }
 while( c!=eol );
 
 fclose( file );
 return colCount;
}


int getFileRows( const String& filename )
{
 if( !fileExists( filename ) ) return -1;
 
 FILE* file = fopen( filename, "r" );
 if( !file ) return -1;

 skipComments( file );

 int c, rowCount = 0;

 do
   {
     c = getc( file );

     if( c == eol )  rowCount++;
   }
 while( c!=EOF );
 
 fclose( file );
 return rowCount;
}

int getFileRowsCols( const String& filename, int& rows, int& cols )
{
  rows = getFileRows( filename );
  cols = getFileCols( filename );

  if( rows==-1 || cols == -1 ) 
    return -1;
  else
    return 0;
}


int readOneCol( FILE* file, double* arr, int count )
{
  for( int i=0; i<count; i++ )
    {
      if( fscanf( file, " %le", arr+i )!=1 )
	{
	  cerr << "Invalid input error!" << i+1 << "(";
	  for( int j=0; j<10; j++ ) cerr << char( getc( file) );
	  cerr << endl; 
	}
    }
  skipLine( file );

  return peek( file );
}

int readFileCol( const String& filename, int col, double* arr, int filecols, int maxRows )
{
  if( filecols == -1 ) filecols = getFileCols( filename );
  if( filecols == -1 ) return -1;

  FILE* file = fopen( filename, "r" );
  if( !file ) return -1;

  skipComments( file );
  
  double buffer[ col+1 ];
  int index=0;
  
  while( TRUE )
    {
      int finished = (readOneCol( file, buffer, col+1 )==EOF);
      
      arr[ index ] = buffer[ col ];
      index++;

      if( finished || index==maxRows ) break;
    }
  
  fclose( file );
  
  return 0;
}



int readFileCols( const char* filename, int cols, double** x )
{
  FILE* file = fopen( filename, "r" );
  if( !file ) return -1;

  skipComments( file );
  
  double buffer[ cols ];
  int index=0;

  while( TRUE )
    {
      int finished = (readOneCol( file, buffer, cols )==EOF);
      
      for( int i=0; i<cols; i++ )
	if( x[i] ) x[i][index]=buffer[i];

      index++;
      if( finished ) break;
    }
  
  fclose( file );
  
  return 0;
}


int readFileColsInc(  const char* filename, int minCol, ... )
{
  int cols = getFileCols( filename );
  double* x[cols];
  for( int i=0; i<cols; i++ ) x[i]=NULL;

  va_list argptr;
  va_start( argptr, minCol );
  do
    {
      double* px = va_arg( argptr, double* );
      if( !px ) break;
      if( minCol==cols )
	{
	  cerr << "Argumentlist for readFileColsInc not NULL terminated !" << endl;
	  exit(1);
	}

      x[minCol++] = px;
    }
  while( TRUE );
  
 va_end( argptr );

 return readFileCols( filename, cols, x );
}


int readFileColsNum( const char* filename, ... )
{
  int cols = getFileCols( filename );
  double* x[cols];
  for( int i=0; i<cols; i++ ) x[i]=NULL;

  va_list argptr;
  va_start( argptr, filename );
  do
    {
      double* px = va_arg( argptr, double* );
      if( !px ) break;

      int nx = va_arg( argptr, int );

      x[nx] = px;
    }
  while( TRUE );
  
 va_end( argptr );

 return readFileCols( filename, cols, x );
}

















