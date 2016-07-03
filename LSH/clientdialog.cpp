#include "clientdialog.h"
#include "ui_clientdialog.h"

#include <QDebug>

ClientDialog::ClientDialog(QWidget *parent, CLIENT_ROLE role) :
    QDialog(parent),
    ui(new Ui::ClientDialog)
  , m_dbManager( nullptr )
  , m_role( role )
{
    ui->setupUi(this);

    setFixedHeight( sizeHint().height() );
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
    setWindowTitle( QString::fromLocal8Bit("¼Õ´Ô Ãß°¡") );
}

void ClientDialog::InitEdit()
{
    setWindowTitle( QString::fromLocal8Bit("¼Õ´Ô ÆíÁý") );
}

void ClientDialog::LoadDB()
{
    qDebug() << __FUNCTION__;

    // 1. ¼Ó´«½ç ±æÀÌ
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

        // 2. ¼Ó´«½ç ½¢
        list = m_dbManager->SelectAllSubTable( TABLE_NUMBER );

        foreach( const QString& str, list )
        {
            QStringList split = str.split( ':' );

            if( 2 == split.count() )
                ui->comboBox_number->addItem( split[1], split[0] );
        }
        // 3. ¹æ¹® °æ·Î
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
//    ui->lineEdit_name->setText( QString::fromLocal8Bit(" °¡³ª´Ù¸¶ ") );
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

void ClientDialog::on_pushButton_OK_clicked()
{
    int lengthIndex = ui->comboBox_length->currentIndex();

    QString lenghData = ui->comboBox_length->itemData( lengthIndex ).toString();

    qDebug() << lenghData;

    accept();
}

void ClientDialog::on_pushButton_Cancel_clicked()
{
    reject();
}
