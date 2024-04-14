#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QClipboard>
#include <QDesktopServices>
#include <QUrl>

#include <memory>

#include "about.h"
#include "rxrtools.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->barcode_gv->setScene(&barcodeScene);

    m_Barcode = new Code128Item();
    m_Barcode->setWidth(300);
    m_Barcode->setHeight(120);
    m_Barcode->setPos(0, 0);
    barcodeScene.addItem(m_Barcode);
    barcodeScene.update();
    m_Barcode->update();

    lastRXR = "";
    currentRXR = "";
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
    std::unique_ptr<About> about = std::make_unique<About>(this);

    about->exec();
}


void MainWindow::on_barcode_but_clicked()
{
    if(validate_rxr(ui->rxr_le->text())) {
        QString r(clean_rxr(ui->rxr_le->text()));
        m_Barcode->setText(r);
        update_last_RXR(r);
    }

    else {
        QMessageBox msg(this);

        msg.setWindowTitle("Invalid RXR number");
        msg.setText("RXR numbers should consist of exactly seven digits, possibly preceded by \"rxr\" or \"RXR\".");
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
    }

    barcodeScene.update();
    m_Barcode->update();
}

void MainWindow::update_last_RXR(QString r)
{
    if (r == "") return;
    if (currentRXR == r) return;
    if ((currentRXR == lastRXR) and (currentRXR != "")) return;

    lastRXR = currentRXR;
    currentRXR = r;
}

void MainWindow::restore_last_RXR()
{
    if(lastRXR == "") {
        clear_RXR();
        return;
    }

    currentRXR = lastRXR;
    lastRXR = "";

    ui->rxr_le->setText(currentRXR);
    m_Barcode->setText(currentRXR);
    barcodeScene.update();
    m_Barcode->update();
}

void MainWindow::clear_RXR()
{
    ui->rxr_le->setText("");
    m_Barcode->setText("");
    barcodeScene.update();
    m_Barcode->update();

    currentRXR = "";
}

void MainWindow::on_clear_but_clicked()
{
    update_last_RXR("");
    clear_RXR();
}


void MainWindow::on_last_but_clicked()
{
    restore_last_RXR();
}


void MainWindow::on_paste_but_clicked()
{
    QClipboard *clip = QGuiApplication::clipboard();
    QString r = clip->text();

    if (validate_rxr(r)) {
        ui->rxr_le->setText(r);
        on_barcode_but_clicked();
    }
    else {
        QMessageBox msg(this);

        msg.setWindowTitle("Invalid RXR number");
        msg.setText("The clipboard does not contain a valid RXR number.");
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
    }
}


void MainWindow::on_copy_but_clicked()
{
    QClipboard *clip = QGuiApplication::clipboard();
    clip->setText(ui->rxr_le->text());
}


void MainWindow::on_toggle_but_clicked()
{
    QString r = toggle_rxr(currentRXR);
    currentRXR = r;
    ui->rxr_le->setText(r);
    m_Barcode->setText(r);
    barcodeScene.update();
    m_Barcode->update();
}


void MainWindow::on_lpres_but_clicked()
{
    if (validate_rxr(ui->rxr_le->text())) {
        on_barcode_but_clicked();
        QString u = "elht-app-web1/lpres/openviewer/?rxr=&person=" + (has_rxr(currentRXR) ? currentRXR : add_rxr(currentRXR));
        QDesktopServices::openUrl(QUrl(u));
    }
    else {
        QMessageBox msg(this);

        msg.setWindowTitle("Invalid RXR number");
        msg.setText("RXR numbers should consist of exactly seven digits, possibly preceded by \"rxr\" or \"RXR\".");
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
    }
}

void MainWindow::on_action_triggered()
{
    on_lpres_but_clicked();
}

