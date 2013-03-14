
void rifeVincentI3( double * W, int aLen ) {
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] =
            +35.0 / 128 +
            -56.0 / 128 * cos( 2 * M_PI * k / ( aLen - 1 ) ) +
            +28.0 / 128 * cos( 4 * M_PI * k / ( aLen - 1 ) ) +
            - 8.0 / 128 * cos( 6 * M_PI * k / ( aLen - 1 ) ) +
            + 1.0 / 128 * cos( 8 * M_PI * k / ( aLen - 1 ) ) ;
}

void rifeVincentI4( double * W, int aLen ) {
    for ( int k = 0 ; k < aLen ; k += 1 )
        W[ k ] =
            +35.0 / 128 +
            -56.0 / 128 * cos( 2 * M_PI * k / ( aLen - 1 ) ) +
            +28.0 / 128 * cos( 4 * M_PI * k / ( aLen - 1 ) ) +
            - 8.0 / 128 * cos( 6 * M_PI * k / ( aLen - 1 ) ) +
            + 1.0 / 128 * cos( 8 * M_PI * k / ( aLen - 1 ) ) ;
}
