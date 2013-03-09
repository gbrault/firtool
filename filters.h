#ifndef FILTERS_H
#define FILTERS_H

void chebyshev( double * W, int aLen, double aAtten ) ;
void kaiser( double * W, int aLen, double aAtten ) ;
void harris( double * W, int aLen, double aAtten ) ;

void lowPass( double * T, double stop_freq, double * W, int aLen ) ;
void highPass( double * T, double start_freq, double * W, int aLen ) ;
void bandPass( double * T, double start_freq, double stop_freq, double * W, int aLen ) ;
void bandStop( double * T, double stop_freq, double start_freq, double * W, int aLen ) ;
void gaussian( double * T, double spb, double bt, int nLen ) ;
void rootRaisedCosine( double * T, double spb, double alpha, int nLen ) ;

void freqChar( double * T, double * F, int n, int m ) ;
void magnitude( double * F, double * M, int n ) ;
void phase( double * F, double * P, int n ) ;
void group( double * P, double * D, int n ) ;

#endif // FILTERS_H
