#ifndef REMEZ_H
#define REMEZ_H

typedef enum _RemezType {
    BANDPASS = 1,
    DIFFERENTIATOR = 2,
    HILBERT = 3
} REMEZ_t ;

int remez( long double h[], int numtaps, int numband, const double bands[],
      const double des[], const double weight[], REMEZ_t type, int griddensity ) ;

#endif // REMEZ_H
