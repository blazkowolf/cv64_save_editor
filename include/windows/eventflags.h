#ifndef EVENTFLAGS_H
#define EVENTFLAGS_H

#include <QWidget>

namespace Ui {
class EventFlagsForm;
}

class EventFlagsForm : public QWidget
{
    Q_OBJECT

public:
    explicit EventFlagsForm(QWidget *parent = nullptr);
    ~EventFlagsForm();

private:
    Ui::EventFlagsForm *ui;
};

#endif // EVENTFLAGS_H
