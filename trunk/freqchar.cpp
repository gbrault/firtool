
#include "math.h"
#include "fftw.h"


void freqChar( long double * T, long double * F, int n, int m ) {
    fftwl_complex R[ m ] ;

    for ( int i = 0 ; i < m ; i += 1 )
        R[ i ][ 0 ] = R[ i ][ 1 ] = 0.0L ;

    for ( int i = 0 ; i < n / 2 ; i += 1 )
        R[ m - n / 2 + i ][ 0 ] = T[ i ] ;

    for ( int i = n / 2 ; i < n ; i += 1 )
        R[ 0 - n / 2 + i ][ 0 ] = T[ i ] ;

    fftf( R, (fftwl_complex *)F, m ) ;
}

void freqChar2( long double * T, long double * F, int n, int m ) {
    long double t = (long double)M_PI * 2.0L / m ;

    for ( int i = 0 ; i < m ; i += 1 ) {
        long double theta = t * i ;
        long double sac = 0.0L ;
        long double sas = 0.0L ;
        for ( int k = 0 ; k < n ; k += 1 ) {
            sac = sac + cos( theta * k ) * T[ k ] ;
            sas = sas + sin( theta * k ) * T[ k ] ;
        }
        F[ 2 * i + 0 ] = sac ;
        F[ 2 * i + 1 ] = sas ;
    }
}


void magnitude( long double * F, double * M, int n, bool log ) {
    long double max = 0.0L ;

    for ( int i = 0 ; i < n ; i += 1 ) {
        M[ i ] = F[ 2 * i + 0 ] * F[ 2 * i + 0 ] + F[ 2 * i + 1 ] * F[ 2 * i + 1 ] ;
        if ( max < fabsl( M[ i ] ) )
            max = fabsl( M[ i ] ) ;
    }
    if ( log )
        for ( int i = 0 ; max > 0.0 && i < n ; i += 1 )
            M[ i ] = 10 * log10( M[ i ] / max ) ;
    else
        for ( int i = 0 ; max > 0.0 && i < n ; i += 1 )
            M[ i ] = M[ i ] / max ;
}

void phase( long double * F, double * P, int n ) {
    for ( int i = 0 ; i < n ; i += 1 )
        P[ i ] = atan2l( F[ 2 * i + 1 ], F[ 2 * i + 0 ] ) ;
}

void group( double * P, double * D, int n ) {
    D[ 0 ] = 0.0 ;
    for ( int i = 1 ; i < n ; i += 1 )
        D[ i ] = P[ i ] - P[ i - 1 ] ;
}

