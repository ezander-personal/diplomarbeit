// ;-*-C++-*-
// tells emacs to use C++-mode instead of C-mode


#ifndef __RUNGE_H__
#define __RUNGE_H__

void rkInitVectors( int dimension );

void rkStep( const vector& vec, vector& newvec, const vector& params, vectorFunction f, double step, int stepCount );

#endif // __RUNGE_H__
