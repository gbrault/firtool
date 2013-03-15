#ifndef FILTERS_H
#define FILTERS_H

void lowPass( double * T, double stop_freq, double * W, int aLen ) ;
void highPass( double * T, double start_freq, double * W, int aLen ) ;
void bandPass( double * T, double start_freq, double stop_freq, double * W, int aLen ) ;
void bandStop( double * T, double stop_freq, double start_freq, double * W, int aLen ) ;
void gaussian( double * T, double spb, double bt, int nLen ) ;
void rootRaisedCosine( double * T, double spb, double alpha, int nLen ) ;

#endif // FILTERS_H
