#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "QVector"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"

#include "qcustomplot.h"

#include "filters.h"
#include "remez.h"
//#include "zolotarev.hpp"
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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void closeEvent(QCloseEvent *event);
private slots:
    void on_actionDesign_triggered();
    void on_actionSave_Coefs_triggered();
    void on_actionAbout_triggered();

    void on_twType_currentChanged(int index);
    void on_cbFilterType_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QCustomPlot * customPlotFreq ;
    QCustomPlot * customPlotTime ;

    QVector<long double> Coefs ;
} ;

#endif // MAINWINDOW_H
