#include "windows/General.h"

General::General(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::General)
{
    ui->setupUi(this);
}

General::~General()
{
    delete ui;
}
