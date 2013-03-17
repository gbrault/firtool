
#include <math.h>
#include <windowRifeVincent.h>
#include <QDebug>

// Class II weighting functions (Taylor)
// according to BSTJ Feb. 1970, p. 207-209

static void taylor( long double D[], int M, double aAtten ) {
    double R = pow( 10.0, aAtten / 20.0 ) ;
    long double L = log( R + sqrt( R * R - 1.0 ) ) / M_PI ; // (48)
    long double L2 = L * L ;

    long double M_1 = M + 1.0 ;
    long double M_5 = M + 0.5 ;
    long double sigma2 = M_1 * M_1 / ( L * L + sqrtl( L2 + M_5 * M_5 ) ) ; // (47)

    D[ 0 ] = 1.0L ;
    for ( int n = 1 ; n < M ; n += 1 ) { // (45)
        long double dp = 1.0L ;
        long double np = 1.0L ;
        long double n2 = n * n ;
        for ( int K = 1 ; K < M ; K += 1 ) {
            long double K2 = K * K ;
            if ( K != n )
                dp *= 1.0L - n2 / K2 ;

            long double K_5 = K - 0.5L ;
            np *= 1.0L - n2 / sigma2 / ( L2 + K_5 * K_5 )  ;
        }
        D[ n ] = - np / dp ;
        qDebug() << n << (double)D[ n ] ;
    }
}

void rifeVincentII( long double * W, int aLen, double aAtten, int M ) {
    qDebug() << M ;
    long double D[ M ] ;
    taylor( D, M, aAtten ) ;
    for ( int k = 0 ; k < aLen ; k += 1 ) {
        W[ k ] = D[ 0 ] ;
        for ( int m = 1 ; m < M ; m += 1 )
            W[ k ] += D[ m ] * cosl( 2.0L * m * M_PI * k / ( aLen - 1 ) ) ;
    }
}


// Class I and III
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


