#ifndef DVLA_H
#define DVLA_H

#include <QDialog>
#include <QCloseEvent>

#include <memory>

#include "database.h"

#define DVLA_INVOICE_PRINT_FILE     "./dvla_invoice%1.pdf"

namespace Ui {
class DVLA;
}

class DVLA : public QDialog
{
    Q_OBJECT

public:
    explicit DVLA(QWidget *parent = nullptr);
    ~DVLA();

    void set_rxr(QString r);
    void set_nhs(QString n);
    void reject();
    void set_invoice_number(int n) {current_invoice_number = n;}
    void set_dvla_fee(int n) {dvla_fee = n;}
    QString get_rxr();

    QString get_current_date();
    QString get_current_time();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void closeEvent(QCloseEvent *event);

private:
    Ui::DVLA *ui;

    bool generate_invoice();

    bool cancel_invoice;
    int dvla_fee;
    int current_invoice_number;
    std::unique_ptr<Database> db;
};

#endif // DVLA_H
