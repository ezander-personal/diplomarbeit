// ;-*-C++-*-
// tells emacs to use C++-mode instead of C-mode

#ifndef __EXTGETOPT_H__
#define __EXTGETOPT_H__

#include <String.h>
#include <time.h>


struct optionEntry;

class ExtGetOpt
{
  int argc;
  char** argv;

  String prgDesc;

  String optText;
  String optDesc;

  optionEntry *firstEntry, *lastEntry;

  clock_t start, end; 
  
private:
  void insertEntry( optionEntry* entry );
  void deleteEntries();
  boolean checkEntries();
  optionEntry* getEntry( char c );

  void displaySyntax();
  void displayExplanation();

public:
  ExtGetOpt( int _argc, char** _argv );
  ~ExtGetOpt();
  
  void descr( const String& str );

  void value( char optchar, String* var, const char* optName, const char* optExp, boolean always=FALSE );
  void value( char optchar, int* var, const char* optName, const char* optExp, boolean always=FALSE );
  void value( char optchar, double* var, const char* optName, const char* optExp, boolean always=FALSE );
  void value( char optchar, char* var, const char* optName, const char* optExp, boolean always=FALSE );

  void values( char optchar, int count, int* var, const char* optName, const char* optExp, boolean always=FALSE );
  void values( char optchar, int count, double* var, const char* optName, const char* optExp, boolean always=FALSE );


  void option( char optchar, boolean* var, const char* optName, const char* optExp );
  
  void error( boolean full );

  int evaluate( boolean deleteAfter = FALSE );

  void writeInfo( const String& filename );
};






#endif

