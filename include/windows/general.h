#ifndef GENERAL_H
#define GENERAL_H

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

private:
    Ui::GeneralForm *ui;
};

#endif // GENERAL_H
