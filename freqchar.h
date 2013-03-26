#ifndef FREQCHAR_H
#define FREQCHAR_H

void freqChar( long double * T, long double * F, int n, int m ) ;
void freqChar2( long double * T, long double * F, int n, int m ) ;
void magnitude( long double * F, double * M, int n, bool log ) ;
void phase( long double * F, double * P, int n ) ;
void group( double * P, double * D, int n ) ;

#endif // FREQCHAR_H
