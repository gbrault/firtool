
#include "math.h"
#include "fftw.h"


void freqChar( double * T, double * F, int n, int m ) {
    fftw_complex R[ m ] ;
    double max = fabs( T[ n / 2 ] ) ;

    for ( int i = 0 ; i < m ; i += 1 )
        R[ i ][ 0 ] = R[ i ][ 1 ] = 0.0 ;

    R[ 0 ][ 0 ] = T[ n / 2 ] / max ;

    for ( int i = 1 ; i <= n / 2 ; i += 1 )
        R[ i ][ 0 ] = R[ m - i ][ 0 ] = T[ n / 2 + i ] / max ;

    fftf( R, (fftw_complex *)F, m ) ;
}

void magnitude( double * F, double * M, int n) {
    double max = 0.0 ;

    for ( int i = 0 ; i < n ; i += 1 ) {
        M[ i ] = F[ 2 * i + 0 ] * F[ 2 * i + 0 ] + F[ 2 * i + 1 ] * F[ 2 * i + 1 ] ;
        if ( max < fabs( M[ i ] ) )
            max = fabs( M[ i ] ) ;
    }
    for ( int i = 0 ; i < n ; i += 1 )
        M[ i ] = 10 * log10( M[ i ] / max ) ;
}

void phase( double * F, double * P, int n ) {
    for ( int i = 0 ; i < n ; i += 1 )
        P[ i ] = atan2( F[ 2 * i + 1 ], F[ 2 * i + 0 ] ) ;
}

void group( double * P, double * D, int n ) {
    D[ 0 ] = 0.0 ;
    for ( int i = 1 ; i < n ; i += 1 )
        D[ i ] = P[ i ] - P[ i - 1 ] ;
}

