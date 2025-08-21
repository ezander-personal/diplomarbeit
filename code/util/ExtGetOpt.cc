// #include <GetOpt.h>
#include <signal.h>
#include <fstream.h>
#include <stdlib.h>
#include <string.h>
#include <GetOpt.h>
#include <utime.h>

#include "General.h"
#include "ExtGetOpt.h"


#define TSTRING 0
#define TBOOL   1
#define TINT    2
#define TDOUBLE 3
#define TCHAR   4
#define TINTARR 5
#define TDBLARR 6
 
struct optionEntry
{

  optionEntry( char optchar, String* var, const char* optName, const char* optExp, boolean always );
  optionEntry( char optchar, double* var, const char* optName, const char* optExp, boolean always );
  optionEntry( char optchar, char* var, const char* optName, const char* optExp, boolean always );
  optionEntry( char optchar, int* var, const char* optName, const char* optExp, boolean always, boolean isBool=FALSE );

  optionEntry( char optchar, int count, int* var, const char* optName, const char* optExp, boolean always );
  optionEntry( char optchar, int count, double* var, const char* optName, const char* optExp, boolean always );

  int type;
  char optchar;
  int  arrayCount;

  union
  {
    String* pStr;
    int* pInt;
    boolean* pBool;
    double* pDouble;
    char* pChar;
  };

  boolean always, ok;  

  String optName, optExp;

  optionEntry* next;
};


optionEntry::optionEntry( char _optchar, String* var, const char* _optName, const char* _optExp,  boolean _always )
{
  type = TSTRING; optchar = _optchar; always=_always; ok = !_always;
  pStr = var;
  optName = _optName;
  optExp = _optExp;
  arrayCount = 0;
}

optionEntry::optionEntry( char _optchar, double* var, const char* _optName, const char* _optExp, boolean _always )
{
  type = TDOUBLE; optchar = _optchar; always=_always; ok = !_always;
  pDouble = var;
  optName = _optName;
  optExp = _optExp;
  arrayCount = 0;
}

optionEntry::optionEntry( char _optchar, char* var, const char* _optName, const char* _optExp, boolean _always )
{
  type = TCHAR; optchar = _optchar; always=_always; ok = !_always;
  pChar = var;
  optName = _optName;
  optExp = _optExp;
  arrayCount = 0;
}

optionEntry::optionEntry( char _optchar, int* var, const char* _optName, const char* _optExp, boolean _always, boolean isBool )
{
  optchar = _optchar; always=_always; ok = !_always;
  if( isBool )
    {
      type = TBOOL; 
      pBool = var;
    }
  else
    {
      type = TINT;
      pInt = var;
    }
  optName = _optName;
  optExp = _optExp;
  arrayCount = 0;
}

optionEntry::optionEntry( char _optchar, int count, double* var, const char* _optName, const char* _optExp, boolean _always )
{
  type = TDBLARR; optchar = _optchar; always=_always; ok = !_always;
  pDouble = var;
  optName = _optName;
  optExp = _optExp;
  arrayCount = count;
}

optionEntry::optionEntry( char _optchar, int count, int* var, const char* _optName, const char* _optExp, boolean _always )
{
  type = TINTARR; optchar = _optchar; always=_always; ok = !_always;
  pInt = var;
  optName = _optName;
  optExp = _optExp;
  arrayCount = count;
}





ExtGetOpt::ExtGetOpt( int _argc, char** _argv )
{
  argc = _argc;
  argv = _argv;
  lastEntry = firstEntry = NULL;
  optText = "-:";
}

ExtGetOpt::~ExtGetOpt( )
{
  deleteEntries();
}


void ExtGetOpt::insertEntry( optionEntry* entry )
{
  if( lastEntry ) lastEntry->next = entry;
  entry->next = NULL;
  lastEntry = entry;

  if( !firstEntry ) firstEntry=entry;
}

void ExtGetOpt::deleteEntries()
{
  while( firstEntry )
    {
      optionEntry* act = firstEntry;
      firstEntry =  act->next;
      delete act;
    }
  lastEntry = NULL;
}

boolean ExtGetOpt::checkEntries()
{
  optionEntry* act = firstEntry;
  while( act )
    {
      if( !act->ok ) return FALSE;

      act = act->next;
    }

  return TRUE;
}

optionEntry* ExtGetOpt::getEntry( char c )
{
  optionEntry* act = firstEntry;
  while( act )
    {
      if( act->optchar == c ) return act;

      act = act->next;
    }

  return NULL;
}

void ExtGetOpt::displaySyntax()
{
  String fname = argv[0];
  while( fname.contains('/') ) fname = fname.after('/');

  String syntax = "usage:   \t" + fname;

  optionEntry* act = firstEntry;
  while( act )
    {
      syntax += ' ';
      if( !act->always ) syntax += '[';
      syntax += '-';
      syntax += act->optchar;

      if( act->optName.length() ) syntax += " " + act->optName;
      
      if( !act->always ) syntax += ']';

      act = act->next;
    }

  syntax += " [--help] [--nohup]";

  cerr << syntax << endl;
}


string formatGetOptString( String& str, char c, const String& repl )
{
  String ret;

  if( str.index( c ) )
    {
      int start=0, end=0;
      do
	{
	  end = str.index( c, start );
	  if( end == -1 ) end=str.length();
	  
	  if( start ) ret += repl;
	  ret += str.at( start, end-start );
	  
	  start = end+1;
	}
      while( start<(int)str.length() );
    }
  else
    ret += str;

  return ret;
}

void ExtGetOpt::displayExplanation()
{
  cerr << endl;
  if( prgDesc.length() )
    {
      cerr << "function:\t" << formatGetOptString( prgDesc, '#', "\n\t\t" ) << endl;
      cerr << endl;
    }

  cerr << "options: \t";
  boolean first=TRUE;
  optionEntry* act = firstEntry;
  while( act )
    {
      if( act->optExp.length() )
	{
	  String expl;
	  if( !first ) expl="          \t";
	  first=FALSE;

	  expl += act->optchar;
	  expl += ": ";

	  expl += formatGetOptString( act->optExp, '#', "\n\t\t   " );
	  
	  cerr << expl << endl;
	}

      act = act->next;
    }

  cerr << endl;
}



void ExtGetOpt::descr( const String& str )
{
  prgDesc = str;
}


void ExtGetOpt::value( char optchar, String* var, const char* optName, const char* optExp, boolean always )
{
  insertEntry( new optionEntry( optchar, var, optName, optExp, always ) );
  optText+=optchar;
  optText+=':';
}

void ExtGetOpt::value( char optchar, int* var, const char* optName, const char* optExp, boolean always )
{
  insertEntry( new optionEntry( optchar, var, optName, optExp, always ) );
  optText+=optchar;
  optText+=':';
}

void ExtGetOpt::value( char optchar, double* var, const char* optName, const char* optExp, boolean always )
{
  insertEntry( new optionEntry( optchar, var, optName, optExp, always ) );
  optText+=optchar;
  optText+=':';
}

void ExtGetOpt::value( char optchar, char* var, const char* optName, const char* optExp, boolean always )
{
  insertEntry( new optionEntry( optchar, var, optName, optExp, always ) );
  optText+=optchar;
  optText+=':';
}

void ExtGetOpt::values( char optchar, int count, int* var, const char* optName, const char* optExp, boolean always )
{
  insertEntry( new optionEntry( optchar, count, var, optName, optExp, always ) );
  optText+=optchar;
  optText+=':';
}

void ExtGetOpt::values( char optchar, int count, double* var, const char* optName, const char* optExp, boolean always )
{
  insertEntry( new optionEntry( optchar, count, var, optName, optExp, always ) );
  optText+=optchar;
  optText+=':';
}


void ExtGetOpt::option( char optchar, boolean* var, const char* optName, const char* optExp )
{
  insertEntry( new optionEntry( optchar, var, optName, optExp, FALSE, TRUE ) );
  optText+=optchar;
}




void readArray( int* arr, int count, const char* arg )
{
  int ind=0;
  const char* ptr = arg;
  while( ind<count )
    {
      arr[ ind ] = atoi( ptr );
      ptr = strchr( ptr, ';' );
      if( !ptr ) break;
      ptr++; ind++;
    }
}

void readArray( double* arr, int count, const char* arg )
{
  int ind=0;
  const char* ptr = arg;
  while( ind<count )
    {
      arr[ ind ] = strtod( ptr, NULL );
      ptr = strchr( ptr, ';' );
      if( !ptr ) break;
      ptr++; ind++;
    }
}

  
void ExtGetOpt::error( boolean full )
{
  displaySyntax();
  if( full ) displayExplanation();
}

int ExtGetOpt::evaluate( boolean deleteAfter )
{
  start = clock();

  GetOpt getopt( argc, argv, (const char*) optText );
  int option_char;

  while( (option_char = getopt()) != EOF )
    {
      switch( option_char )
	{
	case '-':
	  if( !strcmp( "help", getopt.optarg ) ) 
	    {
	      displaySyntax();
	      displayExplanation();
	      return 2;
	    }
	  else if( !strcmp( "nohup", getopt.optarg ) ) 
	    {
	      signal( SIGHUP, SIG_IGN );
	      break;
	    }
	  else
	    {
	      displaySyntax();
	      return 1;
	    }
	case '?':
	  {
	    displaySyntax();
	    return 1;
	  }
	default:
	  {
	    optionEntry* entry = getEntry( option_char );

	    if( !entry )
	      {
		displaySyntax();
		return 1;
	      }
	    
	    switch( entry->type )
	      {
	      case TSTRING: *(entry->pStr) = getopt.optarg; break;
	      case TBOOL:   *(entry->pBool) = TRUE; break;
	      case TINT:    *(entry->pInt) = atoi( getopt.optarg ); break;
	      case TDOUBLE: *(entry->pDouble) = strtod( getopt.optarg, NULL ); break;
	      case TCHAR:   *(entry->pChar) = getopt.optarg[0]; break;
	      case TINTARR: readArray( entry->pInt, entry->arrayCount, getopt.optarg ); break;
	      case TDBLARR: readArray( entry->pDouble, entry->arrayCount, getopt.optarg ); break;
	      }

	    entry->ok = TRUE;
	  }
	}
    }

  boolean ok = checkEntries();

  if( !ok ) displaySyntax();

  if( deleteAfter ) deleteEntries();

  return !ok;
}


void ExtGetOpt::writeInfo( const String& filename )
{
  end = clock();

  if( !firstEntry )
    {
      cerr << "ExtGetOpt:: couldn't write info file, parameter info already deleted" << endl;
      return;
    }

  const String inffile = filename + ".inf";
  ofstream fout( inffile, ios::out | ios::trunc );

  optionEntry* entry = firstEntry;

  while( entry )
    {
      if( entry->type == TBOOL )
	{
	  if( *(entry->pBool ) ) fout << entry->optchar << endl;
	}
      else
	{
	  fout << entry->optchar << ":" << tab;

	  if( entry->pStr )
	    {
	      switch( entry->type )
		{
		case TSTRING: fout << *(entry->pStr); break;
		case TINT:    fout << *(entry->pInt); break;
		case TDOUBLE: fout << *(entry->pDouble); break;
		case TCHAR:   fout << *(entry->pChar); break;
		case TINTARR: cerr << "ExtGetOpt: couldn't write array in info file" << endl; break;
		case TDBLARR: cerr << "ExtGetOpt: couldn't write array in info file" << endl; break;
		}
	    }
	  fout << endl;
	}
      
      entry = entry->next;
    }

  fout << "# Creator:" << tab << argv[0] << endl;
  fout << "# CPUTime:" << tab << ((double)(end-start))/CLOCKS_PER_SEC << endl;

  time_t t = time(0) - (end-start)/CLOCKS_PER_SEC;
  struct utimbuf new_times;
  new_times.actime = t;
  new_times.modtime = t;

  if (utime(inffile, &new_times) != 0) {
    cerr << "Warning: cannot set mod time for inf file: " << inffile << endl;
  }
}















