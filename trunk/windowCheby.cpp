
#include <math.h>
#include "fftw.h"

void cheb( fftw_complex y[], double alpha,  int n ) {
    for ( int i = 0 ; i < n ; i += 1, y++ ) {
        double a = fabs( alpha * cos( M_PI * i / n ) ) ;
        if ( a > 1.0 )
            (*y)[ 0 ] = pow( -1, i ) * cosh( n * acosh( a ) ) ;
        else
            (*y)[ 0 ] = pow( -1, i ) * cos( n * acos( a ) ) ;
        (*y)[ 1 ] = 0.0 ;
    }
}

void chebyshev( double * W, int aLen, double aAtten ) {
    if ( aLen < 0 )
        return ;
    else if ( aLen == 1 )
        W[ 0 ] = 1 ;
    else {
        int M = aLen - 1 ;
        double alpha = cosh( acosh( pow( 10.0, aAtten / 20.0 ) ) / M ) ;

        fftw_complex y[ aLen ] ;
        cheb( y, alpha, M ) ;

        fftw_complex z[ aLen ] ;
        fftb( y, z, M ) ;

        z[ 0 ][ 0 ] = z[ 0 ][ 0 ] / 2 ;
        z[ M ][0] = z[ 0 ][0] ;
        for ( int k = 0 ; k < aLen ; k += 1 )
            W[ k ] = z[ k ][0] / z[ M / 2 ][0] ;
    }
}
