
#include <math.h>

void harris( double * W, int aLen, double aAtten ) {
    (void) aAtten ;
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] = 0.35875 - 0.48829 * cos( 2 * M_PI * k / ( aLen - 1 ) ) + 0.14128 * cos( 4 * M_PI * k / ( aLen - 1 ) )
          - 0.01168 * cos( 6 * M_PI * k / ( aLen - 1 ) ) ;
}

