#include "clientwidget.h"
#include "ui_clientwidget.h"

#include <QMessageBox>
#include <Qmenu>

#include "dbmanager.h"
#include "clientdialog.h"
#include "operationdialog.h"

ClientWidget::ClientWidget(QWidget *parent, DBManager* _dbManager) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
  , m_dbManager( _dbManager )
{
    ui->setupUi(this);

    // client widget

    ui->treeWidget_client->setHeaderLabels( QStringList() <<
                                            QString::fromLocal8Bit("이름") <<
                                            QString::fromLocal8Bit("전화 번호") <<
                                            QString::fromLocal8Bit("방문 경로") <<
                                            QString::fromLocal8Bit("비고") );

    ui->treeWidget_client->header()->resizeSection(0, 120 );
    ui->treeWidget_client->header()->resizeSection(1, 160 );
    ui->treeWidget_client->header()->resizeSection(2, 240 );

    ui->treeWidget_operation->setAutoFillBackground( true );
    ui->treeWidget_operation->setHeaderLabels( QStringList() <<
                                               QString::fromLocal8Bit("날짜") <<
                                               QString::fromLocal8Bit("시간") <<
                                               QString::fromLocal8Bit("컬") <<
                                               QString::fromLocal8Bit("모") <<
                                               QString::fromLocal8Bit("색상") <<  // 4
                                               QString::fromLocal8Bit("길이") <<
                                               QString::fromLocal8Bit("숱") <<
                                               QString::fromLocal8Bit("가격") <<
                                               QString::fromLocal8Bit("리터치") );

    ui->treeWidget_operation->header()->resizeSection(0, 120);
    ui->treeWidget_operation->header()->resizeSection(1, 90);
    ui->treeWidget_operation->header()->resizeSection(2, 60);
    ui->treeWidget_operation->header()->resizeSection(3, 60);
    ui->treeWidget_operation->header()->resizeSection(4, 70);
    ui->treeWidget_operation->header()->resizeSection(5, 80);
    ui->treeWidget_operation->header()->resizeSection(6, 60);
    ui->treeWidget_operation->header()->resizeSection(7, 80);
    ui->treeWidget_operation->header()->resizeSection(8, 30);



    ui->treeWidget_client->setContextMenuPolicy( Qt::CustomContextMenu );
    connect( ui->treeWidget_client, &QTreeWidget::customContextMenuRequested, this, &ClientWidget::RequestContextFromClient );

    ui->treeWidget_operation->setContextMenuPolicy( Qt::CustomContextMenu );
    connect( ui->treeWidget_operation, &QTreeWidget::customContextMenuRequested, this, &ClientWidget::RequestContextFromOperation );


    on_lineEdit_name_textChanged("");

}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::UpdateClient()
{
    if( !ui->lineEdit_phoneNumber->text().isEmpty() )
        on_pushButton_phoneNumber_clicked();
    else
        on_pushButton_name_clicked();
}

void ClientWidget::UpdateOperation()
{
    ui->treeWidget_operation->clear();
    if( m_dbManager != nullptr )
    {
        QStringList queryResult = m_dbManager->SelectOperationWithClientID( m_clientIDforUpdate );

        foreach( const QString& str, queryResult )
        {
            QStringList itemList = str.split('|');

            // time info
            QStringList dateTimeList = itemList[2].split(' ');
            QString dateStr = dateTimeList[0];
            QString timeStr = dateTimeList[1];


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

            // color
            QString colorId = itemList[5];
            QString colorQuery = m_dbManager->SelectSubTableWithId( TABLE_COLOR, colorId );

            //length
            QString lengthId = itemList[6];
            QString lengthQuery = m_dbManager->SelectSubTableWithId( TABLE_LENGTH, lengthId );


            //number
            QString numberId = itemList[7];
            QString numberQuery = m_dbManager->SelectSubTableWithId( TABLE_NUMBER, numberId );

            // price
            QString price = itemList[8];
            QString optionStr = itemList[9];

            int option = optionStr.toInt();

            bool bRetouch = option & 0x00000002;

            QTreeWidgetItem * item = new QTreeWidgetItem(ui->treeWidget_operation);

            item->setText(0, dateStr );
            item->setText(1, timeStr );
            item->setText(2, curlQuery.split('|')[1] );
            item->setText(3, typeQuery.split('|')[1] );
            item->setText(4, colorQuery.split('|')[1] );
            item->setText(5, lengthQuery.split('|')[1] );
            item->setText(6, numberQuery.split('|')[1] );
            item->setText(7, price );
            item->setText(8, bRetouch ? "O" : "X" );


            item->setData(0, Qt::UserRole, itemList[0] );
            ui->treeWidget_operation->addTopLevelItem( item );
        }
    }

}

void ClientWidget::on_lineEdit_phoneNumber_textChanged(const QString &)
{
    on_pushButton_phoneNumber_clicked();
}

void ClientWidget::on_lineEdit_name_textChanged(const QString &)
{
    on_pushButton_name_clicked();
}

void ClientWidget::on_pushButton_name_clicked()
{
    ui->treeWidget_client->clear();
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
                QTreeWidgetItem * item = new QTreeWidgetItem(ui->treeWidget_client);
                item->setText(0, tmpList[1] );
                item->setText(1, tmpList[2] );
                QString contactQueryRes = m_dbManager->SelectSubTableWithId( TABLE_CONTACT, tmpList[3]);
                item->setText(2, contactQueryRes.split('|')[1] );
                item->setText(3, tmpList[4] );
                item->setData(0, Qt::UserRole, tmpList[0]);
                ui->treeWidget_client->addTopLevelItem( item );
            }
        }
    }
}

void ClientWidget::on_pushButton_phoneNumber_clicked()
{
    ui->treeWidget_client->clear();
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
                QTreeWidgetItem * item = new QTreeWidgetItem(ui->treeWidget_client);
                item->setText(0, tmpList[1] );
                item->setText(1, tmpList[2] );
                QString contactQueryRes = m_dbManager->SelectSubTableWithId( TABLE_CONTACT, tmpList[3]);
                item->setText(2, contactQueryRes.split('|')[1] );
                item->setText(3, tmpList[4] );
                item->setData(0, Qt::UserRole, tmpList[0]);
                ui->treeWidget_client->addTopLevelItem( item );
            }
        }
    }
}

void ClientWidget::on_pushButton_add_clicked()
{
    emit SignalAddClient();
}

void ClientWidget::on_pushButton_edit_clicked()
{
    QTreeWidgetItem* widgetItem = ui->treeWidget_client->currentItem();

    if( widgetItem == nullptr )
    {
        QMessageBox::warning( this, QString::fromLocal8Bit("에러"), QString::fromLocal8Bit("손님을 선택해라잉!") );
        return;
    }

    QString clientID = widgetItem->data(0, Qt::UserRole).toString();


    ClientDialog diag;
    diag.SetDbManager( m_dbManager );
    diag.SetRole( ClientDialog::CLIENT_DIALOG_EDIT );
    diag.SetClientId( clientID.toInt() );
    diag.Init();
    if( QDialog::Accepted == diag.exec() )
    {
        UpdateClient();
    }
}

void ClientWidget::on_pushButton_delete_clicked()
{
    QTreeWidgetItem* widgetItem = ui->treeWidget_client->currentItem();

    if( widgetItem == nullptr )
    {
        QMessageBox::warning( this, QString::fromLocal8Bit("에러"), QString::fromLocal8Bit("손님을 선택해라잉!") );
        return;
    }

    int res = QMessageBox::warning( this, QString::fromLocal8Bit("위험"), QString::fromLocal8Bit("정말로 삭제할 거임? 신중하길 바람!"), QMessageBox::Ok | QMessageBox::Cancel );
    if( res == QMessageBox::Ok )
    {
        QString clientID = widgetItem->data(0, Qt::UserRole).toString();
        if( m_dbManager != nullptr )
            m_dbManager->DeleteClient( clientID );

        UpdateClient();
        ui->treeWidget_operation->clear();

        m_clientIDforUpdate = "-1";
    }
}

void ClientWidget::on_treeWidget_client_itemClicked(QTreeWidgetItem *item, int)
{
    qDebug() << __FUNCTION__;
    ui->treeWidget_operation->clear();

    QString clientID = item->data(0, Qt::UserRole).toString();
    m_clientIDforUpdate = clientID;

    if( m_dbManager != nullptr )
    {
        QStringList queryResult = m_dbManager->SelectOperationWithClientID( clientID );

        foreach( const QString& str, queryResult )
        {
            QStringList itemList = str.split('|');

            // time info
            QStringList dateTimeList = itemList[2].split(' ');
            QString dateStr = dateTimeList[0];
            QString timeStr = dateTimeList[1];


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

            // color
            QString colorId = itemList[5];
            QString colorQuery = m_dbManager->SelectSubTableWithId( TABLE_COLOR, colorId );

            //length
            QString lengthId = itemList[6];
            QString lengthQuery = m_dbManager->SelectSubTableWithId( TABLE_LENGTH, lengthId );


            //number
            QString numberId = itemList[7];
            QString numberQuery = m_dbManager->SelectSubTableWithId( TABLE_NUMBER, numberId );

            // price
            QString price = itemList[8];
            QString optionStr = itemList[9];

            int option = optionStr.toInt();

            bool bRetouch = option & 0x00000002;

            QTreeWidgetItem * item = new QTreeWidgetItem(ui->treeWidget_operation);

            item->setText(0, dateStr );
            item->setText(1, timeStr );
            item->setText(2, curlQuery.split('|')[1] );
            item->setText(3, typeQuery.split('|')[1] );
            item->setText(4, colorQuery.split('|')[1] );
            item->setText(5, lengthQuery.split('|')[1] );
            item->setText(6, numberQuery.split('|')[1] );
            item->setText(7, price );
            item->setText(8, bRetouch ? "O" : "X" );


            item->setData(0, Qt::UserRole, itemList[0] );
            ui->treeWidget_operation->addTopLevelItem( item );
        }
    }

}

void ClientWidget::RequestContextFromClient(const QPoint &pos)
{
    QTreeWidgetItem *item = ui->treeWidget_client->itemAt( pos );

    if( item != nullptr )
    {
        m_clientID = item->data( 0, Qt::UserRole ).toString();

        QAction *editAct = new QAction(QIcon(""), QString::fromLocal8Bit("손님 편집"), this);
        connect(editAct, SIGNAL(triggered()), this, SLOT( EditFromClient( ) ));

        QAction *deleteAct = new QAction(QIcon(""), QString::fromLocal8Bit("손님 삭제"), this);
        connect(deleteAct, SIGNAL(triggered()), this, SLOT( DeleteFromClient() ));


        QMenu menu(this);
        menu.addAction(editAct);
        menu.addAction(deleteAct);

        //QPoint pt(pos);
        menu.exec( ui->treeWidget_client->mapToGlobal(pos) );
    }
}

void ClientWidget::RequestContextFromOperation(const QPoint &pos)
{
    QTreeWidgetItem *item = ui->treeWidget_operation->itemAt( pos );

    if( item != nullptr )
    {
        m_operationID = item->data( 0, Qt::UserRole ).toString();

        QAction *editAct = new QAction(QIcon(""), QString::fromLocal8Bit("약속 편집"), this);
        connect(editAct, SIGNAL(triggered()), this, SLOT( EditFromOperation( ) ));

        QAction *deleteAct = new QAction(QIcon(""), QString::fromLocal8Bit("약속 삭제"), this);
        connect(deleteAct, SIGNAL(triggered()), this, SLOT( DeleteFromOperation() ));


        QMenu menu(this);
        menu.addAction(editAct);
        menu.addAction(deleteAct);

        //QPoint pt(pos);
        menu.exec( ui->treeWidget_operation->mapToGlobal(pos) );
    }
}

void ClientWidget::EditFromClient()
{
    ClientDialog diag;
    diag.SetDbManager( m_dbManager );
    diag.SetRole( ClientDialog::CLIENT_DIALOG_EDIT );
    diag.SetClientId( m_clientID.toInt() );
    diag.Init();
    if( QDialog::Accepted == diag.exec() )
    {
        UpdateClient();        
    }
}

void ClientWidget::DeleteFromClient()
{
    qDebug() << __FUNCTION__;
    int res = QMessageBox::warning( this, QString::fromLocal8Bit("위험"), QString::fromLocal8Bit("정말로 삭제할 거임? 신중하길 바람!"), QMessageBox::Ok | QMessageBox::Cancel );
    if( res == QMessageBox::Ok )
    {
        if( m_dbManager != nullptr )
            m_dbManager->DeleteClient( m_clientID );

        UpdateClient();
        m_clientIDforUpdate = "-1";
        ui->treeWidget_operation->clear();
    }

}

void ClientWidget::EditFromOperation()
{
    OperationDialog diag;
    diag.SetDbManager( m_dbManager );
    diag.SetRole( OperationDialog::OPERATION_DIALOG_EDIT );
    diag.SetOperationId( m_operationID );
    diag.Init();

    if( diag.exec() == QDialog::Accepted )
    {
        UpdateClient();
        UpdateOperation();
    }
}

void ClientWidget::DeleteFromOperation()
{
    int res = QMessageBox::warning( this, QString::fromLocal8Bit("위험"), QString::fromLocal8Bit("정말로 삭제할 거임? 신중하길 바람!"), QMessageBox::Ok | QMessageBox::Cancel );

    if( res == QMessageBox::Ok )
    {
        if( m_dbManager != nullptr )
        {
            m_dbManager->DeleteOperation( m_operationID );

            UpdateClient();
            UpdateOperation();
        }
    }
}
