#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>

//#include <memory.h>

#include "code128/code128item.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void update_last_RXR(QString r);
    void restore_last_RXR();
    void clear_RXR();

private slots:
    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_barcode_but_clicked();

    void on_clear_but_clicked();

    void on_last_but_clicked();

    void on_paste_but_clicked();

    void on_copy_but_clicked();

    void on_toggle_but_clicked();

    void on_lpres_but_clicked();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;

    QGraphicsScene barcodeScene;
    //std::unique_ptr<Code128Item> m_Barcode;
    Code128Item *m_Barcode;

    QString lastRXR;
    QString currentRXR;
};
#endif // MAINWINDOW_H
