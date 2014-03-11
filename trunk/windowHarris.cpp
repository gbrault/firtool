
#include <math.h>
#include "double.h"

void harris4( ld_t * W, int aLen ) {
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] =
            +0.35875L +
            -0.48829L * cosl( 2.0L * M_PI * k / ( aLen - 1 ) ) +
            +0.14128L * cosl( 4.0L * M_PI * k / ( aLen - 1 ) ) +
            -0.01168L * cosl( 6.0L * M_PI * k / ( aLen - 1 ) ) +
            +0.00000L * cosl( 8.0L * M_PI * k / ( aLen - 1 ) ) ;
}

void harris7( ld_t * W, int aLen ) {
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] = 0.2712203606 +
            -0.4334446123  * cosl(  2.0L * M_PI * k / ( aLen - 1 ) ) +
            +0.21800412    * cosl(  4.0L * M_PI * k / ( aLen - 1 ) ) +
            -0.0657853433  * cosl(  6.0L * M_PI * k / ( aLen - 1 ) ) +
            +0.0107618673  * cosl(  8.0L * M_PI * k / ( aLen - 1 ) ) +
            -0.0007700127  * cosl( 10.0L * M_PI * k / ( aLen - 1 ) ) +
            +0.00001368088 * cosl( 12.0L * M_PI * k / ( aLen - 1 ) ) ;
}

void nuttall( ld_t * W, int aLen ) {
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] =
            +0.3635819L +
            -0.4891775L * cosl( 2.0L * M_PI * k / ( aLen - 1 ) ) +
            +0.1365995L * cosl( 4.0L * M_PI * k / ( aLen - 1 ) ) +
            -0.0106411L * cosl( 6.0L * M_PI * k / ( aLen - 1 ) ) +
            +0.0000000L * cosl( 8.0L * M_PI * k / ( aLen - 1 ) ) ;
}

void flattop( ld_t * W, int aLen ) {
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] =
            +1.000L +
            -1.930L * cosl( 2.0L * M_PI * k / ( aLen - 1 ) ) +
            +1.290L * cosl( 4.0L * M_PI * k / ( aLen - 1 ) ) +
            -0.388L * cosl( 6.0L * M_PI * k / ( aLen - 1 ) ) +
            +0.028L * cosl( 8.0L * M_PI * k / ( aLen - 1 ) ) ;
}

void connes( ld_t * W, int aLen ) {
    int n = aLen / 2 ;
    int p = ( aLen + 1 ) / 2 ;

    int l = aLen - 1 ;
    for ( int k = 0 ; k < n ; k += 1, l -= 1 ) {
        W[ k ] = powl( 1.0L - powl( ( (ld_t)k - n ) / p, 2 ), 2 ) ;
        W[ l ] = W[ k ] ;
    }
}
