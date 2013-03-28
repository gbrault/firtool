
#include "fftw.h"

void fftf( fftwl_complex x[], fftwl_complex y[], int n ) {
    fftwl_plan pPlan = fftwl_plan_dft_1d( n, x, y, FFTW_FORWARD, FFTW_ESTIMATE ) ;
    fftwl_execute( pPlan ) ;
    fftwl_destroy_plan( pPlan ) ;
}

void fftb( fftwl_complex x[], fftwl_complex y[], int n ) {
    fftwl_plan pPlan = fftwl_plan_dft_1d( n, x, y, FFTW_BACKWARD, FFTW_ESTIMATE ) ;
    fftwl_execute( pPlan ) ;
    fftwl_destroy_plan( pPlan ) ;
}

