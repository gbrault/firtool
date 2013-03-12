#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi( this ) ;

    QIcon icon ;
    icon.addFile( ":/files/toolbox.ico" ) ;
    this->setWindowTitle( "FIRTool V0.0 ( Qt " + QString(QT_VERSION_STR) + ") - http://www.mediatronix.com" ) ;
    this->setWindowIcon( icon ) ;
    qApp->setApplicationName("FIRTool V0.0 ( Qt " + QString(QT_VERSION_STR) + ")") ;
    qApp->setWindowIcon( icon ) ;

    // standard
    connect( ui->actionAbout_Qt, SIGNAL( triggered() ), qApp, SLOT( aboutQt() ) ) ;

    customPlotFreq = new QCustomPlot() ;
    ui->horizontalLayout->addWidget( customPlotFreq ) ;


    customPlotFreq->addGraph( ) ;
    customPlotFreq->graph(0)->setPen(QPen(Qt::blue));
    customPlotFreq->addGraph( customPlotFreq->xAxis, customPlotFreq->yAxis2 ) ;
    customPlotFreq->graph(1)->setPen(QPen(Qt::red));
    customPlotFreq->addGraph( customPlotFreq->xAxis, customPlotFreq->yAxis2 ) ;
    customPlotFreq->graph(2)->setPen(QPen(Qt::green));

    // configure right and top axis to show ticks but no labels:
//    customPlotFreq->setupFullAxesBox() ;
//    customPlotFreq->xAxis2->setVisible(true);
//    customPlotFreq->yAxis2->setVisible(true);

    // make left and bottom axes always transfer their ranges to right and top axes:
//    connect(customPlotFreq->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlotFreq->xAxis2, SLOT(setRange(QCPRange)));
//    connect(customPlotFreq->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlotFreq->yAxis2, SLOT(setRange(QCPRange)));

    // make range moveable by mouse interaction (click and drag):
    customPlotFreq->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    customPlotFreq->setRangeZoom(/*Qt::Horizontal |*/ Qt::Vertical);
    customPlotFreq->setInteraction(QCustomPlot::iSelectPlottables); // allow selection of graphs via mouse click

    customPlotFreq->setAntialiasedElements( QCP::aeNone ) ;
    customPlotFreq->setNotAntialiasedElements( QCP::aeAll ) ;

    customPlotTime = new QCustomPlot() ;
    ui->horizontalLayout_4->addWidget( customPlotTime );

    customPlotTime->setNoAntialiasingOnDrag( true ) ;

    customPlotTime->addGraph();
    customPlotTime->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    customPlotTime->addGraph();
    customPlotTime->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph

    customPlotTime->graph(1)->setScatterStyle( QCP::ssCross ) ;
    customPlotTime->graph(1)->setScatterSize( 4 ) ;

    // configure right and top axis to show ticks but no labels:
    customPlotTime->setupFullAxesBox() ;

    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(customPlotTime->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlotTime->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlotTime->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlotTime->yAxis2, SLOT(setRange(QCPRange)));

    // make range moveable by mouse interaction (click and drag):
    customPlotTime->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    customPlotTime->setRangeZoom(Qt::Horizontal | Qt::Vertical);
    customPlotTime->setInteraction(QCustomPlot::iSelectPlottables); // allow selection of graphs via mouse click

    ui->cbFilterType->addItems( QStringList() << "Chebyshev" << "Kaiser" << "harris" );

    ui->twCoefs->setHeaderLabels( QStringList() << "Index" << "Coefs" << "Actual" << "Window" ) ;
    ui->twCoefs->setColumnWidth( 0, 60 ) ;
    ui->twCoefs->setColumnWidth( 1, 100 ) ;

    ui->vSplitter->setStretchFactor( 0, 10 ) ;
    ui->vSplitter->setStretchFactor( 1, 80 ) ;
    ui->vSplitter->setStretchFactor( 2, 10 ) ;

    ui->hSplitterTop->setStretchFactor( 0, 40 ) ;
    ui->hSplitterTop->setStretchFactor( 1, 60 ) ;

    customPlotTime->replot();
    customPlotFreq->replot();

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

    QVector<double> W( nTaps ) ;

    // filter window
    switch ( ui->cbFilterType->currentIndex() ) {
    case 0 :
        chebyshev( W.data(), nTaps, ui->dsbNTaps->value() ) ;
        break ;
    case 1 :
        kaiser( W.data(), nTaps, ui->dsbNTaps->value() ) ;
        break ;
    case 2 :
        harris( W.data(), nTaps, ui->dsbAtten->value() ) ;
        break ;
    }

    // filter type
    QVector<double> T( nTaps ) ;
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

    customPlotTime->graph(0)->setData( x, W ) ;
    customPlotTime->graph(1)->setData( x, T ) ;

    customPlotTime->rescaleAxes();
    customPlotTime->replot();


    int FFTLEN = nTaps < 2048 ? 2048 : nTaps ;

    QVector<double> x2( FFTLEN ) ;
    for ( int i = 0 ; i < FFTLEN / 2 ; i += 1 )
        x2[ i ] = (double)i / FFTLEN ;

    QVector<double> F( 2 * FFTLEN ) ;
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
    customPlotFreq->graph(0)->rescaleValueAxis();
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
        this, tr("Save Xilinx Coefficient File"), ".", tr( "Xilinx coefficient files (*.coe);;All files (*.*)" ) ) ;
    if ( fileName.isEmpty() )
        return ;

    QFile file( fileName ) ;
    if ( ! file.open( QIODevice::WriteOnly | QIODevice::Text ) )
        return ;

    QTextStream stream( &file ) ;
    stream << ";\n; Created by FIRTool at: " << QDateTime::currentDateTime().toString() << "\n" << "; c 2013 www.mediatronix.com\n;\n" ;
    stream << "radix = 10 ;\n" << "coefdata =\n" ;
    double range = pow( 2, ui->dsbNBits->value() ) - 1 ;
    for ( int i = 0 ; i < Coefs.size() - 1 ; i += 1 )
        stream << QString("%1").arg( trunc( Coefs[ i ] * range ), 0, 'g', 9 ) << ",\n" ;
    stream << QString("%1").arg( trunc( Coefs[ Coefs.size() - 1 ] * range ), 0, 'g', 9 ) << ";\n" ;
    file.close() ;
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about( this, "FIRTool", windowTitle() +
        "\n\nThis program comes with ABSOLUTELY NO WARRANTY. " +
        "This is free software, and you are welcome to redistribute it " +
        "under certain conditions. See <http://www.gnu.org/licenses/>"
    ) ;
}

void MainWindow::closeEvent( QCloseEvent *event ) {
//    writeSettings() ;
    event->accept() ;
 }

void MainWindow::on_twType_currentChanged(int index) {
    ui->cbFilterType->setEnabled( index < 4 ) ;
}
