#ifndef OPERATIONDIALOG_H
#define OPERATIONDIALOG_H

#include <QDialog>

#include "dbmanager.h"


namespace Ui {
class OperationDialog;
}

class OperationDialog : public QDialog
{
    Q_OBJECT

public :
    enum OPERATION_ROLE{ OPERATION_DIALOG_NEW, OPERATION_DIALOG_EDIT };

public:
    explicit OperationDialog(QWidget *parent = 0);
    ~OperationDialog();

    void SetDbManager( DBManager * _dbManager );

    void SetRole( OPERATION_ROLE _role );

    void Init();

private slots:
    void on_pushButton_name_clicked();

    void on_pushButton_phoneNumber_clicked();

    void on_lineEdit_name_textChanged(const QString &arg1);

    void on_lineEdit_phoneNumber_textEdited(const QString &arg1);


    void on_lineEdit_name_returnPressed();

    void on_lineEdit_phoneNumber_returnPressed();

    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

private:
    void Init_New();
    void Init_Edit();
    void LoadDB();



private:
    Ui::OperationDialog *ui;

    DBManager* m_dbManager;
    OPERATION_ROLE m_role;
};

#endif // OPERATIONDIALOG_H
