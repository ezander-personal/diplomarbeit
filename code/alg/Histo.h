// ;-*-C++-*-
// tells emacs to use C++-mode instead of C-mode

#ifndef __HISTO_H__
#define __HISTO_H__

void histo( const String& ifilename, const String& ofilename, double resolution, boolean isInteger, int col, boolean randomMode );

void histo2d( const String& ifilename, const String& ofilename, double resolution, boolean isInteger, int col, int delay );

#endif

