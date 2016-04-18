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

    connect( ui->client_treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *,int)),this,SLOT(on_test(QTreeWidgetItem*)));

//    ui->name_pushButton->setEnabled( true );
//    ui->phoneNumber_pushButton->setEnabled( true);

    QRegExp phoneNumberRegExp("[0-9]{0,11}");
    ui->phoneNumber_lineEdit->setValidator( new QRegExpValidator( phoneNumberRegExp, this));

    ui->client_treeWidget->setColumnCount( 4 );
    ui->client_treeWidget->setHeaderLabels( QStringList() << tr("이름") <<  tr("전화 번호") << tr("생년월일") << tr("최근 방문일") << tr(""));

    ui->client_treeWidget->headerItem()->setTextAlignment(0, Qt::AlignCenter);
    ui->client_treeWidget->headerItem()->setTextAlignment(1, Qt::AlignCenter);
    ui->client_treeWidget->headerItem()->setTextAlignment(2, Qt::AlignCenter);
    ui->client_treeWidget->headerItem()->setTextAlignment(3, Qt::AlignCenter);


    ui->operation_treeWidget->setColumnCount( 7 );
    ui->operation_treeWidget->setHeaderLabels( QStringList() << tr("방문일") << tr("컬") << tr("모") << tr("색") << tr("길이")  << tr("숱")  << tr("금액") << tr(""));

    ui->operation_treeWidget->headerItem()->setTextAlignment(0, Qt::AlignCenter);
    ui->operation_treeWidget->headerItem()->setTextAlignment(1, Qt::AlignCenter);
    ui->operation_treeWidget->headerItem()->setTextAlignment(2, Qt::AlignCenter);
    ui->operation_treeWidget->headerItem()->setTextAlignment(3, Qt::AlignCenter);
    ui->operation_treeWidget->headerItem()->setTextAlignment(4, Qt::AlignCenter);
    ui->operation_treeWidget->headerItem()->setTextAlignment(5, Qt::AlignCenter);
    ui->operation_treeWidget->headerItem()->setTextAlignment(6, Qt::AlignCenter);

    QList<int> sizes;
    sizes << 500 << 200;

    ui->splitter->setSizes( sizes );
    ui->splitter->setStretchFactor(0, 0);
    ui->splitter->setStretchFactor(1, 1);

    TestInit();
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

void MainWidget::TestInit()
{


    for( int i = 0; i < 10; ++i )
    {
        QTreeWidgetItem * item = new QTreeWidgetItem(ui->client_treeWidget);
        item->setText(0, tr("이호"));
        item->setText(1, tr("010-4421-0427"));
        item->setText(2, tr("1982-04-27"));
        item->setText(3, tr("2016-03-27"));
        item->setTextAlignment(0, Qt::AlignCenter);
        item->setTextAlignment(1, Qt::AlignCenter);
        item->setTextAlignment(2, Qt::AlignCenter);
        item->setTextAlignment(3, Qt::AlignCenter);
        ui->client_treeWidget->addTopLevelItem( item );
    }






    for( int i = 0; i < 5; ++i )
    {
        QTreeWidgetItem * item2 = new QTreeWidgetItem(ui->operation_treeWidget);
        item2->setText(0, tr("2016-04-18"));
        item2->setText(1, tr("J 컬"));
        item2->setText(2, tr("실크모"));
        item2->setText(3, tr("블랙"));
        item2->setText(4, tr("7mm"));
        item2->setText(5, tr("60%"));
        item2->setText(6, tr("100000"));

        item2->setTextAlignment(0, Qt::AlignCenter);
        item2->setTextAlignment(1, Qt::AlignCenter);
        item2->setTextAlignment(2, Qt::AlignCenter);
        item2->setTextAlignment(3, Qt::AlignCenter);
        item2->setTextAlignment(4, Qt::AlignCenter);
        item2->setTextAlignment(5, Qt::AlignCenter);
        item2->setTextAlignment(6, Qt::AlignCenter);

        ui->operation_treeWidget->addTopLevelItem( item2 );
    }
}
