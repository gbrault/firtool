
#include "math.h"
#include "double.h"

static ld_t I0( ld_t x ) {
    ld_t d = 0.0 ;
    ld_t ds = 1.0 ;
    ld_t s = 1.0 ;
    do {
        d += 2.0L ;
        ds *= x * x / ( d * d ) ;
        s += ds ;
    } while ( ds > s * 1E-300L ) ;
    return s ;
}

void kaiser( ld_t * W, int aLen, double beta ) {
    ld_t den = I0( M_PI * beta ) ;
    int nOn2 = aLen / 2 ;

    W[ nOn2 ] = 1 ;
    for ( int j = 1 ; j < nOn2 ; j += 1 ) {
        double t = I0( (ld_t)M_PI * beta * sqrt( 1.0L - (ld_t)(j * j) / (ld_t)( nOn2 * nOn2 ) ) ) ;
        W[ nOn2 + j ] = W[ nOn2 - j ] = 1 * t / den ;
    }
}

