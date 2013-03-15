#ifndef FFTW_H
#define FFTW_H

#include "fftw3.h"

void fftf( fftwl_complex x[], fftwl_complex y[], int n ) ;
void fftb( fftwl_complex x[], fftwl_complex y[], int n ) ;

#endif // FFTW_H
