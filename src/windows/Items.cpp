#include "windows/Items.h"

Items::Items(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Items)
{
    ui->setupUi(this);
}

Items::~Items()
{
    delete ui;
}