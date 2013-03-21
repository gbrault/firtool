#ifndef REMEZ_H
#define REMEZ_H

int remez(double h[], int numtaps,
      int numband, const double bands[],
      const double des[], const double weight[],
      int type, int griddensity) ;

#endif // REMEZ_H
