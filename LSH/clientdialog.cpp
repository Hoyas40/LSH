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
    setWindowTitle( QString::fromLocal8Bit("손님 추가") );
}

void ClientDialog::InitEdit()
{
    setWindowTitle( QString::fromLocal8Bit("손님 편집") );

    // DB 에서 데이터 읽어오기
}

void ClientDialog::LoadDB()
{
    qDebug() << __FUNCTION__;

    // 1. 속눈썹 길이
    if( m_dbManager != nullptr )
    {
        QStringList list;
        list = m_dbManager->SelectAllSubTable( TABLE_LENGTH );

        foreach( const QString& str, list )
        {
            QStringList split = str.split( ':' );

            if( 2 == split.count() )
                ui->comboBox_length->addItem( split[1], split[0] );
        }

        // 2. 속눈썹 숱
        list = m_dbManager->SelectAllSubTable( TABLE_NUMBER );

        foreach( const QString& str, list )
        {
            QStringList split = str.split( ':' );

            if( 2 == split.count() )
                ui->comboBox_number->addItem( split[1], split[0] );
        }
        // 3. 방문 경로
        list = m_dbManager->SelectAllSubTable( TABLE_CONTACT );

        foreach( const QString& str, list )
        {
            QStringList split = str.split( ':' );

            if( 2 == split.count() )
                ui->comboBox_contact->addItem( split[1], split[0] );
        }
    }
}


void ClientDialog::Init()
{
//    ui->lineEdit_name->setText( QString::fromLocal8Bit(" 가나다마 ") );
//    ui->lineEdit_name->setMinimumSize( ui->lineEdit_name->sizeHint() );
//    ui->lineEdit_name->clear();

    ui->lineEdit_phoneNumber->setText( "  000-0000-0000  ");
    ui->lineEdit_phoneNumber->setMinimumSize( ui->lineEdit_phoneNumber->sizeHint() );
    ui->lineEdit_phoneNumber->clear();



    ui->comboBox_length->addItem( " 10 mm ");
    ui->comboBox_length->setMinimumSize( ui->comboBox_length->sizeHint() );
    ui->comboBox_length->clear();

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
    QString hairLength = ui->comboBox_length->currentData().toString();
    QString hairNumber = ui->comboBox_number->currentData().toString();

    QString hairSag = ui->lineEdit_sag->text();
    QString hairDamage = ui->lineEdit_damage->text();

    qDebug() << contactWay << " : " << hairLength << " : " << hairNumber << " : " << hairSag << " : " << hairDamage;

    if( name.isEmpty() )
    {
        QMessageBox::warning( this, QString::fromLocal8Bit("에러"), QString::fromLocal8Bit("이름이 비어 있습니다") );
        return;
    }

    if ( phoneNumber.count() != 13 && phoneNumber.count() != 12 )
    {
        QMessageBox::warning( this, QString::fromLocal8Bit("에러"), QString::fromLocal8Bit("전화 번호가 비어 있습니다\n번호 7-8 개를 연속으로 입력하십시오") );
        return;
    }

    QStringList list = phoneNumber.split( '-' );
    if( list.size() != 3 )
    {
        QMessageBox::warning( this, QString::fromLocal8Bit("에러"), QString::fromLocal8Bit("전화 번호 포맷이 비정상입니다.\n정상 포맷 : 010-1234-5678") );
        return;
    }


    m_dbManager->InsertClient( name, phoneNumber, contactWay, hairLength, hairNumber, hairSag, hairDamage );


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
