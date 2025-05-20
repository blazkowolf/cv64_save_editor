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
    void populate(Save::Data*) const;

private:
    Ui::EventFlagsForm *m_ui;

    /**< The array of line edits that appear in the "Event Flags" page */
    QLineEdit* m_hexBitflagLineEdits[Save::NUM_EVENT_FLAGS] = {};
};

#endif // EVENTFLAGS_H
