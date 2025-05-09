#include "windows/EventFlags.h"

EventFlags::EventFlags(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EventFlags)
{
    ui->setupUi(this);
}

EventFlags::~EventFlags()
{
    delete ui;
}
