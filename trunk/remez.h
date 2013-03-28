#ifndef REMEZ_H
#define REMEZ_H

typedef enum _RemezType {
    BANDPASS = 1,
    DIFFERENTIATOR = 2,
    HILBERT = 3
} REMEZ_t ;

int remez( ld_t h[], int numtaps, int numband, const ld_t bands[],
      const ld_t des[], const ld_t weight[], REMEZ_t type, int griddensity ) ;

#endif // REMEZ_H
