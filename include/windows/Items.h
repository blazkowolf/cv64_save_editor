#ifndef ITEMS_H
#define ITEMS_H

#include "ui_Items.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Items; }
QT_END_NAMESPACE

class Items : public QWidget
{
    Q_OBJECT

public:
    explicit Items(QWidget *parent = nullptr);
    ~Items() override;

private:
    Ui::Items *ui;
};

#endif //ITEMS_H
