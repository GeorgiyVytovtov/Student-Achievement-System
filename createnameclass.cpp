#include "createnameclass.h"
#include "ui_createnameclass.h"
#include<QRegExpValidator>

CreateNameClass::CreateNameClass(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::CreateNameClass)
{
    ui->setupUi(this);

    ui->clicOk->setEnabled(false);

    // The regular expression is used for a specific organization
    // and can be changed depending on the user organization.
    // The user organization can bea school, college or university.
    QRegExp expr("[1,2,3,4,5,6,7,8,9,10,11]{1,2}[a-zA-Z]{1}");
    ui->lineEdit->setValidator(new QRegExpValidator(expr,this));
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(OkEnabled()));

    connect(ui->clicOk,SIGNAL(clicked(bool)),SLOT(accept()));
    connect(ui->clicCaled,SIGNAL(clicked(bool)),SLOT(reject()));
}

CreateNameClass::~CreateNameClass()
{
    delete ui;
}

QString CreateNameClass::nameClass() const
{
    return ui->lineEdit->text();
}

void CreateNameClass::OkEnabled()
{
    ui->clicOk->setEnabled(ui->lineEdit->hasAcceptableInput());
}
