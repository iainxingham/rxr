#include "rxrtools.h"

#include <QRegularExpression>

bool validate_rxr(QString r)
{
    static QRegularExpression re("^(rxr)?\\s*\\d\\d\\d\\d\\d\\d\\d$", QRegularExpression::CaseInsensitiveOption);

    QRegularExpressionMatch m = re.match(r.trimmed().toUpper(), 0);
    return m.hasMatch();
}

QString clean_rxr(QString r)
{
    return r.trimmed().toUpper();
}

bool has_rxr(QString r)
{
    static QRegularExpression re("^(rxr)", QRegularExpression::CaseInsensitiveOption);

    QRegularExpressionMatch m = re.match(r);
    return m.hasMatch();
}

QString chop_rxr(QString r)
{
    static QRegularExpression re("\\d\\d\\d\\d\\d\\d\\d");

    QRegularExpressionMatch m = re.match(r);
    if (m.hasMatch()) return m.captured(0);
    return "Error in toggle_rxr()";
}

QString toggle_rxr(QString r)
{
    if (has_rxr(r)) return chop_rxr(r);

    return "RXR" + r;
}
