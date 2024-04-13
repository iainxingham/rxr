#ifndef RXRTOOLS_H
#define RXRTOOLS_H

#include <QString>

bool validate_rxr(QString r);
QString clean_rxr(QString r);
bool has_rxr(QString r);
QString chop_rxr(QString r);
QString toggle_rxr(QString r);

#endif // RXRTOOLS_H
