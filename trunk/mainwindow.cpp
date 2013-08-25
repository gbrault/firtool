#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi( this ) ;

    this->setWindowTitle( "FIRTool V0.1 (Qt " + QString(QT_VERSION_STR) + ") - http://www.mediatronix.com" ) ;
    this->setWindowIcon( QIcon( ":/files/toolbox.ico" ) ) ;

    // standard
    connect( ui->actionAbout_Qt, SIGNAL( triggered() ), qApp, SLOT( aboutQt() ) ) ;

    // frequency plot
    customPlotFreq = new QCustomPlot() ;
    ui->loMagnitude->addWidget( customPlotFreq ) ;

    customPlotFreq->addGraph( ) ;
    customPlotFreq->graph( 0 )->setPen( QPen( Qt::blue ) ) ;
    customPlotFreq->addGraph( customPlotFreq->xAxis, customPlotFreq->yAxis2 ) ;
    customPlotFreq->graph( 1 )->setPen( QPen( Qt::red ) ) ;
    customPlotFreq->addGraph( customPlotFreq->xAxis, customPlotFreq->yAxis2 ) ;
    customPlotFreq->graph( 2 )->setPen( QPen( Qt::green ) ) ;

    customPlotFreq->xAxis->setRange( QCPRange( 0.0, 0.4999 ) ) ;
    customPlotFreq->yAxis->setRange( QCPRange( -200, 10 ) ) ;
    customPlotFreq->xAxis->setAutoTickStep( false ) ;
    customPlotFreq->xAxis->setAutoTickCount( 10 ) ;
        customPlotFreq->xAxis->setTickStep( 0.1 ) ;

    // make range moveable by mouse interaction (click and drag):
    customPlotFreq->setRangeDrag( Qt::Horizontal | Qt::Vertical ) ;
    customPlotFreq->setRangeZoom( Qt::Horizontal | Qt::Vertical ) ;
//    customPlotFreq->setInteraction( QCustomPlot::iSelectPlottables ) ; // allow selection of graphs via mouse click

    customPlotFreq->setAntialiasedElements( QCP::aeNone ) ;
    customPlotFreq->setNotAntialiasedElements( QCP::aeAll ) ;
    customPlotFreq->xAxis->setSubGrid( true ) ;
    customPlotFreq->yAxis->setSubGrid( true ) ;

    customPlotTime = new QCustomPlot() ;
    ui->loTime->addWidget( customPlotTime ) ;

    customPlotTime->setNoAntialiasingOnDrag( true ) ;

    customPlotTime->addGraph() ;
    customPlotTime->graph(0)->setPen( QPen( Qt::lightGray ) ) ;
    customPlotTime->addGraph() ;
    customPlotTime->graph(1)->setPen( QPen( Qt::blue ) ) ;

    customPlotTime->graph(1)->setScatterStyle( QCP::ssCircle ) ;
    customPlotTime->graph(1)->setScatterSize( 4 ) ;

    customPlotTime->graph(1)->setLineStyle( QCPGraph::lsImpulse );

    // configure right and top axis to show ticks but no labels:
    customPlotTime->setupFullAxesBox() ;

    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(customPlotTime->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlotTime->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlotTime->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlotTime->yAxis2, SLOT(setRange(QCPRange)));

    // make range moveable by mouse interaction (click and drag):
    customPlotTime->setRangeDrag( Qt::Horizontal | Qt::Vertical ) ;
    customPlotTime->setRangeZoom( Qt::Horizontal | Qt::Vertical ) ;
    customPlotTime->setInteraction(QCustomPlot::iSelectPlottables); // allow selection of graphs via mouse click
    customPlotTime->xAxis->setSubGrid( true ) ;
    customPlotTime->yAxis->setSubGrid( true ) ;

    customPlotZero = new QCustomPlot() ;
    ui->loZero->insertWidget( 0, customPlotZero ) ;
    customPlotZero->setMinimumWidth( customPlotZero->size().width() ) ;
    customPlotZero->setupFullAxesBox() ;
    customPlotZero->xAxis->setRange( QCPRange( -1.3, 1.3 ) ) ;
    customPlotZero->yAxis->setRange( QCPRange( -1.3, 1.3 ) ) ;
    customPlotZero->xAxis->setSubGrid( true ) ;
    customPlotZero->yAxis->setSubGrid( true ) ;
    customPlotZero->xAxis->setAutoTickStep( false ) ;
    customPlotZero->yAxis->setAutoTickStep( false ) ;
    customPlotZero->xAxis->setTickStep( 0.2 ) ;
    customPlotZero->yAxis->setTickStep( 0.2 ) ;
    customPlotZero->addGraph( ) ;
    customPlotZero->graph( 0 )->setScatterStyle( QCP::ssCircle ) ;
    customPlotZero->graph( 0 )->setScatterSize( 6 ) ;
    customPlotZero->graph( 0 )->setLineStyle( QCPGraph::lsNone ) ;
    customPlotZero->setRangeDrag( Qt::Horizontal | Qt::Vertical ) ;
    customPlotZero->setRangeZoom( Qt::Horizontal | Qt::Vertical ) ;

    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(customPlotZero->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlotZero->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlotZero->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlotZero->yAxis2, SLOT(setRange(QCPRange)));

    QCPItemEllipse * unitcircle = new QCPItemEllipse( customPlotZero ) ;
    customPlotZero->addItem( unitcircle ) ;
    unitcircle->setPen( QPen( Qt::gray ) ) ;
    unitcircle->topLeft->setCoords( 1, -1 ) ;
    unitcircle->bottomRight->setCoords( -1, 1 ) ;


    ui->cbFilterType->addItems(
        QStringList()
            << " Taylor" << " Rife-Vincent"
            << " harris" << " Nuttall" << " Flat top" << "Connes"
    ) ;

    ui->twCoefs->setHeaderLabels( QStringList() << "Index" << "Coefs" << "Actual" << "Window" ) ;
    ui->twCoefs->setColumnWidth( 0, 60 ) ;
    ui->twCoefs->setColumnWidth( 1, 100 ) ;

    ui->vSplitter->setStretchFactor( 0, 10 ) ;
    ui->vSplitter->setStretchFactor( 1, 80 ) ;
    ui->vSplitter->setStretchFactor( 2, 10 ) ;

    ui->hSplitterTop->setStretchFactor( 0, 40 ) ;
    ui->hSplitterTop->setStretchFactor( 1, 60 ) ;

    customPlotFreq->replot() ;
    customPlotTime->replot() ;
    customPlotZero->replot() ;

    // exit
    connect( ui->actionExit, SIGNAL( triggered() ), this, SLOT( close() ) ) ;

    ui->cbFilterType->setCurrentIndex( 0 ) ;
    ui->dsbSubtype->setValue( 0 ) ;

    // settings
//    readSettings() ;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about( this, "FIRTool", windowTitle() +
        "\n\nThis program comes with ABSOLUTELY NO WARRANTY.\n" +
        "This is free software, and you are welcome to redistribute it " +
        "under certain conditions. See <http://www.gnu.org/licenses/>"
    ) ;
}

void MainWindow::on_actionDesign_triggered() {
    Window.clear() ;
    Coefs.clear() ;

//    if ( ui->twType->currentIndex() < 4 ) {
        nTaps = (int)ui->dsbNTaps->value() | 1 ;
        ui->dsbNTaps->setValue( nTaps ) ;
//    }

    switch ( ui->twMethod->currentIndex() ) {
    case 0 : doCheby() ; break ;
    case 1 : doKaiser() ; break ;
    case 2 : doRemez() ; break ;
    case 3 : doWindowed() ; break ;
    case 4 : doRRC() ; break ;
    case 5 : doGauss() ; break ;
    }
    doShow() ;
}

void MainWindow::doCheby( void ) {
    Window.resize( nTaps ) ;
    for ( int n = 0 ; n < nTaps ; n += 1 )
        Window[ n ] = 0.0L ;

    double beta = ui->dsbChebyBeta->value() ;
    chebyshev( Window.data(), nTaps, beta ) ;

    // filter type
    QVector<ld_t> T( nTaps ) ;
    switch ( ui->twType->currentIndex() ) {
    case 0 :
        lowPass( T.data(), ui->dsbLPStop->value(), Window.data(), nTaps ) ;
        break ;
    case 1 :
        highPass( T.data(), ui->dsbHPStart->value(), Window.data(), nTaps ) ;
        break ;
    case 2 :
        bandPass( T.data(), ui->dsbBPStart->value(), ui->dsbBPStop->value(), Window.data(), nTaps ) ;
        break ;
    case 3 :
        bandStop( T.data(), ui->dsbBSStop->value(), ui->dsbBSStart->value(), Window.data(), nTaps ) ;
        break ;
    default :
        statusBar()->showMessage( "Chebyshev: <not implemented yet>", 2000 ) ;
    }
    Coefs = T ;
}

void MainWindow::doKaiser( void ) {
    Window.resize( nTaps ) ;
    for ( int n = 0 ; n < nTaps ; n += 1 )
        Window[ n ] = 0.0L ;

    double beta = ui->dsbKaiserBeta->value() ;
    kaiser( Window.data(), nTaps, beta ) ;

    // filter type
    Coefs.resize( nTaps ) ;
    switch ( ui->twType->currentIndex() ) {
    case 0 :
        lowPass( Coefs.data(), ui->dsbLPStop->value(), Window.data(), nTaps ) ;
        break ;
    case 1 :
        highPass( Coefs.data(), ui->dsbHPStart->value(), Window.data(), nTaps ) ;
        break ;
    case 2 :
        bandPass( Coefs.data(), ui->dsbBPStart->value(), ui->dsbBPStop->value(), Window.data(), nTaps ) ;
        break ;
    case 3 :
        bandStop( Coefs.data(), ui->dsbBSStop->value(), ui->dsbBSStart->value(), Window.data(), nTaps ) ;
        break ;
    default :
        statusBar()->showMessage( "Kaiser: <not implemented yet>", 2000 ) ;
    }
}

void MainWindow::doWindowed( void ) {
    Window.resize( nTaps ) ;
    for ( int n = 0 ; n < nTaps ; n += 1 )
        Window[ n ] = 0.0L ;

    double atten = ui->dsbAtten->value() ;

    // filter window
    switch ( ui->cbFilterType->currentIndex() ) {
    case 0 :
        rifeVincentII( Window.data(), nTaps, atten, (int)ui->dsbSubtype->value() ) ;
        break ;
    case 1 :
        rifeVincent( (RV_t)ui->dsbSubtype->value(), Window.data(), nTaps ) ;
        break ;
    case 2 :
        harris( Window.data(), nTaps ) ;
        break ;
    case 3 :
        nuttall( Window.data(), nTaps ) ;
        break ;
    case 4 :
        flattop( Window.data(), nTaps ) ;
        break ;
    case 5 :
        connes( Window.data(), nTaps ) ;
        break ;
    }

    // filter type
    Coefs.resize( nTaps ) ;
    switch ( ui->twType->currentIndex() ) {
    case 0 :
        lowPass( Coefs.data(), ui->dsbLPStop->value(), Window.data(), nTaps ) ;
        break ;
    case 1 :
        highPass( Coefs.data(), ui->dsbHPStart->value(), Window.data(), nTaps ) ;
        break ;
    case 2 :
        bandPass( Coefs.data(), ui->dsbBPStart->value(), ui->dsbBPStop->value(), Window.data(), nTaps ) ;
        break ;
    case 3 :
        bandStop( Coefs.data(), ui->dsbBSStop->value(), ui->dsbBSStart->value(), Window.data(), nTaps ) ;
        break ;
    default :
        statusBar()->showMessage( "Windowed: <not implemented yet>", 2000 ) ;
    }
}

void MainWindow::doRemez( void ) {
    QVector<ld_t> bands ;
    QVector<ld_t> response ;
    QVector<ld_t> weight ;
    int nbands = 0 ;

    double tw = ui->dsbTW->value() / 2.0 ;
    double tf, tfl, tfr ;
    REMEZ_t type = BANDPASS ;

    switch ( ui->twType->currentIndex() ) {
    case 0 :
        nbands = 2 ;
        tf = ui->dsbLPStop->value() ;
        bands << 0.0 << tf-tw << tf+tw << 0.5 ;
        response << 1 << 1 << 0 << 0 ;
        weight << 1 << 1 ;
        type = BANDPASS ;
        break ;
    case 1 :
        nbands = 2 ;
        tf = ui->dsbHPStart->value() ;
        bands << 0.0 << tf-tw << tf+tw << 0.5 ;
        response << 0 << 0 << 1 << 1 ;
        weight << 1 << 1 ;
        type = BANDPASS ;
        break ;
    case 2 :
        nbands = 3 ;
        tfl = ui->dsbBPStart->value() ;
        tfr = ui->dsbBPStop->value() ;
        bands << 0.0 << tfl-tw << tfl+tw << tfr-tw << tfr+tw << 0.5 ;
        response << 0 << 0 << 1 << 1 << 0 << 0 ;
        weight << 1 << 1 << 1 ;
        type = BANDPASS ;
        break ;
    case 3 :
        nbands = 3 ;
        tfl = ui->dsbBSStop->value() ;
        tfr = ui->dsbBSStart->value() ;
        bands << 0.0 << tfl-tw << tfl+tw << tfr-tw << tfr+tw << 0.5 ;
        response << 1 << 1 << 0 << 0 << 1 << 1 ;
        weight << 1 << 1 << 1 ;
        type = BANDPASS ;
        break ;
    case 4 :
        nbands = 1 ;
        tfl = ui->dsbDiffLowerBandEdge->value() ;
        tfr = ui->dsbDiffUpperBandEdge->value() ;
//        slope = ui->dsbDiffDesiredSlope->value() ;
        bands << tfl << tfr ;
        response << 0 << 1 << 0 ;
        weight << 1 << 1 ;
        type = DIFFERENTIATOR ;
        break ;
    case 5 :
        nbands = 1 ;
        tfl = ui->dsbHilbertStart->value() ;
        tfr = ui->dsbHilbertStop->value() ;
        bands << tfl << tfr ;
        response << 1 ;
        weight << 1 ;
        type = HILBERT ;
        break ;
    default :
        statusBar()->showMessage( "Remez: <not implemented yet>", 2000 ) ;
        return ;
    }

    Coefs.resize( nTaps ) ;
    int err = remez( Coefs.data(), nTaps, nbands, bands.data(), response.data(), weight.data(), type, 64 ) ;

    switch ( err ) {
    case -1 :
        statusBar()->showMessage( "Remez: failed to converge", 2000 ) ;
        break ;
    case -2 :
        statusBar()->showMessage( "Remez: insufficient extremals -- cannot continue", 2000 ) ;
        break ;
    case -3 :
        statusBar()->showMessage( "Remez: too many extremals -- cannot continue", 2000 ) ;
        break ;
    }
}

void MainWindow::doRRC( void ) {
    Coefs.resize( nTaps ) ;
    rootRaisedCosine( Coefs.data(), ui->dsbRRCSPS->value(), ui->dsbRRCBeta->value(), nTaps ) ;
}

void MainWindow::doGauss( void ) {
    Coefs.resize( nTaps ) ;
    gaussian( Coefs.data(), ui->dsbGSPS->value(), ui->dsbGBT->value(), nTaps ) ;
}

#include <complex>
int newton_real( register int n, const double coeff[], std::complex<double> res[] ) ;
void MainWindow::findRoots( int nTaps ) {
    double t[ nTaps ] ;
    for ( int i = 0 ; i < nTaps ; i += 1 )
        t[ i ] = Coefs[ i ] ;

    std::complex<double> zeroes[ nTaps ] ;
    newton_real( nTaps, t, zeroes ) ;

    ZeroesReal.resize( nTaps ) ;
    ZeroesImag.resize( nTaps ) ;
    for ( int i = 0 ; i < nTaps ; i += 1 ) {
        ZeroesReal[ i ] = zeroes[ i ].real() ;
        ZeroesImag[ i ] = zeroes[ i ].imag() ;
    }
}

void MainWindow::resizeEvent(QResizeEvent *) {
    customPlotZero->setFixedWidth( customPlotZero->size().height() ) ;
}

void MainWindow::doShow( void ) {
    customPlotTime->graph(0)->clearData() ;
    customPlotTime->graph(1)->clearData() ;
    customPlotFreq->graph(0)->clearData() ;
    customPlotZero->graph(0)->clearData() ;

    QVector<double> x( nTaps ) ;
    for ( int i = 0 ; i < nTaps ; i += 1 )
        x[ i ] = (double)i ;

    // do time plots
    if ( ! Window.isEmpty() ) {
        QVector<double> w( nTaps ) ;
        for ( int i = 0 ; i < nTaps ; i += 1 )
            w[ i ] = Window[ i ] ;
        customPlotTime->graph(0)->setData( x, w ) ;
    }
    if ( ! Coefs.isEmpty() ) {
        QVector<double> t( nTaps ) ;
        for ( int i = 0 ; i < nTaps ; i += 1 )
            t[ i ] = Coefs[ i ] ;
        customPlotTime->graph(1)->setData( x, t ) ;
    }
    customPlotTime->rescaleAxes();
    customPlotTime->replot();

    if ( Coefs.isEmpty() )
        return ;

    // do freq char plot
    int FFTLEN = nTaps < 4096 ? 4096 : nTaps ;

    QVector<double> x2( FFTLEN ) ;
    for ( int i = 0 ; i < FFTLEN / 2 ; i += 1 )
        x2[ i ] = (double)i / FFTLEN ;

    QVector<ld_t> F( 2 * FFTLEN ) ;
    freqChar( Coefs.data(), F.data(), nTaps, FFTLEN ) ;

    QVector<double> M( FFTLEN ) ;
    magnitude( F.data(), M.data(), FFTLEN, ui->cbLog->isChecked() ) ;
//    QVector<double> P( FFTLEN ) ;
//    phase( F.data(), P.data(), FFTLEN ) ;
//    QVector<double> D( FFTLEN ) ;
//    group( P.data(), D.data(), FFTLEN ) ;

    customPlotFreq->graph(0)->setData( x2, M ) ;

    customPlotFreq->graph(0)->rescaleKeyAxis();

    if ( ui->cbLog->isChecked() )
        customPlotFreq->yAxis->setRange( QCPRange( -200, 10 ) ) ;
    else
        customPlotFreq->yAxis->setRange( QCPRange( -0.2, 1.2 ) ) ;

    customPlotFreq->replot() ;

    // do zeroes plot
    findRoots( nTaps ) ;
    customPlotZero->graph(0)->setData( ZeroesReal, ZeroesImag ) ;
    customPlotZero->replot() ;

    // fill list view of coefficients, window
    double range = pow( 2, ui->dsbNBits->value() ) - 1 ;
    ui->twCoefs->clear();
    for ( int i = 0 ; i < nTaps ; i += 1 ) {
        QStringList columns ;
        columns << QString( "%1" ).arg( i ) ;
        columns << QString( "%1" ).arg( trunc( Coefs[ i ] * 1E9 ) / 1E9, 0, 'g', 9 ) ;
        columns << QString( "%1" ).arg( trunc( Coefs[ i ] * range ), 0, 'g', 9 ) ;
        if ( ! Window.isEmpty() )
            columns << QString( "%1" ).arg( trunc( Window[ i ] * 1E9 ) / 1E9, 0, 'g', 9 ) ;
        else
            columns << "" ;
        ui->twCoefs->addTopLevelItem( new QTreeWidgetItem( columns ) ) ;
    }
}

void MainWindow::on_actionSave_Coefs_triggered() {
    if ( Coefs.isEmpty() )
        return ;

    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save Coefficient File"), ".", tr(
            "Xilinx coefficient files (*.coe);;C/C++ include files (*.h);;VHDL files (*.vhd);;All files (*.*)" ) ) ;
    if ( fileName.isEmpty() )
        return ;

    QFile file( fileName ) ;
    if ( ! file.open( QIODevice::WriteOnly | QIODevice::Text ) )
        return ;

    QDateTime date( QDateTime::currentDateTime() ) ;
    QTextStream stream( &file ) ;
    if ( fileName.endsWith( ".coe", Qt::CaseInsensitive ) ) {
        stream << ";\n; Created by FIRTool at: " << date.toString("MMMM d yyyy") << "\n; c 2013 www.mediatronix.com\n;\n" ;
        stream << "radix = 10 ;\n" << "coefdata =\n" ;
        if ( ui->dsbNBits->value() > 0.5 ) {
            double range = pow( 2, ui->dsbNBits->value() ) - 1 ;
            for ( int i = 0 ; i < Coefs.size() - 1 ; i += 1 )
                stream << QString("%1").arg( trunc( Coefs[ i ] * range ), 0, 'g', 9 ) << ",\n" ;
            stream << QString("%1").arg( trunc( Coefs[ Coefs.size() - 1 ] * range ), 0, 'g', 9 ) << ";\n" ;
        } else {
            for ( int i = 0 ; i < Coefs.size() - 1 ; i += 1 )
                stream << QString("%1").arg( Coefs[ i ], 0, 'g', 9 ) << ",\n" ;
            stream << QString("%1").arg( Coefs[ Coefs.size() - 1 ], 0, 'g', 9 ) << " ;\n" ;
        }
    } else
    if ( fileName.endsWith( ".h", Qt::CaseInsensitive ) ) {
        stream << "//\n// Created by FIRTool at: " << date.toString("MMMM d yyyy") << "\n// c 2013 www.mediatronix.com\n//\n" ;
        stream << "double coefdata[] = {\n" ;
        for ( int i = 0 ; i < Coefs.size() - 1 ; i += 1 )
            stream << QString("    %1").arg( Coefs[ i ], 0, 'g', 9 ) << ",\n" ;
        stream << QString("    %1").arg( Coefs[ Coefs.size() - 1 ], 0, 'g', 9 ) << "\n} ;\n" ;
    } else
    if ( fileName.endsWith( ".vhd", Qt::CaseInsensitive ) ) {
        double range = pow( 2, ui->dsbNBits->value() ) - 1 ;
        stream << "--\n-- Created by FIRTool at: " << date.toString("MMMM d yyyy") << "\n-- c 2013 www.mediatronix.com\n--\n" ;
        stream << QString( "    signal coefdata : array( 0 to %1 ) of integer range %2 to %3 := (\n" )
                      .arg( trunc( Coefs.size() - 1 ) )
                      .arg( -(int)(range / 2) )
                      .arg( (int)(range / 2) ) ;
        for ( int i = 0 ; i < Coefs.size() - 1 ; i += 1 )
          stream << QString("        %1").arg( trunc( Coefs[ i ] * range ), 0, 'g', 9 ) << ",\n" ;
        stream << QString("        %1").arg( trunc( Coefs[ Coefs.size() - 1 ] * range ), 0, 'g', 9 ) << "\n    ) ;" ;
    }
    file.close() ;
}

void MainWindow::closeEvent( QCloseEvent *event ) {
//    writeSettings() ;
    event->accept() ;
}

void MainWindow::doUIenables( void ) {
    ui->actionDesign->setEnabled( ui->twType->currentIndex() < 4 || ui->twMethod->currentIndex() == 2 ) ;
}

void MainWindow::on_twType_currentChanged( int index ) {
    (void)index;
    doUIenables();
}

void MainWindow::on_twMethod_currentChanged( int index ) {
    (void)index;
    doUIenables();
}

void MainWindow::on_cbFilterType_currentIndexChanged( int index ) {
    (void)index;
//    ui->dsbSubtype->setEnabled( index == 0 || index == 1 ) ;
//    switch ( index ) {
//    case 0: ui->dsbSubtype->setPrefix( "M: " ) ; break ;
//    case 1: ui->dsbSubtype->setPrefix( "Type: " ) ; break ;
//    default: ui->dsbSubtype->setPrefix( "<not used> " ) ; break ;
//    }
}

void MainWindow::on_pbEstimate_clicked() {
    double tw = ui->dsbTW->value() ;
    double attn = ui->dsbAtten->value() ;
    double dp = - attn / 20.0 ;
    double ds = - attn / 20.0 ;
    int nTaps = 3 ;

    // various estimators
    switch ( ui->twMethod->currentIndex() ) {
    case 0 : {
            nTaps = ceil( 1 + acosh( 1 / pow( 10.0, dp ) ) / tw / 2 ) ;
            double beta = cosh( acosh( pow( 10.0, attn / 20.0 ) ) / (nTaps - 1) ) ;
            ui->dsbChebyBeta->setValue( beta ) ;
        }
        break ;
    case 1 : {
            double beta = 0.0 ;
            if ( attn > 50.0 )
                beta = 0.1102 *( attn - 8.7 ) ;
            else if ( attn >= 21.0 )
                beta = 0.5842 * pow( ( attn - 21.0 ), 0.4 ) + 0.07886 * ( attn - 21.0 ) ;
            ui->dsbKaiserBeta->setValue( beta ) ;
            nTaps = ceil( ( attn - 8.0 ) / ( 2.285 * tw ) ) ;
        }
        break ;
    default :
    case 2 : {
            double Dinf = ds * ( 5.309e-3 * dp * dp + 7.114e-2 * dp + -4.761e-1 ) +
                -2.66e-3 * dp * dp + -5.941e-1 * dp + -4.278e-1 ;
            double f = 11.01217 + 0.51244 * ( dp - ds ) ;
            nTaps = ceil( Dinf / tw - f * tw + 1 ) ;
        }
        break ;
//    default :
//        return ;
    }
    ui->dsbNTaps->setValue( nTaps | 1 ) ;
}


void MainWindow::on_cbLog_stateChanged(int arg1) {
    (void)arg1 ;
    doShow() ;
}
