
#include <math.h>
#include "fftw.h"

void cheb( fftwl_complex y[], long double alpha,  int n ) {
    for ( int i = 0 ; i < n ; i += 1, y++ ) {
        long double a = fabsl( alpha * cosl( (long double)M_PI * i / n ) ) ;
        if ( a > 1.0L )
            (*y)[ 0 ] = powl( -1.0L, i ) * coshl( acoshl( a ) * n ) ;
        else
            (*y)[ 0 ] = powl( -1.0L, i ) * cosl( acosl( a ) * n ) ;
        (*y)[ 1 ] = 0.0 ;
    }
}

void chebyshev( long double * W, int aLen, double aAtten ) {
    if ( aLen < 0 )
        return ;
    else if ( aLen == 1 )
        W[ 0 ] = 1 ;
    else {
        int M = aLen - 1 ;
        long double alpha = coshl( acoshl( powl( 10.0L, aAtten / 20.0L ) ) / M ) ;

        fftwl_complex y[ aLen ] ;
        cheb( y, alpha, M ) ;

        fftwl_complex z[ aLen ] ;
        fftb( y, z, M ) ;

        z[ 0 ][ 0 ] = z[ 0 ][ 0 ] / 2 ;
        z[ M ][ 0 ] = z[ 0 ][ 0 ] ;
        for ( int i = 0 ; i < aLen ; i += 1 )
            W[ i ] = z[ i ][ 0 ] / z[ M / 2 ][ 0 ] ;
    }
}
