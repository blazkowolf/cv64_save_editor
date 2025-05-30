#ifndef CHECKBOXHELPER_H
#define CHECKBOXHELPER_H

#include <QCheckBox>
#include <QObject>

namespace CheckBox {

/**
 * When we press on a checkbox, a setter function will be called that will set a certain value.
 * Likewise, when we uncheck them, an unsetter function will be called which will remove the value setted in the setter.
 */
template <typename TValue>
void setup(QCheckBox* cb, TValue value, const std::function<void(TValue)> &setter, const std::function<void(TValue)> &unsetter)
{
    QObject::connect(cb, &QCheckBox::toggled, [setter, unsetter, value](const bool checked) {
        if (checked) {
            setter(value);
        } else {
            unsetter(value);
        }
    });
}

inline void setup(QCheckBox* cb, const std::function<void()> &setter, const std::function<void()> &unsetter)
{
    QObject::connect(cb, &QCheckBox::toggled, [setter, unsetter](const bool checked) {
        if (checked) {
            setter();
        } else {
            unsetter();
        }
    });
}

}

#endif //CHECKBOXHELPER_H
