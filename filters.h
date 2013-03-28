#ifndef FILTERS_H
#define FILTERS_H

void lowPass( ld_t * T, double stop_freq, ld_t * W, int aLen ) ;
void highPass( ld_t * T, double start_freq, ld_t * W, int aLen ) ;
void bandPass( ld_t * T, double start_freq, double stop_freq, ld_t * W, int aLen ) ;
void bandStop( ld_t * T, double stop_freq, double start_freq, ld_t * W, int aLen ) ;
void differentiator( ld_t * T, double start_freq, double stop_freq, ld_t * W, int aLen ) ;
void gaussian( ld_t * T, double spb, double bt, int nLen ) ;
void rootRaisedCosine( ld_t * T, double spb, double alpha, int nLen ) ;

#endif // FILTERS_H
