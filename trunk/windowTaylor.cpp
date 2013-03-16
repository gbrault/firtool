
#include <math.h>
#include <QDebug>

void taylor( long double * W, int aLen, double aAtten ) {
    int M = 4 ;

    double R = pow( 10.0, aAtten / 20.0 ) ;
    qDebug() << R ;
    double L = log( R + sqrt( R * R - 1.0 ) ) / M_PI ;

    double M_1 = M + 1.0 ;
    double M_5 = M + 0.5 ;
    double sigma2 = M_1 * M_1 / ( L * L + sqrt( L * L + M_5 * M_5 ) ) ;

    double D[ M ] ;
    D[ 0 ] = 0.0 ;
    for ( int n = 1 ; n < M ; n += 1 ) {
        double dp = 1.0 ;
        double np = 1.0 ;
        for ( int K = 1 ; K < M ; K += 1 ) {
            if ( K != n )
                dp *= 1.0 - n * n / K * K ;

            double K_5 = K - 0.5 ;
            np *= 1.0 - n * n / sigma2 / ( L + K_5 * K_5 )  ;
        }
        D[ n ] = - np / dp ;
        qDebug() << n << D[ n ] ;
    }

    for ( int i = 0 ; i < aLen ; i += 1, W++ ) {
        *W = 1.0 ;
        for ( int m = 1 ; m < M ; m += 1 )
            *W += 2 * D[ m ] * -cos( 2.0 * m * M_PI * i / aLen ) ;
    }
}

