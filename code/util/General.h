#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <assert.h>
#include <stdlib.h>
#include <String.h>


typedef int boolean;
typedef String string;


#define _DEBUG

#ifdef _DEBUG
  #define ASSERT( _val ) assert( _val )
#else
  #define ASSERT( _val )
#endif

#ifndef NULL
#define NULL (0)
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif


#ifdef INTERFACE
#include <Gpfile.h>
#include <ExtGetOpt.h>
#endif

#ifdef ALGORITHM
#include <iostream.h>
#include <fstream.h>
#include <Gpfile.h>
#include <ExtFile.h>
#include "nrutil.h"
#endif

#ifdef UTILITY
#endif


#define DEFAULT_CONFIG "~/.tsConfig"


const char tab = '\t';
const char eol = '\n';
const char car = '\r';
const char lif = '\n';

string toString( int x);

double minRound( double min, double range, double add );
double maxRound( double min, double range, double add );
void minmaxRound( double& min, double& max, double add );

#endif // __GENERAL_H__
