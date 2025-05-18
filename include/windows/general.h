#ifndef GENERAL_H
#define GENERAL_H

#include "save/Save.h"

#include <QWidget>

namespace Ui {
class GeneralForm;
}

class GeneralForm : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralForm(QWidget *parent = nullptr);
    ~GeneralForm();
    void setup();
    void populate(SaveData*) const;

private:
    Ui::GeneralForm *ui;
};

#endif // GENERAL_H
