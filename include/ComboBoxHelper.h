/**
 * @file ComboBoxHelper.h
 *
 * Provides common setup utilities for bootstrapping a ComboBox with values
 * and display strings.
 *
 * Yoinked from:
 * https://github.com/KDABLabs/kdabtv/blob/master/Qt-Widgets-and-more/Qt6Migration/ComboBoxSetup-Good/ComboBoxHelper.h
 */

#ifndef COMBOBOXHELPER_H
#define COMBOBOXHELPER_H

#include <QComboBox>
#include <QObject>
#include <QString>
#include <QVariant>
#include <functional>

namespace ComboBoxHelper {

template <typename TValue>
struct Item
{
    Item(const QString &text, const TValue &value)
        : text(text)
        , value(value)
    {
    }
    const QString text;
    const TValue value;
};

template <typename TValue>
void setup(QComboBox *cb, TValue defaultValue, const QVector<Item<TValue>> &list,
           const std::function<void(TValue)> &function = {})
{
    for (const auto &item : list) {
        cb->addItem(item.text, QVariant::fromValue(item.value));
        if (item.value == defaultValue) {
            cb->setCurrentIndex(cb->count() - 1);
        }
    }
    if (function) {
        QObject::connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged), [function, cb] {
            const auto value = cb->currentData().value<TValue>();
            function(value);
        });
        function(defaultValue);
    }
}

template <typename TValue, typename TTarget, typename TFunction>
void setup(QComboBox *cb, TValue defaultValue, const QVector<Item<TValue>> &list,
           TTarget *target, TFunction function)
{
    setup(cb, defaultValue, list);
    QObject::connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [function, cb, target] {
                         const auto value = cb->currentData().value<TValue>();
                         std::invoke(function, target, value);
                     });
    std::invoke(function, target, defaultValue);
}

template <typename T>
void setCurrentValue(QComboBox *cb, T value)
{
    const auto data = QVariant::fromValue(value);
    // Workaround to fix a bug where some comboboxes wouldn't update properly when setting
    // an option whose value was 0.
    // if (data.toInt() == 0) {
    //     cb->setCurrentIndex(0);
    //     return;
    // }
    auto index = cb->findData(data);
    Q_ASSERT(index != -1);
    cb->setCurrentIndex(index);
}

}

#endif // !COMBOBOXHELPER_H
