#ifndef CLIENTDIALOG_H
#define CLIENTDIALOG_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui {
class ClientDialog;
}

class ClientDialog : public QDialog
{
    Q_OBJECT

public:
    enum CLIENT_ROLE{ CLIENT_DIALOG_NEW, CLIENT_DIALOG_EDIT };

    explicit ClientDialog(QWidget *parent = 0, CLIENT_ROLE role = CLIENT_DIALOG_NEW );
    ~ClientDialog();

    void SetDbManager( DBManager* _dbManager );

    void Init();

    void SetRole( CLIENT_ROLE _role );

    void SetClientId( const int _id );

private slots:
    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

    void on_lienEdit_Text_Changed( const QString & _str );

private:
    void InitNew();

    void InitEdit();

    void LoadDB();


private:
    Ui::ClientDialog *ui;

    DBManager * m_dbManager;

    CLIENT_ROLE m_role;

    int m_clientId;

};

#endif // CLIENTDIALOG_H
