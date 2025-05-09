//
// Created by blazkowolf on 5/8/25.
//

#ifndef EVENTFLAGS_H
#define EVENTFLAGS_H

#include "ui_EventFlags.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class EventFlags; }
QT_END_NAMESPACE

class EventFlags : public QWidget
{
Q_OBJECT

public:
    explicit EventFlags(QWidget *parent = nullptr);
    ~EventFlags() override;

private:
    Ui::EventFlags *ui;
};

#endif //EVENTFLAGS_H
