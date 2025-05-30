/**
 * @file lineedit.h
 *
 * Provides common setup utilities for bootstrapping a LineEdit.
 */

#ifndef LINEEDITHELPER_H
#define LINEEDITHELPER_H

#include <QString>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

namespace LineEdit {

inline void setup(QLineEdit *le, const QString &defaultValue, const QValidator *validator = nullptr, const std::function<void(QString)> &function = {})
{
    // const auto* validator = new QRegularExpressionValidator(acceptDecimalAndHexRegex, target);
    if (validator) {
        le->setValidator(validator);
    }
    // le->setProperty("minValue", minValue);
    // le->setProperty("maxValue", maxValue);
    if (function) {
        QObject::connect(le, &QLineEdit::editingFinished, [function, le]() {
            const auto value = le->text();
            function(value);
        });
        function(defaultValue);
    }
}

// template <typename TTarget, typename TFunction>
// void setup(QLineEdit *le, const QString &defaultValue, TTarget *target, const QValidator *validator = nullptr, TFunction function)
// {
//     setup(le, defaultValue, validator);
//     if (validator) {
//         le->setValidator(validator);
//     }
//     QObject::connect(le, &QLineEdit::editingFinished, [function, le, target]() {
//         const auto value = le->text().toUInt();
//         std::invoke(function, target, value);
//     });
//     std::invoke(function, target, defaultValue);
// }

template <typename TValue>
TValue handleUnsignedInteger(const QString &text, const TValue min, const TValue max)
{
    static_assert(std::is_unsigned_v<TValue>, "TValue must be an unsigned integral type");
    auto ok = false;
    const auto isHex = text.startsWith("0x", Qt::CaseInsensitive);
    auto value = static_cast<TValue>(isHex ? text.mid(2).toUInt(&ok, 16) : text.toUInt(&ok, 10));
    if (!ok)
        return 0;
    value = qBound<TValue>(min, value, max);
    // checkMandragoraAndNitroLineEdits();
    return value;
}

}

#endif //LINEEDITHELPER_H
