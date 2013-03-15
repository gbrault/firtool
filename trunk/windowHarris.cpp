
#include <math.h>

void harris( long double * W, int aLen ) {
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] =
            +0.35875L +
            -0.48829L * cosl( 2.0L * M_PI * k / ( aLen - 1 ) ) +
            +0.14128L * cosl( 4.0L * M_PI * k / ( aLen - 1 ) ) +
            -0.01168L * cosl( 6.0L * M_PI * k / ( aLen - 1 ) ) +
            +0.00000L * cosl( 8.0L * M_PI * k / ( aLen - 1 ) ) ;
}

void nuttall( long double * W, int aLen ) {
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] =
            +0.3635819L +
            -0.4891775L * cosl( 2.0L * M_PI * k / ( aLen - 1 ) ) +
            +0.1365995L * cosl( 4.0L * M_PI * k / ( aLen - 1 ) ) +
            -0.0106411L * cosl( 6.0L * M_PI * k / ( aLen - 1 ) ) +
            +0.0000000L * cosl( 8.0L * M_PI * k / ( aLen - 1 ) ) ;
}

void flattop( long double * W, int aLen ) {
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] =
            +1.000L +
            -1.930L * cosl( 2.0L * M_PI * k / ( aLen - 1 ) ) +
            +1.290L * cosl( 4.0L * M_PI * k / ( aLen - 1 ) ) +
            -0.388L * cosl( 6.0L * M_PI * k / ( aLen - 1 ) ) +
            +0.028L * cosl( 8.0L * M_PI * k / ( aLen - 1 ) ) ;
}
