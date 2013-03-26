#ifndef FILTERS_H
#define FILTERS_H

void lowPass( long double * T, double stop_freq, long double * W, int aLen ) ;
void highPass( long double * T, double start_freq, long double * W, int aLen ) ;
void bandPass( long double * T, double start_freq, double stop_freq, long double * W, int aLen ) ;
void bandStop( long double * T, double stop_freq, double start_freq, long double * W, int aLen ) ;
void differentiator( long double * T, double start_freq, double stop_freq, long double * W, int aLen ) ;
void gaussian( long double * T, double spb, double bt, int nLen ) ;
void rootRaisedCosine( long double * T, double spb, double alpha, int nLen ) ;

#endif // FILTERS_H
