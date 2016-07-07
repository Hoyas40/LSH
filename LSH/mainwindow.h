#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class DBManager;

namespace Ui {
class MainWindow;
}

class CalendarWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void ReadConfigFile( const QString& _filename );

    void CreateActions();
    void CreateMenus();
    void CreateToolbars();

private slots:
    void SaveCSV();
    void LoadCSV();

    void AddClient();
    void AddOperation();
    void EditDbTables();
    void SignalAddOperation( const QDate& _date);


private:
    Ui::MainWindow *ui;

    DBManager * m_dbManager;

    CalendarWidget * m_calendarWidget;

    QAction * m_saveCsvAction;
    QAction * m_loadCsvAction;
    QAction * m_quitAction;

    QAction * m_addClientAction;
    QAction * m_addOperationAction;
    QAction * m_editDbTablesAction;

    QMenu * m_fileMenu;
    QMenu * m_editMenu;
};

#endif // MAINWINDOW_H
