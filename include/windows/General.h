//
// Created by blazkowolf on 5/8/25.
//

#ifndef GENERAL_H
#define GENERAL_H

#include "ui_General.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class General; }
QT_END_NAMESPACE

class General : public QWidget
{
Q_OBJECT

public:
    explicit General(QWidget *parent = nullptr);
    ~General() override;

private:
    Ui::General *ui;
};

#endif //GENERAL_H
