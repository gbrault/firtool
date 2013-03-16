
#include <math.h>
#include <QDebug>

void taylor( long double * W, int aLen, double aAtten ) {
    int nprime = 8 ;

    double x = pow( 10.0, aAtten / 20.0 ) ;
    double A = log( x + sqrt ( x * x - 1.0 ) ) / M_PI ;

    double np_5 = nprime - 0.5 ;
    double sigma = (double)nprime / sqrt( A * A + np_5 * np_5 ) ;

    double Fm[ nprime ] ;
    Fm[ 0 ] = 0.0 ;
    for ( int m = 1 ; m < nprime ; m += 1 ) {
        double dp = 1.0 ;
        double np = 1.0 ;
        for ( int n = 1 ; n < nprime ; n += 1 ) {
            if ( n != m )
                dp *= 1.0 - m * m / n * n ;

            double n_5 = n - 0.5 ;
            np *= 1.0 - m * m / ( A * A + n_5 * n_5 ) / sigma / sigma ;
        }
        Fm[ m ] = ( m % 2 ? 1.0 : -1.0 ) * np / dp ;
        qDebug() << m << Fm[ m ] ;
    }

    for ( int i = 0 ; i < aLen ; i += 1, W++ ) {
        *W = 1.0 ;
        for ( int m = 1 ; m < nprime ; m += 1 )
            *W += 2 * Fm[ m ] * -cos( 2.0 * m * M_PI * i / aLen ) ;
    }
}

