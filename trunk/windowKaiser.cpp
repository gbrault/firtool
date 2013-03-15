
#include "math.h"

static long double I0( long double x ) {
    long double d = 0.0 ;
    long double ds = 1.0 ;
    long double s = 1.0 ;
    do {
        d += 2.0L ;
        ds *= x * x / ( d * d ) ;
        s += ds ;
    } while ( ds > s * 1E-300L ) ;
    return s ;
}

void kaiser( long double * W, int aLen, double aAtten ) {
    long double alpha ;

    if ( aAtten < 21.0 )
        alpha = 0.0L ;
    else if ( aAtten > 50.0 )
        alpha = 0.1102L *( aAtten- 8.7 ) ;
    else
        alpha = 0.5842L * pow( ( aAtten - 21.0 ), 0.4 ) + 0.07886 * ( aAtten - 21 ) ;

    long double den = I0( M_PI * alpha ) ;
    int nOn2 = aLen / 2 ;

    W[ nOn2 ] = 1 ;
    for ( int j = 1 ; j < nOn2 ; j += 1 ) {
        double t = I0( (long double)M_PI * alpha * sqrt( 1.0L - (long double)(j * j) / (long double)( nOn2 * nOn2 ) ) ) ;
        W[ nOn2 + j ] = W[ nOn2 - j ] = 1 * t / den ;
    }
}

