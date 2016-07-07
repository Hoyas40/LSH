#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Qdir>
#include "calendarWidget.h"

#include "dbmanager.h"
#include "editdbtabledialog.h"
#include "clientdialog.h"
#include "operationdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , m_calendarWidget( nullptr )
  , m_dbManager( nullptr )
{
    ui->setupUi(this);



    m_dbManager = new DBManager;



    //MainWindow::setWindowState(Qt::WindowMaximized);


    CreateActions();
    CreateMenus();
    CreateToolbars();



    setWindowTitle( "LSH Beauty" );

    // set config
    QDir dir;
    QString configFilename = dir.currentPath();
    configFilename += "/config.ini";

    QFileInfo configFileInfo( configFilename );
    if( configFileInfo.exists() )
        ReadConfigFile( configFilename );

    m_dbManager->Init();

    m_calendarWidget = new CalendarWidget( this, m_dbManager );
    m_calendarWidget->SetDbManager( m_dbManager );

    this->setWindowState( Qt::WindowMaximized );
    setCentralWidget( m_calendarWidget );

    connect( m_calendarWidget, SIGNAL(SignalAddOperation( const QDate&)), this, SLOT(SignalAddOperation(const QDate& )));

}

MainWindow::~MainWindow()
{
    if( m_dbManager != nullptr )
        delete m_dbManager;

    delete ui;
}

void MainWindow::ReadConfigFile(const QString &_filename)
{
    qDebug() << __FUNCTION__ << " | file : " << _filename;

    QFile file( _filename );
    if( file.open(QIODevice::ReadOnly | QIODevice::Text ))
    {
        QTextStream in( &file );
        while( !in.atEnd() )
        {
            QString line = in.readLine();

            line = line.trimmed();

            if( line[0] == '*' )
                continue;

            if( line.isEmpty() )
                continue;

            QStringList params;

            params = line.split( '=');
            if( params.count() != 2 )
                continue;

            for( int i = 0; i < params.size(); ++i )
                params[i] = params[i].trimmed();

            //<- set config data
            if( params[0] == QString("dbFilename") )
            {
                if( m_dbManager != nullptr )
                    m_dbManager->SetDbFilename( params[1] );
            }
        }
    }

    file.close();
}

void MainWindow::CreateActions()
{
    qDebug() << __FUNCTION__;


    m_saveCsvAction = new QAction( QString::fromLocal8Bit("CSV 저장하기"), this);
    m_saveCsvAction->setStatusTip( QString::fromLocal8Bit("데이터베이스를 CSV 파일로 저장하기"));
    connect( m_saveCsvAction, SIGNAL( triggered(bool)), this, SLOT( SaveCSV()) );

    m_loadCsvAction = new QAction( QString::fromLocal8Bit("CSV 불러오기"), this);
    m_loadCsvAction->setStatusTip( QString::fromLocal8Bit("CSV 파일 불러와서 데이터 베이스 덮어쓰기"));
    connect( m_loadCsvAction, SIGNAL( triggered(bool)), this, SLOT(LoadCSV()) );

    m_quitAction = new QAction( QString::fromLocal8Bit("종료"), this);
    m_quitAction->setStatusTip( QString::fromLocal8Bit("프로그램 종료하기"));
    connect( m_quitAction, SIGNAL( triggered(bool)), this, SLOT(close()) );


    m_addClientAction = new QAction(QString::fromLocal8Bit("손님 추가"), this);
    m_addClientAction->setStatusTip( QString::fromLocal8Bit("손님 추가하기"));
    connect( m_addClientAction, SIGNAL( triggered(bool)), this, SLOT(AddClient()) );

    m_addOperationAction = new QAction(QString::fromLocal8Bit("약속 추가"), this);
    m_addOperationAction->setStatusTip( QString::fromLocal8Bit("약속 추가하기"));
    connect( m_addOperationAction, SIGNAL( triggered(bool)), this, SLOT(AddOperation()) );

    m_editDbTablesAction = new QAction(QString::fromLocal8Bit("참조 DB 편집"), this);
    m_editDbTablesAction->setStatusTip( QString::fromLocal8Bit("참조되는 데이터베이스 편집하기"));
    connect( m_editDbTablesAction, SIGNAL( triggered(bool)), this, SLOT(EditDbTables()) );

}

void MainWindow::CreateMenus()
{
    qDebug() << __FUNCTION__;

    m_fileMenu = menuBar()->addMenu( QString::fromLocal8Bit("파일") );
    m_fileMenu->addAction( m_saveCsvAction );
    m_fileMenu->addAction( m_loadCsvAction );
    m_fileMenu->addAction( m_quitAction );

    m_editMenu = menuBar()->addMenu( QString::fromLocal8Bit("편집") );
    m_editMenu->addAction( m_addClientAction );
    m_editMenu->addAction( m_addOperationAction );
    m_editMenu->addAction( m_editDbTablesAction );
}

void MainWindow::CreateToolbars()
{
    qDebug() << __FUNCTION__;

}

void MainWindow::SaveCSV()
{
    qDebug() << __FUNCTION__;

}

void MainWindow::LoadCSV()
{
    qDebug() << __FUNCTION__;

}

void MainWindow::AddClient()
{
    qDebug() << __FUNCTION__;

    ClientDialog diag;


    diag.SetDbManager( m_dbManager );
    diag.SetRole( ClientDialog::CLIENT_DIALOG_NEW );
    diag.Init();

    if( diag.exec() == QDialog::Accepted )
    {
        qDebug() << "accepted";
    }
}

void MainWindow::AddOperation()
{
    qDebug() << __FUNCTION__;

    OperationDialog diag;
    diag.SetDbManager( m_dbManager );
    diag.SetRole( OperationDialog::OPERATION_DIALOG_NEW );
    diag.Init();

    if( diag.exec() == QDialog::Accepted )
    {
        //qDebug() << "accepted";
    }


}

void MainWindow::EditDbTables()
{
    qDebug() << __FUNCTION__;

    EditDbTableDialog diag;
    diag.SetDbManager( m_dbManager );

    diag.exec();
}

void MainWindow::SignalAddOperation(const QDate &_date)
{
    qDebug() << __FUNCTION__;

    OperationDialog diag;
    diag.SetDbManager( m_dbManager );
    diag.SetRole( OperationDialog::OPERATION_DIALOG_NEW );
    diag.Init();
    diag.SetDate( _date );

    if( diag.exec() == QDialog::Accepted )
    {
        // update calendar widget

        m_calendarWidget->UpdateCalendar();
        m_calendarWidget->UpdateSchedule();
    }


    qDebug() << _date;
}


