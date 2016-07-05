#include "operationdialog.h"
#include "ui_operationdialog.h"

#include <QDate>
#include <QMessageBox>

#include <QDebug>

OperationDialog::OperationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperationDialog)
  , m_dbManager( nullptr )
  , m_role( OPERATION_DIALOG_NEW )
{
    ui->setupUi(this);    
}

OperationDialog::~OperationDialog()
{
    delete ui;
}

void OperationDialog::SetDbManager(DBManager *_dbManager)
{
    m_dbManager = _dbManager;
}

void OperationDialog::SetRole(OperationDialog::OPERATION_ROLE _role)
{
    m_role = _role;
}

void OperationDialog::Init()
{
    ui->treeWidget->setHeaderLabels( QStringList() << QString::fromLocal8Bit("이름") << QString::fromLocal8Bit("전화 번호") );


    // date
    QDate today = QDate::currentDate();
    ui->dateEdit->setDate( today );


    // time
    for( int i = 10; i < 21; ++i )
    {
        for( int j = 0; j < 60; j += 30 )
        {
            QString time = QString("%1 : %2").arg(i).arg(j, 2, 10, QChar('0'));
            ui->comboBox_time->addItem( time );
        }
    }

    ui->comboBox_time->setCurrentIndex(8);


    QRegExp phoneNumberRegExp("[0-9]{0,4}");
    ui->lineEdit_phoneNumber->setValidator( new QRegExpValidator( phoneNumberRegExp, this));




    QString temp( "00000000" );
    ui->comboBox_curl->addItem( temp );
    ui->comboBox_curl->setMinimumWidth(ui->comboBox_curl->sizeHint().width() );
    ui->comboBox_curl->clear();

    ui->comboBox_type->addItem( temp );
    ui->comboBox_type->setMinimumWidth(ui->comboBox_type->sizeHint().width() );
    ui->comboBox_type->clear();

    ui->comboBox_color->addItem( temp );
    ui->comboBox_color->setMinimumWidth(ui->comboBox_color->sizeHint().width() );
    ui->comboBox_color->clear();

    ui->comboBox_length->addItem( temp );
    ui->comboBox_length->setMinimumWidth(ui->comboBox_length->sizeHint().width() );
    ui->comboBox_length->clear();

    ui->comboBox_number->addItem( temp );
    ui->comboBox_number->setMinimumWidth(ui->comboBox_number->sizeHint().width() );
    ui->comboBox_number->clear();



    LoadDB();

    on_pushButton_name_clicked();

    if( m_role == OPERATION_DIALOG_NEW )
    {
        Init_New();
    }
    else
    {
        Init_Edit();
    }
}

void OperationDialog::Init_New()
{
    setWindowTitle( QString::fromLocal8Bit( "약속 추가") );
}

void OperationDialog::Init_Edit()
{
    setWindowTitle( QString::fromLocal8Bit( "약속 편집") );

}

void OperationDialog::LoadDB()
{
    qDebug() << __FUNCTION__;

    if( m_dbManager != nullptr )
    {
        QStringList list;

        // Curl
        list = m_dbManager->SelectAllSubTable( TABLE_CURL );

        foreach( const QString& str, list )
        {
            QStringList split = str.split( ':' );

            if( 2 == split.count() )
                ui->comboBox_curl->addItem( split[1], split[0] );
        }

        // Type
        list = m_dbManager->SelectAllSubTable( TABLE_TYPE);

        foreach( const QString& str, list )
        {
            QStringList split = str.split( ':' );

            if( 2 == split.count() )
                ui->comboBox_type->addItem( split[1], split[0] );
        }

        // Color
        list = m_dbManager->SelectAllSubTable( TABLE_COLOR);

        foreach( const QString& str, list )
        {
            QStringList split = str.split( ':' );

            if( 2 == split.count() )
                ui->comboBox_color->addItem( split[1], split[0] );
        }

        // Length
        list = m_dbManager->SelectAllSubTable( TABLE_LENGTH);

        foreach( const QString& str, list )
        {
            QStringList split = str.split( ':' );

            if( 2 == split.count() )
                ui->comboBox_length->addItem( split[1], split[0] );
        }

        // Number
        list = m_dbManager->SelectAllSubTable( TABLE_NUMBER);

        foreach( const QString& str, list )
        {
            QStringList split = str.split( ':' );

            if( 2 == split.count() )
                ui->comboBox_number->addItem( split[1], split[0] );
        }
    }
}

void OperationDialog::on_pushButton_name_clicked()
{
    qDebug() << __FUNCTION__;

    ui->treeWidget->clear();

    if( m_dbManager != nullptr )
    {
        QStringList list;

        if( ui->lineEdit_name->text().isEmpty() )
        {
            list = m_dbManager->SelectClientAll();
        }
        else
        {
            list = m_dbManager->SelectClientWithName( ui->lineEdit_name->text() );
        }

        foreach( const QString & str, list )
        {
            QStringList tmpList = str.split(':');

            if( tmpList.size() != 0 )
            {
                QTreeWidgetItem * item = new QTreeWidgetItem(ui->treeWidget);
                item->setText(0, tmpList[1] );
                item->setText(1, tmpList[2] );
                item->setData(0, Qt::UserRole, tmpList[0]);
                ui->treeWidget->addTopLevelItem( item );
            }

        }
    }

    // search DB with name
}

void OperationDialog::on_pushButton_phoneNumber_clicked()
{
    qDebug() << __FUNCTION__;

    // search DB with phone number

    ui->treeWidget->clear();
    if( m_dbManager != nullptr )
    {
        QStringList list;

        if( ui->lineEdit_phoneNumber->text().isEmpty() )
        {
            list = m_dbManager->SelectClientAll();
        }
        else
        {
            list = m_dbManager->SelectClientWithPhoneNumber( ui->lineEdit_phoneNumber->text() );
        }

        foreach( const QString & str, list )
        {
            QStringList tmpList = str.split(':');

            if( tmpList.size() != 0 )
            {
                QTreeWidgetItem * item = new QTreeWidgetItem(ui->treeWidget);
                item->setText(0, tmpList[1] );
                item->setText(1, tmpList[2] );
                item->setData(0, Qt::UserRole, tmpList[0]);
                ui->treeWidget->addTopLevelItem( item );
            }

        }
    }

}

void OperationDialog::on_lineEdit_name_textChanged(const QString &arg1)
{
    qDebug() << __FUNCTION__;

    on_pushButton_name_clicked();
}

void OperationDialog::on_lineEdit_phoneNumber_textEdited(const QString &arg1)
{
    qDebug() << __FUNCTION__;
    on_pushButton_phoneNumber_clicked();

}



void OperationDialog::on_lineEdit_name_returnPressed()
{
    on_pushButton_name_clicked();

}

void OperationDialog::on_lineEdit_phoneNumber_returnPressed()
{
    on_pushButton_phoneNumber_clicked();
}

void OperationDialog::on_pushButton_OK_clicked()
{
    //qDebug() << ui->treeWidget->currentItem()->data(0, Qt::UserRole );

    // verify

    QTreeWidgetItem* widgetItem = ui->treeWidget->currentItem();
    if( widgetItem == nullptr )
    {
        QMessageBox::warning( this, QString::fromLocal8Bit("에러"), QString::fromLocal8Bit("손님을 선택하세요!") );
        return;
    }

    QString price = ui->lineEdit_price->text();
    if( price.isEmpty() )
    {
        QMessageBox::warning( this, QString::fromLocal8Bit("에러"), QString::fromLocal8Bit("가격을 입력하세요!") );
        return;
    }

    QString clientID = widgetItem->data( 0, Qt::UserRole ).toString();

    QString dateTime = ui->dateEdit->date().toString( "yyyy-MM-dd" );
    QString time = ui->comboBox_time->currentText();

    time.remove(' ');
    dateTime += " " + time;

    //qDebug() << clientID << " | " << dateTime;

    QString curl = ui->comboBox_curl->currentData().toString();

    QString type = ui->comboBox_type->currentData().toString();

    QString color = ui->comboBox_color->currentData().toString();

    QString length = ui->comboBox_length->currentData().toString();

    QString number = ui->comboBox_number->currentData().toString();


    if( m_dbManager != nullptr )
    {
        m_dbManager->InsertOperation( clientID, dateTime, curl, type, color, length, number, price );
    }

    accept();
}

void OperationDialog::on_pushButton_Cancel_clicked()
{
    reject();
}
