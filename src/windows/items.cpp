#include "windows/items.h"
#include "ui_items.h"

ItemsForm::ItemsForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ItemsForm)
{
    ui->setupUi(this);
}

ItemsForm::~ItemsForm()
{
    delete ui;
}
