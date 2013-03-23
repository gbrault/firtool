

long double zoltarevCoef[ 41 ] = {
    -0.643099,
    -0.226762,
    -0.035981,
    0.223379,
    0.387465,

    0.325961,
    0.039811,
    -0.317256,
    -0.520533,
    -0.416778,

    -0.036271,
    0.406232,
    0.634285,
    0.485255,
    0.025390,

    -0.476835,
    -0.710942,
    -0.520577,
    -0.009122,
    0.517382,

    0.737995,

    0.517382,
    -0.009122,
    -0.520577,
    -0.710942,
    -0.476835,

    0.025390,
    0.485255,
    0.634285,
    0.406232,
    -0.036271,

    -0.416778,
    -0.520533,
    -0.317256,
    0.039811,
    0.325961,

    0.387465,
    0.223379,
    -0.035981,
    -0.226762,
    -0.643099
    } ;

void zolotarevFIR( long double * T, double spb, double alpha, int nLen ) {
    for ( int n = 0 ; n < nLen ; n += 1 )
        T[ n ] = zoltarevCoef[ n ] ;
}
