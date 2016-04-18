#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

private slots:\
    void on_name_lineEdit_textChanged();
    void on_phoneNumber_lineEdit_textChanged();

    void on_name_pushButton_pressed();
    void on_phoneNumber_pushButton_pressed();

    void on_test(QTreeWidgetItem* );


private:
    void TestInit();

};

#endif // MAINWIDGET_H
