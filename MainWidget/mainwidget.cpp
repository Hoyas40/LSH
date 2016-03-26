#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QRegExp>
#include <QMessageBox>
#include <QStringList>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    connect( ui->name_lineEdit,SIGNAL(textChanged(QString)), this, SLOT(on_name_lineEdit_textChanged()) );
    connect( ui->phoneNumber_lineEdit,SIGNAL(textChanged(QString)), this, SLOT(on_phoneNumber_lineEdit_textChanged()) );

    connect( ui->name_pushButton, SIGNAL(clicked(bool)), this, SLOT(on_name_pushButton_pressed()));
    connect( ui->phoneNumber_pushButton, SIGNAL(clicked(bool)), this, SLOT( on_phoneNumber_pushButton_pressed()) );

    connect( ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *,int)),this,SLOT(on_test(QTreeWidgetItem*)));

//    ui->name_pushButton->setEnabled( true );
//    ui->phoneNumber_pushButton->setEnabled( true);

    QRegExp phoneNumberRegExp("[0-9]{0,11}");
    ui->phoneNumber_lineEdit->setValidator( new QRegExpValidator( phoneNumberRegExp, this));

    ui->treeWidget->setColumnCount( 4 );
    ui->treeWidget->setHeaderLabels( QStringList() << tr("이름") <<  tr("전화 번호") << tr("생년월일") << tr("최근 방문일") );

    QTreeWidgetItem * item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0, tr("이호"));
    item->setText(1, tr("010-4421-0427"));
    item->setText(2, tr("1982-04-27"));
    item->setText(3, tr("2016-03-27"));

    ui->treeWidget->addTopLevelItem( item );
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_name_lineEdit_textChanged()
{
//    if( !ui->name_lineEdit->text().isEmpty() )
//        ui->name_pushButton->setEnabled( true );
//    else
//        ui->name_pushButton->setEnabled( false );
}

void MainWidget::on_phoneNumber_lineEdit_textChanged()
{
    if( ui->phoneNumber_lineEdit->hasAcceptableInput() )
        ui->phoneNumber_pushButton->setEnabled( true );
    else
        ui->phoneNumber_pushButton->setEnabled( false );
}

void MainWidget::on_name_pushButton_pressed()
{
    QMessageBox::information( NULL, tr("Name"), tr("Name pressed") );
}

void MainWidget::on_phoneNumber_pushButton_pressed()
{
    QMessageBox::information( NULL, tr("Phone number"), tr("Phone number") );
}

void MainWidget::on_test(QTreeWidgetItem * item)
{
    QMessageBox::information( NULL, item->text(0), item->text(1) );
}
