#include "editdbtabledialog.h"
#include "ui_editdbtabledialog.h"
#include "insertsubtabledialog.h"

#include <QDebug>


EditDbTableDialog::EditDbTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDbTableDialog)
  , m_dbManager( nullptr )
  , m_selectedTable( TABLE_NONE )
{
    ui->setupUi(this);

    ui->treeWidget->setColumnCount( 2 );
    ui->treeWidget->setHeaderLabels( QStringList() << "ID" << "Name");
}

EditDbTableDialog::~EditDbTableDialog()
{
    delete ui;
}

void EditDbTableDialog::SetDbManager(DBManager *_dbManager)
{
    m_dbManager = _dbManager;
}

void EditDbTableDialog::on_radioButton_curl_clicked()
{
    qDebug() << __FUNCTION__;

    m_selectedTable = TABLE_CURL;

    UpdateView();
}

void EditDbTableDialog::on_radioButton_type_clicked()
{
    qDebug() << __FUNCTION__;

    m_selectedTable = TABLE_TYPE;

    UpdateView();
}

void EditDbTableDialog::on_radioButton_color_clicked()
{
    qDebug() << __FUNCTION__;

    m_selectedTable = TABLE_COLOR;

    UpdateView();
}

void EditDbTableDialog::on_radioButton_length_clicked()
{
    qDebug() << __FUNCTION__;

    m_selectedTable = TABLE_LENGTH;

    UpdateView();
}

void EditDbTableDialog::on_radioButton_number_clicked()
{
    qDebug() << __FUNCTION__;

    m_selectedTable = TABLE_NUMBER;

    UpdateView();
}

void EditDbTableDialog::on_radioButton_contact_clicked()
{
    qDebug() << __FUNCTION__;

    m_selectedTable = TABLE_CONTACT;

    UpdateView();
}


void EditDbTableDialog::UpdateView()
{
    ui->treeWidget->clear();

    if( m_dbManager != nullptr )
    {
        QStringList tableList = m_dbManager->SelectAllSubTable( m_selectedTable );

        foreach( const QString & str, tableList )
        {
            QStringList split = str.split(':');

            if( split.size() == 2 )
            {
                QTreeWidgetItem * item = new QTreeWidgetItem( ui->treeWidget );
                item->setText(0, split[0] );
                item->setText(1, split[1] );

                //item->setTextAlignment(0, Qt::AlignCenter);
                //item->setTextAlignment(1, Qt::AlignCenter);

                ui->treeWidget->addTopLevelItem( item );
            }
        }


    }

    qDebug() << __FUNCTION__;
}

void EditDbTableDialog::on_pushButton_add_clicked()
{
    qDebug() << __FUNCTION__;

    if( m_selectedTable == TABLE_NONE )
    {
        // show warning message
        return;
    }

    int id = -1;
    if( m_dbManager != nullptr )
    {
        QStringList tableList = m_dbManager->SelectAllSubTable( m_selectedTable );
        foreach( const QString & str, tableList )
        {
            QStringList split = str.split(':');

            if( split.size() == 2 )
            {
                int tmpId = split[0].mid(2).toInt();
                id = std::max( id, tmpId );
            }
        }

        id++;

        QString idStr = DBManager::GetTagName( m_selectedTable ) + QString::number( id );

        InsertSubTableDialog diag;
        diag.SetId( idStr );
        if( diag.exec() == QDialog::Accepted )
        {
            QString nameStr = diag.GetName();

            m_dbManager->InsertSubTable( m_selectedTable, idStr, nameStr );
        }

        UpdateView();
    }

}

void EditDbTableDialog::on_pushButton_delete_clicked()
{
    qDebug() << __FUNCTION__;

    if( m_selectedTable == TABLE_NONE )
    {
        // show warning message
        return;
    }


    // Important
    // warning message to indicate that deleting an item
    // is CRITICAL

    QTreeWidgetItem * item = ui->treeWidget->currentItem();
    if( item != nullptr )
    {
        qDebug() << ui->treeWidget->currentItem()->text( 0 );
        QString id = item->text( 0 );

        if( false == id.isEmpty() )
            m_dbManager->DeleteSubTable( m_selectedTable, id );
    }
    UpdateView();



}

void EditDbTableDialog::on_pushButton_edit_clicked()
{
    qDebug() << __FUNCTION__;

    if( m_selectedTable == TABLE_NONE )
    {
        // show warning message
        return;
    }


    // Important
    // warning message to indicate that deleting an item
    // is CRITICAL

    QTreeWidgetItem * item = ui->treeWidget->currentItem();
    if( item != nullptr )
    {
        qDebug() << ui->treeWidget->currentItem()->text( 0 );
        QString idStr = item->text( 0 );

        if( false == idStr.isEmpty() )
        {
            InsertSubTableDialog diag;
            diag.SetId( idStr );

            if( diag.exec() == QDialog::Accepted )
            {
                QString nameStr = diag.GetName();

                m_dbManager->UpdateSubTable( m_selectedTable, idStr, nameStr );
            }

        }
    }
    UpdateView();
}
