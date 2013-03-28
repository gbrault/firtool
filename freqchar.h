#ifndef FREQCHAR_H
#define FREQCHAR_H

void freqChar( ld_t * T, ld_t * F, int n, int m ) ;
void freqChar2( ld_t * T, ld_t * F, int n, int m ) ;
void magnitude( ld_t * F, double * M, int n, bool log ) ;
void phase( ld_t * F, double * P, int n ) ;
void group( double * P, double * D, int n ) ;

#endif // FREQCHAR_H
