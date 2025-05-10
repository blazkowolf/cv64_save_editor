#ifndef LINEEDITHELPER_H
#define LINEEDITHELPER_H

#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

namespace LineEditHelper {

constexpr QRegularExpression acceptDecimalAndHexRegex(R"(^(\d{1,8}|0[xX][0-9A-Fa-f]{1,8})$)");

template <typename TValue>
void setupNumber(QLineEdit *le, TValue minValue, TValue maxValue, const std::function<void(TValue)> &function = {})
{

    const auto* validator = new QRegularExpressionValidator(acceptDecimalAndHexRegex, this);
    le->setValidator(validator);

    le->setProperty("minValue", minValue);
    le->setProperty("maxValue", maxValue);

    if (function) {
        QObject::connect(le, &QLineEdit::editingFinished, [function, le]() {
            const auto value = le->text().toUInt();
            function(value);
        });
    }
}


/// With this function, we can have more control during lineEdit initialization.
/// In this case, we make it so that we can add a min and max value to each lineEdit without much copy-pasting
// void setupLineEditNumberUnsigned(QLineEdit* lineEdit, const std::uint32_t minValue, const std::uint32_t maxValue, std::function<void(std::uint32_t)> setter) {
//     // Using this regex, we can accept either only hex values (preceded "0x") or decimal values
//     // of up to 8 digits long (to prevent them from overflowing the max std::int32_t / uint)
//     QRegularExpression acceptDecimalAndHexRegex(R"(^(\d{1,8}|0[xX][0-9A-Fa-f]{1,8})$)");
//     const auto* validator = new QRegularExpressionValidator(acceptDecimalAndHexRegex, this);
//     lineEdit->setValidator(validator);
//
//     lineEdit->setProperty("minValue", minValue);
//     lineEdit->setProperty("maxValue", maxValue);
//
//     connect(lineEdit, &QLineEdit::editingFinished, this, [this, setter, lineEdit]() {
//         handleNumberOnlyInputUnsigned(setter, lineEdit);
//     });
// }

}

#endif //LINEEDITHELPER_H
