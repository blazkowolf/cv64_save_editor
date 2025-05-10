#include "windows/eventflags.h"
#include "ui_eventflags.h"

EventFlagsForm::EventFlagsForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EventFlagsForm)
{
    ui->setupUi(this);
}

EventFlagsForm::~EventFlagsForm()
{
    delete ui;
}
