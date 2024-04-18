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
    static QRegularExpression re("^(RXR)?\\s*(\\d\\d\\d\\d\\d\\d\\d)$", QRegularExpression::CaseInsensitiveOption);

    QRegularExpressionMatch m = re.match(r.trimmed().toUpper());
    if (m.hasMatch()) {
        if (m.hasCaptured(1)) return m.captured(1) + m.captured(2);
        return m.captured(2);
    }

    return r;   // Should be an error string?
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

QString add_rxr(QString r)
{
    return "RXR" + r;
}

QString strip_mrn(QString r)
{
    static QRegularExpression re("^(MRN:)(\\w+)");

    QRegularExpressionMatch m = re.match(r.trimmed());
    if (m.hasMatch()) return m.captured(2);
    return r;
}
