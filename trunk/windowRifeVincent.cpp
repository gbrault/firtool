
#include <math.h>
#include <windowRifeVincent.h>

void rifeVincent( RV_t type, long double * W, int aLen ) {
    switch ( type ) {
    case RV_I1 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                + 1.0L / 2 +
                - 1.0L / 2 * cosl( 2.0L * M_PI * k / ( aLen - 1 ) ) ;
        break ;
    case RV_I2 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                + 3.0L / 8 +
                - 4.0L / 8 * cosl( 2.0L * M_PI * k / ( aLen - 1 ) ) +
                + 1.0L / 8 * cosl( 4.0L * M_PI * k / ( aLen - 1 ) ) ;
        break ;
    case RV_I3 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                +10.0L / 32 +
                -15.0L / 32 * cosl( 2.0L * M_PI * k / ( aLen - 1 ) ) +
                + 6.0L / 32 * cosl( 4.0L * M_PI * k / ( aLen - 1 ) ) +
                - 1.0L / 32 * cosl( 6.0L * M_PI * k / ( aLen - 1 ) ) ;
        break ;
    case RV_I4 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                +35.0L / 128 +
                -56.0L / 128 * cosl( 2.0L * M_PI * k / ( aLen - 1 ) ) +
                +28.0L / 128 * cosl( 4.0L * M_PI * k / ( aLen - 1 ) ) +
                - 8.0L / 128 * cosl( 6.0L * M_PI * k / ( aLen - 1 ) ) +
                + 1.0L / 128 * cosl( 8.0L * M_PI * k / ( aLen - 1 ) ) ;
        break ;
    case RV_III1 :
        break ;
    case RV_III2 :
        break ;
    case RV_III3 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                +0.9999992L / 2.9950724 +
                -1.4359600L / 2.9950724 * cosl( 2.0L * M_PI * k / ( aLen - 1 ) ) +
                +0.4975370L / 2.9950724 * cosl( 4.0L * M_PI * k / ( aLen - 1 ) ) +
                -0.0615762L / 2.9950724 * cosl( 6.0L * M_PI * k / ( aLen - 1 ) ) ;
            break ;
    case RV_III4 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                +1.0035479L / 3.493834 +
                -1.5662720L / 3.493834 * cos( 2.0L * M_PI * k / ( aLen - 1 ) ) +
                +0.7254480L / 3.493834 * cos( 4.0L * M_PI * k / ( aLen - 1 ) ) +
                -0.1806450L / 3.493834 * cos( 6.0L * M_PI * k / ( aLen - 1 ) ) +
                +0.0179211L / 3.493834 * cos( 8.0L * M_PI * k / ( aLen - 1 ) ) ;
        break ;
    }
}


