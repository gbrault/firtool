#ifndef WINDOWRIFEVINCENT_H
#define WINDOWRIFEVINCENT_H

typedef enum _RV {
    RV_I1 = 0, RV_I2, RV_I3, RV_I4,
    RV_III1, RV_III2, RV_III3, RV_III4
} RV_t ;

void rifeVincentII( long double * W, int aLen , double aAtten, int M ) ;
void rifeVincent( RV_t type, long double * W, int aLen ) ;


#endif // WINDOWRIFEVINCENT_H
