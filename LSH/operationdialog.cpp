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
    ui->treeWidget->setHeaderLabels( QStringList() << QString::fromLocal8Bit("이름")
                                     << QString::fromLocal8Bit("전화 번호")
                                     );



    ui->treeWidget_operation->setHeaderLabels( QStringList() << QString::fromLocal8Bit("날짜")
                                               << QString::fromLocal8Bit("시간")
                                               << QString::fromLocal8Bit("컬")
                                               << QString::fromLocal8Bit("모")
                                               << QString::fromLocal8Bit("리터치")
                                               );

    ui->treeWidget_operation->header()->resizeSection(0, 120);
    ui->treeWidget_operation->header()->resizeSection(1, 60);
    ui->treeWidget_operation->header()->resizeSection(2, 50);
    ui->treeWidget_operation->header()->resizeSection(3, 50);
    ui->treeWidget_operation->header()->resizeSection(4, 60);



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


    ui->comboBox_retouch->addItem( temp );
    ui->comboBox_retouch->setMinimumWidth(ui->comboBox_retouch->sizeHint().width() );
    ui->comboBox_retouch->clear();
    ui->comboBox_retouch->addItem( "X" );
    ui->comboBox_retouch->addItem( "O" );


    LoadDB();



    if( m_role == OPERATION_DIALOG_NEW )
    {
        Init_New();
    }
    else
    {
        Init_Edit();
    }
}

void OperationDialog::SetDate(const QDate &_date)
{
    ui->dateEdit->setDate( _date );
}

void OperationDialog::SetOperationId(const QString &_operationId)
{
    m_operationId = _operationId;
}

void OperationDialog::Init_New()
{
    on_pushButton_name_clicked();
    setWindowTitle( QString::fromLocal8Bit( "약속 추가") );
}

void OperationDialog::Init_Edit()
{
    setWindowTitle( QString::fromLocal8Bit( "약속 편집") );


    // restore options

    if( m_dbManager != nullptr )
    {
        QString str = m_dbManager->SelectOperationWithID( m_operationId );

        //qDebug() << str;
        QStringList itemList = str.split('|');


        // time info
        QStringList dateTimeList = itemList[2].split(' ');
        QString dateStr = dateTimeList[0];
        QStringList dateList = dateStr.split('-');

        QDate date = QDate( dateList[0].toInt(), dateList[1].toInt(), dateList[2].toInt());

        this->SetDate( date );


        QString timeStr = dateTimeList[1];
        timeStr.insert(2, ' ');
        timeStr.insert(4, ' ');

        int index = ui->comboBox_time->findText(timeStr);
        if( index != -1 )
            ui->comboBox_time->setCurrentIndex( index );
        else
            qDebug() << "Time not found";


        // client info
        QString clientID = itemList[1];
        QString queryWithID = m_dbManager->SelectClientWithId( clientID );
        QString clientName = queryWithID.split( '|' )[1];
        QString phoneNumber = queryWithID.split( '|' )[2];

        ui->lineEdit_name->setText( clientName );
        ui->lineEdit_phoneNumber->setText( phoneNumber );
        on_lineEdit_phoneNumber_returnPressed();

        if( ui->treeWidget->topLevelItem(0) != nullptr )
            ui->treeWidget->setCurrentItem( ui->treeWidget->topLevelItem(0) );


        // curl
        QString curlId = itemList[3];
        //QString curlQuery = m_dbManager->SelectSubTableWithId( TABLE_CURL, curlId );
        index = ui->comboBox_curl->findData( curlId );
        if( index != -1 )
            ui->comboBox_curl->setCurrentIndex( index );
        else
            qDebug() << "Curl not found";


        // type
        QString typeId = itemList[4];
        //QString typeQuery = m_dbManager->SelectSubTableWithId( TABLE_TYPE, typeId );
        index = ui->comboBox_type->findData( typeId );
        if( index != -1 )
            ui->comboBox_type->setCurrentIndex( index );
        else
            qDebug() << "Type not found";


        // color
        QString colorId = itemList[5];
        //QString colorQuery = m_dbManager->SelectSubTableWithId( TABLE_COLOR, colorId );
        index = ui->comboBox_color->findData( colorId );
        if( index != -1 )
            ui->comboBox_color->setCurrentIndex( index );
        else
            qDebug() << "Color not found";


        //length
        QString lengthId = itemList[6];
        //QString lengthQuery = m_dbManager->SelectSubTableWithId( TABLE_LENGTH, lengthId );
        index = ui->comboBox_length->findData( lengthId );
        if( index != -1 )
            ui->comboBox_length->setCurrentIndex( index );
        else
            qDebug() << "Length not found";



        //number
        QString numberId = itemList[7];
        //QString numberQuery = m_dbManager->SelectSubTableWithId( TABLE_NUMBER, numberId );
        index = ui->comboBox_number->findData( numberId );
        if( index != -1 )
            ui->comboBox_number->setCurrentIndex( index );
        else
            qDebug() << "number not found";


        // price
        QString price = itemList[8];

        ui->lineEdit_price->setText( price );

        // option
        QString optionStr = itemList[9];

        int option = optionStr.toInt();

        //bool bShown = option & 0x00000001;
        bool bRetouch = option & 0x00000002;

        if( bRetouch )
        {
            index = ui->comboBox_retouch->findText( "O" );
            if( index != -1 )
                ui->comboBox_retouch->setCurrentIndex( index );
            else
                qDebug() << "number not found";
        }
        else
        {
            index = ui->comboBox_retouch->findText( "X" );
            if( index != -1 )
                ui->comboBox_retouch->setCurrentIndex( index );
            else
                qDebug() << "number not found";
        }

//        QTreeWidgetItem * item = new QTreeWidgetItem(ui->treeWidget);
//        item->setText(0, timeStr );
//        item->setText(1, clientName );
//        item->setText(2, curlQuery.split('|')[1] );
//        item->setText(3, typeQuery.split('|')[1] );
//        item->setText(4, colorQuery.split('|')[1] );
//        item->setText(5, lengthQuery.split('|')[1] );
//        item->setText(6, numberQuery.split('|')[1] );
//        item->setText(7, price );
////            item->setTextAlignment(0, Qt::AlignCenter);
////            item->setTextAlignment(1, Qt::AlignCenter);
////            item->setTextAlignment(2, Qt::AlignCenter);
////            item->setTextAlignment(3, Qt::AlignCenter);

//        if( bShown )
//        {
//            for( int i = 0; i < 4; ++i )
//            {
//                item->setBackgroundColor( i, Qt::black );
//                item->setTextColor( i, Qt::white );
//            }
//        }

//        item->setText(8, bRetouch ? "O" : "X" );

//        item->setData(0, Qt::UserRole, itemList[0] );

//        ui->treeWidget->addTopLevelItem( item );

        //qDebug() << clientName << timeStr << curlId << price << shown;
    }

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
            QStringList split = str.split( '|' );

            if( 2 == split.count() )
                ui->comboBox_curl->addItem( split[1], split[0] );
        }

        // Type
        list = m_dbManager->SelectAllSubTable( TABLE_TYPE);

        foreach( const QString& str, list )
        {
            QStringList split = str.split( '|' );

            if( 2 == split.count() )
                ui->comboBox_type->addItem( split[1], split[0] );
        }

        // Color
        list = m_dbManager->SelectAllSubTable( TABLE_COLOR);

        foreach( const QString& str, list )
        {
            QStringList split = str.split( '|' );

            if( 2 == split.count() )
                ui->comboBox_color->addItem( split[1], split[0] );
        }

        // Length
        list = m_dbManager->SelectAllSubTable( TABLE_LENGTH);

        foreach( const QString& str, list )
        {
            QStringList split = str.split( '|' );

            if( 2 == split.count() )
                ui->comboBox_length->addItem( split[1], split[0] );
        }

        // Number
        list = m_dbManager->SelectAllSubTable( TABLE_NUMBER);

        foreach( const QString& str, list )
        {
            QStringList split = str.split( '|' );

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
            QStringList tmpList = str.split('|');

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
            QStringList tmpList = str.split('|');

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
    QTreeWidgetItem* widgetItem = ui->treeWidget->currentItem();
    if( widgetItem == nullptr )
    {
        QMessageBox::warning( this, QString::fromLocal8Bit("에러"), QString::fromLocal8Bit("손님을 선택해라잉!") );
        return;
    }

    QString price = ui->lineEdit_price->text();
    if( price.isEmpty() )
    {
        QMessageBox::warning( this, QString::fromLocal8Bit("에러"), QString::fromLocal8Bit("가격 입력은 필수입니닷!") );
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

    QString retouch = ui->comboBox_retouch->currentText();

    QString optionStr;

    int option = 0;

    if( retouch == "O" )
        option += 2;
    optionStr = QString::number( option );

    if( m_dbManager != nullptr )
    {
        if( m_role == OPERATION_DIALOG_NEW )
            m_dbManager->InsertOperation( clientID, dateTime, curl, type, color, length, number, price, optionStr);
        else if( m_role == OPERATION_DIALOG_EDIT )
            m_dbManager->UpdateOperation( m_operationId, clientID, dateTime, curl, type, color, length, number, price, optionStr);
    }

    accept();
}

void OperationDialog::on_pushButton_Cancel_clicked()
{
    reject();
}

void OperationDialog::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    qDebug() << __FUNCTION__;

    ui->treeWidget_operation->clear();

    QString clientID = item->data(0, Qt::UserRole).toString();


    if( m_dbManager != nullptr )
    {
        QStringList queryResult = m_dbManager->SelectOperationWithClientID( clientID );

        foreach( const QString& str, queryResult )
        {
            QStringList itemList = str.split('|');

            // time info
            QStringList dateTimeList = itemList[2].split(' ');
            QString timeStr = dateTimeList[1];
            QString dateStr = dateTimeList[0];


            // client info
            //QString clientID = itemList[1];
            //QString queryWithID = m_dbManager->SelectClientWithId( clientID );
            //QString clientName = queryWithID.split( '|' )[1];


            // curl
            QString curlId = itemList[3];
            QString curlQuery = m_dbManager->SelectSubTableWithId( TABLE_CURL, curlId );

            // type
            QString typeId = itemList[4];
            QString typeQuery = m_dbManager->SelectSubTableWithId( TABLE_TYPE, typeId );

//            // color
//            QString colorId = itemList[5];
//            QString colorQuery = m_dbManager->SelectSubTableWithId( TABLE_COLOR, colorId );

//            //length
//            QString lengthId = itemList[6];
//            QString lengthQuery = m_dbManager->SelectSubTableWithId( TABLE_LENGTH, lengthId );


//            //number
//            QString numberId = itemList[7];
//            QString numberQuery = m_dbManager->SelectSubTableWithId( TABLE_NUMBER, numberId );

//            // price
//            QString price = itemList[8];
            QString optionStr = itemList[9];

            int option = optionStr.toInt();

            bool bRetouch = option & 0x00000002;

            QTreeWidgetItem * item = new QTreeWidgetItem(ui->treeWidget_operation);

            item->setText(0, dateStr );
            item->setText(1, timeStr );
            item->setText(2, curlQuery.split('|')[1] );
            item->setText(3, typeQuery.split('|')[1] );
            item->setText(4, bRetouch ? "O" : "X" );


            ui->treeWidget_operation->addTopLevelItem( item );
        }
    }
}


