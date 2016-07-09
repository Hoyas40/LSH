#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Qdir>
#include <QMessageBox>

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


    QIcon icon = QIcon(":/images/save.png");

    m_saveCsvAction = new QAction( QString::fromLocal8Bit("CSV 저장하기"), this);
    m_saveCsvAction->setStatusTip( QString::fromLocal8Bit("데이터베이스를 CSV 파일로 저장하기"));
    m_saveCsvAction->setIcon( QIcon(":/images/save.png") );

    connect( m_saveCsvAction, SIGNAL( triggered(bool)), this, SLOT( SaveCSV()) );

    m_loadCsvAction = new QAction( QString::fromLocal8Bit("CSV 불러오기"), this);
    m_loadCsvAction->setStatusTip( QString::fromLocal8Bit("CSV 파일 불러와서 데이터 베이스 덮어쓰기"));
    m_loadCsvAction->setIcon( QIcon(":/images/load.png"));
    connect( m_loadCsvAction, SIGNAL( triggered(bool)), this, SLOT(LoadCSV()) );

    m_quitAction = new QAction( QString::fromLocal8Bit("종료"), this);
    m_quitAction->setStatusTip( QString::fromLocal8Bit("프로그램 종료하기"));
    connect( m_quitAction, SIGNAL( triggered(bool)), this, SLOT(close()) );


    m_addClientAction = new QAction(QString::fromLocal8Bit("손님 추가"), this);
    m_addClientAction->setStatusTip( QString::fromLocal8Bit("손님 추가하기"));
    m_addClientAction->setIcon( QIcon(":/images/add_client.png"));
    connect( m_addClientAction, SIGNAL( triggered(bool)), this, SLOT(AddClient()) );

    m_addOperationAction = new QAction(QString::fromLocal8Bit("약속 추가"), this);
    m_addOperationAction->setStatusTip( QString::fromLocal8Bit("약속 추가하기"));
    m_addOperationAction->setIcon( QIcon(":/images/add_operation.png"));
    connect( m_addOperationAction, SIGNAL( triggered(bool)), this, SLOT(AddOperation()) );

    m_editDbTablesAction = new QAction(QString::fromLocal8Bit("참조 DB 편집"), this);
    m_editDbTablesAction->setStatusTip( QString::fromLocal8Bit("참조되는 데이터베이스 편집하기"));
    m_editDbTablesAction->setIcon( QIcon(":/images/editDb.png"));
    connect( m_editDbTablesAction, SIGNAL( triggered(bool)), this, SLOT(EditDbTables()) );

    m_helpAction = new QAction( QString::fromLocal8Bit("About LSH"));
    m_helpAction->setStatusTip( QString::fromLocal8Bit("LSH 프로그램 소개"));
    connect( m_helpAction, SIGNAL( triggered(bool)), this, SLOT(About()));


}

void MainWindow::CreateMenus()
{
    qDebug() << __FUNCTION__;

    // file menu
    m_fileMenu = menuBar()->addMenu( QString::fromLocal8Bit("파일") );
    m_fileMenu->addAction( m_saveCsvAction );
    m_fileMenu->addAction( m_loadCsvAction );
    m_fileMenu->addAction( m_quitAction );    

    // edit menu
    m_editMenu = menuBar()->addMenu( QString::fromLocal8Bit("편집") );
    m_editMenu->addAction( m_addClientAction );
    m_editMenu->addAction( m_addOperationAction );
    m_editMenu->addAction( m_editDbTablesAction );    

    // help menu
    m_helpMenu = menuBar()->addMenu( QString::fromLocal8Bit("도움") );
    m_helpMenu->addAction( m_helpAction );

    // font setting
    menuBar()->setFont( QFont( QString::fromLocal8Bit("맑은 고딕"), 12 ) );
    m_editMenu->setFont(QFont( QString::fromLocal8Bit("맑은 고딕"), 12 ));
    m_fileMenu->setFont(QFont( QString::fromLocal8Bit("맑은 고딕"), 12 ));
    m_helpMenu->setFont(QFont( QString::fromLocal8Bit("맑은 고딕"), 12 ));
}

void MainWindow::CreateToolbars()
{
    qDebug() << __FUNCTION__;

    int iconSize = 48;
    ui->mainToolBar->hide();
    m_fileToolBar = addToolBar( "File" );
    m_fileToolBar->addAction( m_saveCsvAction );
    m_fileToolBar->addAction( m_loadCsvAction );
    m_fileToolBar->setMinimumHeight( 70 );
    m_fileToolBar->setIconSize( QSize( iconSize, iconSize));

    m_editToolBar = addToolBar( "Edit" );
    m_editToolBar->addAction( m_addClientAction );
    m_editToolBar->addAction( m_addOperationAction );
    m_editToolBar->addAction( m_editDbTablesAction );
    m_editToolBar->setMinimumHeight( 70 );
    m_editToolBar->setIconSize( QSize( iconSize, iconSize));

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

void MainWindow::About()
{
    QMessageBox::about( this, QString::fromLocal8Bit("LSH 프로그램 소개"),
                        QString::fromLocal8Bit("세상에서 제일 멋진 오빠가\n"
                                               "사랑하는 동생 선호의 사업 번창을 위해 만듦\n"
                                               "2016년 7월"));
}


