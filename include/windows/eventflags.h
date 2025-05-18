#ifndef EVENTFLAGS_H
#define EVENTFLAGS_H

#include "save/Save.h"

#include <QWidget>
#include <QLineEdit>

namespace Ui {
class EventFlagsForm;
}

class EventFlagsForm : public QWidget
{
    Q_OBJECT

public:
    explicit EventFlagsForm(QWidget *parent = nullptr);
    ~EventFlagsForm();
    void setup();
    void populate(SaveData*) const;

private:
    Ui::EventFlagsForm *ui;

    /**< The array of line edits that appear in the "Event Flags" page */
    QLineEdit* hexBitflagLineEdits[NUM_EVENT_FLAGS] = {};
};

#endif // EVENTFLAGS_H
