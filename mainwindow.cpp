#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "about.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->barcode_gv->setScene(&barcodeScene);

    m_Barcode = new Code128Item();
    m_Barcode->setWidth( 300 );
    m_Barcode->setHeight( 120 );
    m_Barcode->setPos(0,0);
    barcodeScene.addItem( m_Barcode );
    barcodeScene.update();
    m_Barcode->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionAbout_triggered()
{
    About *about;

    about = new About(this);
    about->exec();
    delete about;
}

