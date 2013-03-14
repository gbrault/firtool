
#include <math.h>

void harris( double * W, int aLen ) {
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] =
            +0.35875 +
            -0.48829 * cos( 2 * M_PI * k / ( aLen - 1 ) ) +
            +0.14128 * cos( 4 * M_PI * k / ( aLen - 1 ) ) +
            -0.01168 * cos( 6 * M_PI * k / ( aLen - 1 ) ) +
            +0.00000 * cos( 8 * M_PI * k / ( aLen - 1 ) ) ;
}

void nuttall( double * W, int aLen ) {
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] =
            +0.3635819 +
            -0.4891775 * cos( 2 * M_PI * k / ( aLen - 1 ) ) +
            +0.1365995 * cos( 4 * M_PI * k / ( aLen - 1 ) ) +
            -0.0106411 * cos( 6 * M_PI * k / ( aLen - 1 ) ) +
            +0.0000000 * cos( 8 * M_PI * k / ( aLen - 1 ) ) ;
}

void flattop( double * W, int aLen ) {
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] =
            +1.000 +
            -1.930 * cos( 2 * M_PI * k / ( aLen - 1 ) ) +
            +1.290 * cos( 4 * M_PI * k / ( aLen - 1 ) ) +
            -0.388 * cos( 6 * M_PI * k / ( aLen - 1 ) ) +
            +0.028 * cos( 8 * M_PI * k / ( aLen - 1 ) ) ;
}

void rifeVincent( double * W, int aLen ) {
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] =
            +35.0 / 128 +
            -56.0 / 128 * cos( 2 * M_PI * k / ( aLen - 1 ) ) +
            +28.0 / 128 * cos( 4 * M_PI * k / ( aLen - 1 ) ) +
            - 8.0 / 128 * cos( 6 * M_PI * k / ( aLen - 1 ) ) +
            + 1.0 / 128 * cos( 8 * M_PI * k / ( aLen - 1 ) ) ;
}
