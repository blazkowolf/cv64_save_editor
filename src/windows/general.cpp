#include "windows/general.h"
#include "ui_general.h"

GeneralForm::GeneralForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GeneralForm)
{
    ui->setupUi(this);
}

GeneralForm::~GeneralForm()
{
    delete ui;
}
