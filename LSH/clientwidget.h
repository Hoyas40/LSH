#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
class ClientWidget;
}

class DBManager;

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = 0, DBManager* _dbManager = nullptr );
    ~ClientWidget();

    void UpdateClient();

    void UpdateOperation();

private:


private slots:


    void on_lineEdit_phoneNumber_textChanged(const QString &arg1);

    void on_lineEdit_name_textChanged(const QString &arg1);

    void on_pushButton_name_clicked();

    void on_pushButton_phoneNumber_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_delete_clicked();

    void on_treeWidget_client_itemClicked(QTreeWidgetItem *item, int column);

    void RequestContextFromClient( const QPoint & pos );

    void RequestContextFromOperation( const QPoint & pos );

    void EditFromClient();

    void DeleteFromClient();

    void EditFromOperation();

    void DeleteFromOperation();

private:
    Ui::ClientWidget *ui;
    DBManager* m_dbManager;

    QString m_clientID;
    QString m_operationID;

    QString m_clientIDforUpdate;

signals:
    void SignalAddClient();
};

#endif // CLIENTWIDGET_H
