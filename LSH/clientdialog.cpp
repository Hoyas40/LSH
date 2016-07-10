#include "clientdialog.h"
#include "ui_clientdialog.h"

#include <QDebug>
#include <QMessageBox>

ClientDialog::ClientDialog(QWidget *parent, CLIENT_ROLE role) :
    QDialog(parent),
    ui(new Ui::ClientDialog)
  , m_dbManager( nullptr )
  , m_role( role )
  , m_clientId( -1 )
{
    ui->setupUi(this);

    setFixedHeight( sizeHint().height() );

    connect( ui->lineEdit_phoneNumber, SIGNAL(textChanged(QString)), this, SLOT( on_lienEdit_Text_Changed( const QString & )) );
}

ClientDialog::~ClientDialog()
{
    delete ui;
}

void ClientDialog::SetDbManager(DBManager *_dbManager)
{
    m_dbManager = _dbManager;
}

void ClientDialog::InitNew()
{
    setWindowTitle( QString::fromLocal8Bit("�մ� �߰�") );
}

void ClientDialog::InitEdit()
{
    qDebug() << __FUNCTION__;
    setWindowTitle( QString::fromLocal8Bit("�մ� ����") );

    // DB ���� ������ �о����
    if( m_dbManager != nullptr )
    {
        QString queryWithID = m_dbManager->SelectClientWithId( QString::number(m_clientId ));
        QStringList list = queryWithID.split( '|' );
        QString clientName = list[1];
        QString phoneNumber = list[2];
        QString contactWay = list[3];
        QString info = list[4];

        ui->lineEdit_name->setText( clientName );
        ui->lineEdit_phoneNumber->setText( phoneNumber );
        int index = ui->comboBox_contact->findData( contactWay );
        ui->comboBox_contact->setCurrentIndex( index );
        ui->lineEdit_info->setText( info );
    }

}

void ClientDialog::LoadDB()
{
    qDebug() << __FUNCTION__;

    // 1. �Ӵ��� ����
    if( m_dbManager != nullptr )
    {
        QStringList list;

        // 3. contact way
        list = m_dbManager->SelectAllSubTable( TABLE_CONTACT );

        foreach( const QString& str, list )
        {
            QStringList split = str.split( '|' );

            if( 2 == split.count() )
                ui->comboBox_contact->addItem( split[1], split[0] );
        }
    }
}


void ClientDialog::Init()
{
    ui->lineEdit_phoneNumber->setText( "  000-0000-0000  ");
    ui->lineEdit_phoneNumber->setMinimumSize( ui->lineEdit_phoneNumber->sizeHint() );
    ui->lineEdit_phoneNumber->clear();

    LoadDB();

    if( m_role == CLIENT_DIALOG_NEW )
        InitNew();
    else
        InitEdit();
}

void ClientDialog::SetRole(ClientDialog::CLIENT_ROLE _role)
{
    m_role = _role;
}

void ClientDialog::SetClientId(const int _id)
{
    m_clientId = _id;
}

void ClientDialog::on_pushButton_OK_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString phoneNumber = ui->lineEdit_phoneNumber->text();
    QString contactWay = ui->comboBox_contact->currentData().toString();
    QString info = ui->lineEdit_info->text();

    if( name.isEmpty() )
    {
        QMessageBox::warning( this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�̸��� ��� �ֽ��ϴ�") );
        return;
    }

    if ( phoneNumber.count() != 13 && phoneNumber.count() != 12 )
    {
        QMessageBox::warning( this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȭ ��ȣ�� ��� �ֽ��ϴ�\n��ȣ 7-8 ���� �������� �Է��Ͻʽÿ�") );
        return;
    }

    QStringList list = phoneNumber.split( '-' );
    if( list.size() != 3 )
    {
        QMessageBox::warning( this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ȭ ��ȣ ������ �������Դϴ�.\n���� ���� : 010-1234-5678") );
        return;
    }



    if( m_role == CLIENT_DIALOG_NEW )
    {
        QStringList checkIfExsitList = m_dbManager->SelectClientWithPhoneNumber( phoneNumber );
        if( checkIfExsitList.size() != 0 )
        {
            QMessageBox::warning( this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�̹� �ִ� ��ȭ ��ȣ�Դϴ�.") );
            return;
        }

        m_dbManager->InsertClient( name, phoneNumber, contactWay, info );
    }
    else
    {
        m_dbManager->UpdateClient( QString::number(m_clientId), name, phoneNumber, contactWay, info );
    }


    accept();
}

void ClientDialog::on_pushButton_Cancel_clicked()
{
    reject();
}

void ClientDialog::on_lienEdit_Text_Changed(const QString &_str)
{
    QString res = _str;


    if( res.count() < 7 )
        return;

    if( res.count() > 13 )
        res = res.left(13);

    QStringList list = res.split( '-' );


    if( list.size() == 1 )
    {
        if( res.count() == 7 )
        {
            res.insert( 3, QChar('-') );
            res = "010-" + res;
        }
        else if( res.count() == 8 )
        {
            res.insert( 4, QChar('-') );
            res = "010-" + res;
        }
    }
    else if( list.size() == 2 )
    {

    }
    else if( list.size() == 3 )
    {
        if( res.count() == 13 )
        {
            if( list[0].count() == 3 && list[1].count() == 3 && list[2].count() == 5 )
            {
                list[1].push_back( list[2][0] );
                list[2] = list[2].mid(1);

                res = list[0] + "-" + list[1] + "-" + list[2];
            }
        }
    }
    else
        res = "";

    ui->lineEdit_phoneNumber->setText( res );
    return;
}
