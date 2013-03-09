
#include "math.h"

static double I0( double x ) {
    double d = 0.0 ;
    double ds = 1.0 ;
    double s = 1.0 ;
    do {
        d += 2.0 ;
        ds *= x * x / ( d * d ) ;
        s += ds ;
    } while ( ds > s * 1E-21 ) ;
    return s ;
}

void kaiser( double * W, int aLen, double aAtten ) {
    double alpha ;

    if ( aAtten < 21 )
        alpha = 0 ;
    else if ( aAtten > 50 )
        alpha = 0.1102 *( aAtten- 8.7 ) ;
    else
        alpha = 0.5842 * pow( ( aAtten - 21 ), 0.4 ) + 0.07886 * ( aAtten - 21 ) ;

    double den = I0( M_PI * alpha ) ;
    int nOn2 = aLen / 2 ;

    W[ nOn2 ] = 1 ;
    for ( int j = 1 ; j < nOn2 ; j += 1 ) {
        double t = I0( M_PI * alpha * sqrt( 1.0 - (double)(j * j) / (double)( nOn2 * nOn2 ) ) ) ;
        W[ nOn2 + j ] = W[ nOn2 - j ] = 1 * t / den ;
    }
}

