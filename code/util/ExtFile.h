// ;-*-C++-*-
// tells emacs to use C++-mode instead of C-mode

#ifndef __EXFILE_H__
#define __EXFILE_H__


boolean fileExists( const String& filename );

int getFileRows( const String& filename );
int getFileCols( const String& filename );
int getFileRowsCols( const String& filename, int& rows, int& cols );


int readFileCol( const String& filename, int col, double* arr, int filecols=-1, int maxRows=-1 );

int readFileCols(  const char* filename, int numCols, double** x );
int readFileColsInc(  const char* filename, int minCol, ... );
int readFileColsNum(  const char* filename, ... );

#endif




























