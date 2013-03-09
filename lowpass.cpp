
#include "math.h"
#include "filters.h"

void lowPass( double * T, double cutoff_freq, double sampling_freq, double * W, int aLen ) {
    int M = ( aLen - 1 ) / 2 ;

    double fwT0 = 2 * M_PI * cutoff_freq / sampling_freq ;
    for ( int n = -M ; n <= M ; n++ ) {
        if ( n == 0 )
            T[ n + M ] = fwT0 / M_PI * W[ n + M ] ;
        else {
            T[ n + M ] =  sin( n * fwT0 ) / ( n * M_PI ) * W[ n + M ] ;
        }
    }

    double fmax = T[ 0 + M ] ;
    for( int n = 1 ; n <= M ; n++ )
        fmax += 2 * T[ n + M ] ;

    double gain = 1.0 ;
    gain /= fmax ;

    for( int i = 0; i < aLen ; i++ )
        T[ i ] *= gain ;
}

