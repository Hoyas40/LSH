#ifndef EDITDBTABLEDIALOG_H
#define EDITDBTABLEDIALOG_H

#include <QDialog>


#include "dbmanager.h"

namespace Ui {
class EditDbTableDialog;
}

class EditDbTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDbTableDialog(QWidget *parent = 0);
    ~EditDbTableDialog();

    void SetDbManager( DBManager* _dbManager );

private:
    void UpdateView();



private slots:
    void on_radioButton_curl_clicked();

    void on_radioButton_type_clicked();

    void on_radioButton_color_clicked();

    void on_radioButton_length_clicked();

    void on_radioButton_number_clicked();

    void on_radioButton_contact_clicked();    

    void on_pushButton_add_clicked();

    void on_pushButton_delete_clicked();



    void on_pushButton_edit_clicked();

private:


    ENUM_DB_TABLES m_selectedTable;

    Ui::EditDbTableDialog *ui;

    DBManager * m_dbManager;


};

#endif // EDITDBTABLEDIALOG_H
