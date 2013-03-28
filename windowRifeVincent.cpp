
#include <math.h>
#include "double.h"
#include <windowRifeVincent.h>

// Class II weighting functions (Taylor)
// according to BSTJ Feb. 1970, p. 207-209

static void taylor( ld_t D[], int M, double aAtten ) {
    ld_t R = powl( 10.0L, aAtten / 20.0L ) ;
    ld_t L = log( R + sqrtl( R * R - 1.0L ) ) / (ld_t)M_PI ; // (48)
    ld_t L2 = L * L ;

    ld_t M_1 = M + 1.0L ;
    ld_t M_5 = M + 0.5L ;
    ld_t sigma2 = M_1 * M_1 / ( L * L + sqrtl( L2 + M_5 * M_5 ) ) ; // (47)

    D[ 0 ] = 1.0L ;
    for ( int n = 1 ; n < M ; n += 1 ) { // (45)
        ld_t dp = 1.0L ;
        ld_t np = 1.0L ;
        ld_t n2 = n * n ;
        for ( int K = 1 ; K < M ; K += 1 ) {
            ld_t K2 = K * K ;
            if ( K != n )
                dp *= 1.0L - n2 / K2 ;

            ld_t K_5 = K - 0.5L ;
            np *= 1.0L - n2 / sigma2 / ( L2 + K_5 * K_5 )  ;
        }
        D[ n ] = - np / dp ;
    }
}

void rifeVincentII( ld_t * W, int aLen, double aAtten, int M ) {
    ld_t D[ M ] ;
    taylor( D, M, aAtten ) ;
    ld_t Wm = -1E100 ;

    for ( int k = 0 ; k < aLen ; k += 1 ) {
        W[ k ] = D[ 0 ] ;
        for ( int m = 1 ; m < M ; m += 1 )
            W[ k ] += D[ m ] * cosl( 2.0L * m * M_PI * k / ( aLen - 1 ) ) ;
        if ( Wm < fabsl( W[ k ] ) )
            Wm = fabsl( W[ k ] ) ;
    }
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] /= Wm ;
}

// Class I and III
void rifeVincent( RV_t type, ld_t * W, int aLen ) {
    switch ( type ) {
    default :
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
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                + 1.0L / 2 +
                - 1.0L / 2 * cosl( 2.0L * M_PI * k / ( aLen - 1 ) ) ;
        break ;
    case RV_III2 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                +1.0000000L / 2.3937L +
                -1.1968500L / 2.3937L * cosl( 2.0L * M_PI * k / ( aLen - 1 ) ) +
                +0.1968500L / 2.3937L * cosl( 4.0L * M_PI * k / ( aLen - 1 ) ) ;
        break ;
    case RV_III3 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                +0.9999992L / 2.9950724L +
                -1.4359600L / 2.9950724L * cosl( 2.0L * M_PI * k / ( aLen - 1 ) ) +
                +0.4975370L / 2.9950724L * cosl( 4.0L * M_PI * k / ( aLen - 1 ) ) +
                -0.0615762L / 2.9950724L * cosl( 6.0L * M_PI * k / ( aLen - 1 ) ) ;
        break ;
    case RV_III4 :
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] =
                +1.0035479L / 3.493834L +
                -1.5662720L / 3.493834L * cos( 2.0L * M_PI * k / ( aLen - 1 ) ) +
                +0.7254480L / 3.493834L * cos( 4.0L * M_PI * k / ( aLen - 1 ) ) +
                -0.1806450L / 3.493834L * cos( 6.0L * M_PI * k / ( aLen - 1 ) ) +
                +0.0179211L / 3.493834L * cos( 8.0L * M_PI * k / ( aLen - 1 ) ) ;
        break ;
    }
}


