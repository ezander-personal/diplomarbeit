// ;-*-C++-*-
// tells emacs to use C++-mode instead of C-mode

#ifndef __NEURAL_H__
#define __NEURAL_H__

void neural( const String& ifilename, const String& ofilename, int inputs, int hidden, int samples, int max_training,  double learning_rate, double momentum, bool random);

#endif

