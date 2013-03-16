#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi( this ) ;

    this->setWindowTitle( "FIRTool V0.1 ( Qt " + QString(QT_VERSION_STR) + ") - http://www.mediatronix.com" ) ;
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

    // make range moveable by mouse interaction (click and drag):
    customPlotFreq->setRangeDrag( Qt::Horizontal | Qt::Vertical ) ;
    customPlotFreq->setRangeZoom( Qt::Horizontal | Qt::Vertical ) ;
//    customPlotFreq->setInteraction( QCustomPlot::iSelectPlottables ) ; // allow selection of graphs via mouse click

    customPlotFreq->setAntialiasedElements( QCP::aeNone ) ;
    customPlotFreq->setNotAntialiasedElements( QCP::aeAll ) ;

    customPlotTime = new QCustomPlot() ;
    ui->loTime->addWidget( customPlotTime ) ;

    customPlotTime->setNoAntialiasingOnDrag( true ) ;

    customPlotTime->addGraph();
    customPlotTime->graph(0)->setPen( QPen( Qt::lightGray ) ) ;
    customPlotTime->addGraph();
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

    ui->cbFilterType->addItems(
        QStringList() << "Chebyshev" << "Kaiser" << "Taylor"
            << "Rife-Vincent" << "harris" << "Nuttall" << "Flat top" );

    ui->twCoefs->setHeaderLabels( QStringList() << "Index" << "Coefs" << "Actual" << "Window" ) ;
    ui->twCoefs->setColumnWidth( 0, 60 ) ;
    ui->twCoefs->setColumnWidth( 1, 100 ) ;

    ui->vSplitter->setStretchFactor( 0, 10 ) ;
    ui->vSplitter->setStretchFactor( 1, 80 ) ;
    ui->vSplitter->setStretchFactor( 2, 10 ) ;

    ui->hSplitterTop->setStretchFactor( 0, 40 ) ;
    ui->hSplitterTop->setStretchFactor( 1, 60 ) ;

    customPlotTime->replot() ;
    customPlotFreq->replot() ;

    // exit
    connect( ui->actionExit, SIGNAL( triggered() ), this, SLOT( close() ) ) ;

    ui->cbFilterType->setCurrentIndex( 0 ) ;

    // settings
//    readSettings() ;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionDesign_triggered() {
    int nTaps = (int)ui->dsbNTaps->value() | 1 ;
    ui->dsbNTaps->setValue( nTaps ) ;

    QVector<double> x( nTaps ) ;
    for ( int i = 0 ; i < nTaps ; i += 1 )
        x[ i ] = (double)i ;

    QVector<long double> W( nTaps ) ;

    // filter window
    switch ( ui->cbFilterType->currentIndex() ) {
    case 0 :
        chebyshev( W.data(), nTaps, ui->dsbAtten->value() ) ;
        break ;
    case 1 :
        kaiser( W.data(), nTaps, ui->dsbAtten->value() ) ;
        break ;
    case 2 :
        taylor( W.data(), nTaps, ui->dsbAtten->value() ) ;
        break ;
    case 3 :
        rifeVincent( RV_III4, W.data(), nTaps ) ;
        break ;
    case 4 :
        harris( W.data(), nTaps ) ;
        break ;
    case 5 :
        nuttall( W.data(), nTaps ) ;
        break ;
    case 6 :
        flattop( W.data(), nTaps ) ;
        break ;
    }

    // filter type
    QVector<long double> T( nTaps ) ;
    switch ( ui->twType->currentIndex() ) {
    case 0 :
        lowPass( T.data(), ui->dsbLPStop->value(), W.data(), nTaps ) ;
        break ;
    case 1 :
        highPass( T.data(), ui->dsbHPStart->value(), W.data(), nTaps ) ;
        break ;
    case 2 :
        bandPass( T.data(), ui->dsbBPStart->value(), ui->dsbBPStop->value(), W.data(), nTaps ) ;
        break ;
    case 3 :
        bandStop( T.data(), ui->dsbBSStop->value(), ui->dsbBSStart->value(), W.data(), nTaps ) ;
        break ;
    case 4 :
        gaussian( T.data(), ui->dsbGSPS->value(), ui->dsbGBT->value(), nTaps ) ;
        break ;
    case 5 :
        rootRaisedCosine( T.data(), ui->dsbRRCSPS->value(), ui->dsbRRCBeta->value(), nTaps ) ;
        break ;
    }


    QVector<double> w( nTaps ) ;
    for ( int i = 0 ; i < nTaps ; i += 1 )
        w[ i ] = W[ i ] ;
    customPlotTime->graph(0)->setData( x, w ) ;
    QVector<double> t( nTaps ) ;
    for ( int i = 0 ; i < nTaps ; i += 1 )
        t[ i ] = T[ i ] ;
    customPlotTime->graph(1)->setData( x, t ) ;

    customPlotTime->rescaleAxes();
    customPlotTime->replot();


    int FFTLEN = nTaps < 2048 ? 2048 : nTaps ;

    QVector<double> x2( FFTLEN ) ;
    for ( int i = 0 ; i < FFTLEN / 2 ; i += 1 )
        x2[ i ] = (double)i / FFTLEN ;

    QVector<long double> F( 2 * FFTLEN ) ;
    freqChar( T.data(), F.data(), nTaps, FFTLEN ) ;

    QVector<double> M( FFTLEN ) ;
    magnitude( F.data(), M.data(), FFTLEN ) ;
    QVector<double> P( FFTLEN ) ;
    phase( F.data(), P.data(), FFTLEN ) ;
    QVector<double> D( FFTLEN ) ;
    group( P.data(), D.data(), FFTLEN ) ;

    customPlotFreq->graph(0)->setData( x2, M ) ;
//    customPlotFreq->graph(1)->setData( x2, P ) ;
//    customPlotFreq->graph(2)->setData( x2, D ) ;

    customPlotFreq->graph(0)->rescaleKeyAxis();

    QCPRange newRange( -200, 0 ) ;
    customPlotFreq->yAxis->setRange( newRange ) ;

//    customPlotFreq->graph(0)->rescaleValueAxis();
//    customPlotFreq->graph(1)->rescaleValueAxis();
    customPlotFreq->replot();

    double range = pow( 2, ui->dsbNBits->value() ) - 1 ;
    ui->twCoefs->clear();
    for ( int i = 0 ; i < nTaps ; i += 1 ) {
        QStringList columns ;
        columns << QString("%1").arg( i ) ;
        columns << QString("%1").arg( trunc( T[ i ] * 1E9 ) / 1E9, 0, 'g', 9 ) ;
        columns << QString("%1").arg( trunc( T[ i ] * range ), 0, 'g', 9 ) ;
        columns << QString("%1").arg( trunc( W[ i ] * 1E9 ) / 1E9, 0, 'g', 9 ) ;
        ui->twCoefs->addTopLevelItem( new QTreeWidgetItem( columns ) ) ;
    }

    Coefs = T ;
}

void MainWindow::on_actionSave_Coefs_triggered() {
    if ( Coefs.isEmpty() )
        return ;

    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save Coefficient File"), ".", tr( "Xilinx coefficient files (*.coe);;C/C++ include files (*.h);;All files (*.*)" ) ) ;
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
        stream << "double coefdata[] = (\n" ;
        for ( int i = 0 ; i < Coefs.size() - 1 ; i += 1 )
            stream << QString("    %1").arg( Coefs[ i ], 0, 'g', 9 ) << ",\n" ;
        stream << QString("    %1").arg( Coefs[ Coefs.size() - 1 ], 0, 'g', 9 ) << "\n) ;\n" ;
    }
    file.close() ;
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about( this, "FIRTool", windowTitle() +
        "\n\nThis program comes with ABSOLUTELY NO WARRANTY.\n" +
        "This is free software, and you are welcome to redistribute it " +
        "under certain conditions. See <http://www.gnu.org/licenses/>"
    ) ;
}

void MainWindow::closeEvent( QCloseEvent *event ) {
//    writeSettings() ;
    event->accept() ;
 }

void MainWindow::on_twType_currentChanged( int index ) {
    ui->cbFilterType->setEnabled( index < 4 ) ;
}

void MainWindow::on_cbFilterType_currentIndexChanged( int index ) {
    ui->dsbAtten->setEnabled( index < 3 ) ;
}
