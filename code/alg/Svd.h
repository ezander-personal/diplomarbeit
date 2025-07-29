// ;-*-C++-*-
// tells emacs to use C++-mode instead of C-mode

#ifndef __SVD_H__
#define __SVD_H__

void svd( const String& ifilename, const String& ofilename, int window, boolean nosort );
void svdrec( const String& ifilename, const String& vfilename, const String& ofilename, int dimension, int components, boolean scale, boolean lines );

#endif

