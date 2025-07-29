// ;-*-C++-*-
// tells emacs to use C++-mode instead of C-mode

#ifndef __FUELL_H__
#define __FUELL_H__

  // f�r verschiedene Einbettungsdimensionen d und eine jeweils konstante Menge
  // Verz�gerungszeiten t aus (t1, t2, ... tn ) wird jeweils n mal folgendes 
  // gemacht
  //
  //   aus der Zeitreihe werden d Vektoren v1..vd zuf�llig ausgew�hlt und das Volumen
  //   das dieses Paralellepipeds aus det(v1,...,vd) bestimmt
  //   diese Volumina werden aufsummiert
  //
  // das Volumen wird durch das Volumen des den Attraktor umfassenden Hyperkubus
  // geteilt (und evtl. logarithmiert)


void fuell( const String& ifilename, const String& _ofilename, int maxDim, int minDim, int maxTau, int count );

void fuelld( const String& _ifilename, const String& ofilename, int tau_a, int tau_e );

#endif

