// ;-*-C++-*-
// tells emacs to use C++-mode instead of C-mode

#ifndef __EVL_H__
#define __EVL_H__

#include <String.h>

#define COMPARE_TYPE 0
#define COMPARE_POS 1
#define COMPARE_VALUE 2

void evl( const String& ifilename, int column, int compare, boolean shortDisp );

#endif







