
#include <math.h>
#include <windowRifeVincent.h>

void rifeVincent( RV_t type, double * W, int aLen ) {
    switch ( type ) {
    case RV_I1 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                + 1.0 / 2 +
                - 1.0 / 2 * cos( 2 * M_PI * k / ( aLen - 1 ) ) ;
        break ;
    case RV_I2 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                + 3.0 / 8 +
                - 4.0 / 8 * cos( 2 * M_PI * k / ( aLen - 1 ) ) +
                + 1.0 / 8 * cos( 4 * M_PI * k / ( aLen - 1 ) ) ;
        break ;
    case RV_I3 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                +10.0 / 32 +
                -15.0 / 32 * cos( 2 * M_PI * k / ( aLen - 1 ) ) +
                + 6.0 / 32 * cos( 4 * M_PI * k / ( aLen - 1 ) ) +
                - 1.0 / 32 * cos( 6 * M_PI * k / ( aLen - 1 ) ) ;
        break ;
    case RV_I4 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                +35.0 / 128 +
                -56.0 / 128 * cos( 2 * M_PI * k / ( aLen - 1 ) ) +
                +28.0 / 128 * cos( 4 * M_PI * k / ( aLen - 1 ) ) +
                - 8.0 / 128 * cos( 6 * M_PI * k / ( aLen - 1 ) ) +
                + 1.0 / 128 * cos( 8 * M_PI * k / ( aLen - 1 ) ) ;
        break ;
    case RV_III1 :
        break ;
    case RV_III2 :
        break ;
    case RV_III3 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                +0.9999992 / 2.9950724 +
                -1.43596 / 2.9950724 * cos( 2 * M_PI * k / ( aLen - 1 ) ) +
                +0.497537 / 2.9950724 * cos( 4 * M_PI * k / ( aLen - 1 ) ) +
                -0.0615762 / 2.9950724 * cos( 6 * M_PI * k / ( aLen - 1 ) ) ;
            break ;
    case RV_III4 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                +1.0035479 / 3.493834 +
                -1.5662720 / 3.493834 * cos( 2 * M_PI * k / ( aLen - 1 ) ) +
                +0.7254480 / 3.493834 * cos( 4 * M_PI * k / ( aLen - 1 ) ) +
                -0.1806450 / 3.493834 * cos( 6 * M_PI * k / ( aLen - 1 ) ) +
                +0.0179211 / 3.493834 * cos( 8 * M_PI * k / ( aLen - 1 ) ) ;
        break ;
    }
}


