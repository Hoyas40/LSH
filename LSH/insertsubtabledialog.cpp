#include "insertsubtabledialog.h"
#include "ui_insertsubtabledialog.h"

#include <QDebug>

InsertSubTableDialog::InsertSubTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertSubTableDialog)
{
    ui->setupUi(this);

    ui->lineEdit_id->setEnabled( false );
}

InsertSubTableDialog::~InsertSubTableDialog()
{
    delete ui;
}

void InsertSubTableDialog::SetId(const QString &_id)
{
    qDebug() << __FUNCTION__;
    ui->lineEdit_id->setText( _id );
}

QString InsertSubTableDialog::GetName() const
{
    return ui->lineEdit_name->text();
}
