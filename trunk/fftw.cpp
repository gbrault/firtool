
#include "fftw3.h"

void fftf( fftw_complex x[], fftw_complex y[], int n ) {
    fftw_plan pPlan = fftw_plan_dft_1d( n, x, y, FFTW_FORWARD, FFTW_ESTIMATE ) ;
    fftw_execute( pPlan ) ;
    fftw_destroy_plan( pPlan ) ;
}

void fftb( fftw_complex x[], fftw_complex y[], int n ) {
    fftw_plan pPlan = fftw_plan_dft_1d( n, x, y, FFTW_BACKWARD, FFTW_ESTIMATE ) ;
    fftw_execute( pPlan ) ;
    fftw_destroy_plan( pPlan ) ;
}

