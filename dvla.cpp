#include "dvla.h"
#include "ui_dvla.h"

#include <QMessageBox>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QDate>
#include <QTime>

QString INVOICE_ADDRESS = "Placeholder";


DVLA::DVLA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DVLA)
{
    ui->setupUi(this);

    ui->cb_salutation->addItem("");
    ui->cb_salutation->addItem("Mr");
    ui->cb_salutation->addItem("Ms");
    ui->cb_salutation->addItem("Dr");

    cancel_invoice = true;
    db = std::make_unique<Database>();
}

DVLA::~DVLA()
{
    delete ui;
}

void DVLA::set_rxr(QString r)
{
    ui->le_rxr->setText(r);
}

void DVLA::set_nhs(QString n)
{
    ui->le_nhs->setText(n);
}

void DVLA::on_buttonBox_accepted()
{
    if(!generate_invoice()) {
        QMessageBox msg(this);

        msg.setWindowTitle("Error");
        msg.setText("Something went wrong creating the DVLA invoice");
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
    }

    if(!write_dvla_log(get_current_date(),
                   get_current_time(),
                   ui->le_rxr->text(),
                   ui->le_nhs->text(),
                   ui->le_dvla->text(),
                   ui->le_fname->text(),
                   ui->le_sname->text(),
                   QString::number(current_invoice_number),
                   ui->cb_salutation->currentText(),
                   QString::number(dvla_fee))) {

        QMessageBox msg(this);

        msg.setWindowTitle("Error");
        msg.setText("Something went wrong writing to the log of DVLA invoices");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }

    ++current_invoice_number;
}

void DVLA::on_buttonBox_rejected()
{
    cancel_invoice = true;
}

void DVLA::closeEvent(QCloseEvent *event)
{
    if(cancel_invoice) {
        QMessageBox msg(this);

        msg.setWindowTitle("Warning");
        msg.setText("Are you sure? No DVLA invoice will be created.");
        msg.setIcon(QMessageBox::Warning);
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg.setDefaultButton(QMessageBox::No);
        int ret = msg.exec();

        if(ret == QMessageBox::Yes) event->accept();
        else event->ignore();
    }

    else event->accept();
}

void DVLA::reject()
{
    QMessageBox msg(this);

    msg.setWindowTitle("Warning");
    msg.setText("Are you sure? No DVLA invoice will be created.");
    msg.setIcon(QMessageBox::Warning);
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    int ret = msg.exec();

    if(ret == QMessageBox::Yes) QDialog::reject();
}

bool DVLA::generate_invoice()
{
    QPrinter printer;

    QPrintDialog qpd(&printer, this);
    if(qpd.exec() == QDialog::Accepted) {
        QPainter painter;
        QRect rect;
        QFont font;
        QString item;

        painter.begin(&printer);

        // Need to replace pmw->config with calls to database methods

        font = painter.font();
        pmw->config->get_rect("address_pos", &rect);
        painter.drawText(rect, INVOICE_ADDRESS);
        pmw->config->get_rect("date_pos", &rect);
        painter.drawText(rect, get_current_date());

        pmw->config->get_rect("payable_pos", &rect);
        painter.drawText(rect, "Please make cheques payable to placeholder");

        pmw->config->get_rect("invoice_num_pos", &rect);
        item = QString("Invoice number %1\\%2")
                   .arg("Invoice lead placeholder")
                   .arg(current_invoice_number, 5, 10, QChar('0'));
        painter.drawText(rect, item);
        pmw->config->get_rect("reference_pos", &rect);
        item = QString("Your reference: %1").arg(ui->le_dvla->text());
        painter.drawText(rect, item);

        pmw->config->get_rect("report_pos", &rect);
        item = QString("%1\tMedical report on %2 %3 %4")
                .arg(get_current_date())
                .arg(ui->cb_salutation->currentText())
                .arg(ui->le_fname->text().at(0).toUpper())
                .arg(ui->le_sname->text());
        painter.drawText(rect, item);

        pmw->config->get_rect("fee_pos", &rect);
        item = QString("£%1.00").arg(dvla_fee);
        painter.drawText(rect, item);
        pmw->config->get_rect("total_fee_pos", &rect);
        painter.drawText(rect, item);
        pmw->config->get_rect("total_pos", &rect);
        painter.drawText(rect, "Total");

        pmw->config->get_rect("invoice_pos", &rect);
        font.setBold(true);
        font.setPixelSize(32);
        painter.setFont(font);
        painter.drawText(rect, "INVOICE");

        painter.end();
    }

    return true;
}

QString DVLA::get_rxr()
{
    return ui->le_rxr->text();
}

QString DVLA::get_current_date()
{
    QDate d;

    return d.currentDate().toString("dd\\MM\\yyyy");
}

QString DVLA::get_current_time()
{
    QTime t;

    return t.currentTime().toString("hh:mm");
}
