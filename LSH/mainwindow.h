#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>

#include <QStackedWidget>

class DBManager;
class CalendarWidget;
class ClientWidget;

namespace Ui {
class MainWindow;
}



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

    void WriteCsvFile( const QStringList & _queryList, const QString & _filename );

    QStringList ReadCsvFile( const QString & _filename );

private slots:
    void SaveCSV();
    void LoadCSV();

    void AddClient();
    void AddOperation();
    void EditDbTables();
    void SignalAddOperation( const QDate& _date);
    void About();

    void ChangeToCalendarWidget();

    void ChangeToClientWidget();


private:
    Ui::MainWindow *ui;

    DBManager * m_dbManager;

    QString m_dataPath;
    QString m_dbFilename;
    QString m_clientCsvFilename;
    QString m_operationCsvFilename;
    QString m_curlCsvFilename;
    QString m_typeCsvFilename;
    QString m_colorCsvFilename;
    QString m_lengthCsvFilename;
    QString m_numberCsvFilename;
    QString m_contactCsvFilename;

    CalendarWidget * m_calendarWidget;
    ClientWidget * m_clientWidget;

    QAction * m_saveCsvAction;
    QAction * m_loadCsvAction;
    QAction * m_quitAction;

    QAction * m_addClientAction;
    QAction * m_addOperationAction;
    QAction * m_editDbTablesAction;
    QAction * m_helpAction;

    QAction * m_calendarWidgetAction;
    QAction * m_clientWidgetAction;

    QActionGroup * m_viewActionGroup;

    QMenu * m_fileMenu;
    QMenu * m_editMenu;
    QMenu * m_helpMenu;
    QMenu * m_viewMenu;

    QToolBar * m_fileToolBar;
    QToolBar * m_editToolBar;
    QToolBar * m_viewToolBar;

    QStackedWidget * m_centralWidget;
};

#endif // MAINWINDOW_H
