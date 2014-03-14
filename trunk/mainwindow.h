#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QVector>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

#include "qcustomplot.h"

#include "double.h"
#include "filters.h"
#include "remez.h"
#include "freqchar.h"

#include <windowCheby.h>
#include <windowKaiser.h>
#include <windowHarris.h>
#include <windowRifeVincent.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0) ;
    ~MainWindow() ;
    
    void closeEvent(QCloseEvent *event) ;
    void findRoots(int nTaps) ;

protected:
   void resizeEvent(QResizeEvent *) ;  // virtual

private slots:
    void on_actionDesign_triggered() ;
    void on_pbEstimate_clicked() ;
    void on_actionAbout_triggered() ;

    void on_twType_currentChanged(int index) ;
    void on_cbFilterType_currentIndexChanged(int index) ;
    void on_twMethod_currentChanged(int index) ;
    void on_cbLog_stateChanged(int arg1) ;

    void on_actionLoad_Coefs_triggered() ;
    void on_actionSave_Coefs_triggered() ;

    void on_actionNew_triggered() ;
    void on_actionOpen_triggered() ;
    void on_actionSave_triggered() ;
    void on_actionSave_As_triggered() ;

private:
    void doCheby() ;
    void doKaiser() ;
    void doWindowed() ;
    void doRemez() ;
    void doRRC() ;
    void doGauss() ;

    void doShow() ;
    void doUIenables() ;

    Ui::MainWindow * ui ;
    QCustomPlot * customPlotFreq ;
    QCustomPlot * customPlotTime ;
    QCustomPlot * customPlotZero ;

    QString loadSavePath ;
    QString projectFileName ;

    int nTaps ;
    QVector<ld_t> Coefs ;
    QVector<ld_t> Window ;
    QVector<double> ZeroesReal ;
    QVector<double> ZeroesImag ;

    void readSettings();
    void writeSettings();
} ;

#endif // MAINWINDOW_H
