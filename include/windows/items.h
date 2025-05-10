#ifndef ITEMS_H
#define ITEMS_H

#include <QWidget>

namespace Ui {
class ItemsForm;
}

class ItemsForm : public QWidget
{
    Q_OBJECT

public:
    explicit ItemsForm(QWidget *parent = nullptr);
    ~ItemsForm();

private:
    Ui::ItemsForm *ui;
};

#endif // ITEMS_H
