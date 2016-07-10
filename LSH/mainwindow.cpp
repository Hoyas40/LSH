#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Qdir>
#include <QMessageBox>

#include "calendarWidget.h"

#include "dbmanager.h"
#include "editdbtabledialog.h"
#include "clientdialog.h"
#include "operationdialog.h"

#include "clientwidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , m_calendarWidget( nullptr )
  , m_clientWidget(nullptr )
  , m_dbManager( nullptr )
  , m_dataPath( "C:/" )
  , m_dbFilename( "db.db" )
  , m_clientCsvFilename( "client.csv")
  , m_operationCsvFilename( "operation.csv" )
  , m_curlCsvFilename( "curl.csv" )
  , m_typeCsvFilename( "type.csv" )
  , m_colorCsvFilename( "color.csv" )
  , m_lengthCsvFilename( "length.csv" )
  , m_numberCsvFilename( "number.csv" )
  , m_contactCsvFilename( "contact.csv" )
{
    ui->setupUi(this);

    CreateActions();
    CreateMenus();
    CreateToolbars();
    setWindowTitle( "LSH Beauty" );




    // db init
    m_dbManager = new DBManager;


    // set config
    QDir dir;
    QString configFilename = dir.currentPath();
    configFilename += "/config.ini";

    QFileInfo configFileInfo( configFilename );
    if( configFileInfo.exists() )
        ReadConfigFile( configFilename );

    m_dbManager->Init();

    // calendar widget
    m_calendarWidget = new CalendarWidget( this, m_dbManager );

    // client widget
    m_clientWidget = new ClientWidget( this, m_dbManager );

    m_centralWidget = new QStackedWidget( this );

    //setWindowState( Qt::WindowMaximized );

    this->showFullScreen();

    setCentralWidget( m_centralWidget );



    m_centralWidget->addWidget( m_calendarWidget );
    m_centralWidget->addWidget( m_clientWidget );

    connect( m_calendarWidget, SIGNAL(SignalAddOperation( const QDate&)), this, SLOT(SignalAddOperation(const QDate& )));
    connect( m_clientWidget, SIGNAL(SignalAddClient()), this, SLOT(AddClient()));



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
            if( params[0] == QString("databaseFilename") )
                m_dbFilename = params[1];

            if( params[0] == QString("dataPath") )
                m_dataPath = params[1];

            if( params[0] == QString( "clientFilename" ))
                m_clientCsvFilename = params[1];

            if( params[0] == QString( "operationFilename" ))
                m_operationCsvFilename = params[1];

            if( params[0] == QString( "curlFilename" ))
                m_curlCsvFilename = params[1];

            if( params[0] == QString( "typeFilename" ))
                m_typeCsvFilename = params[1];

            if( params[0] == QString( "colorFilename" ))
                m_colorCsvFilename = params[1];

            if( params[0] == QString( "lengthFilename" ))
                m_lengthCsvFilename = params[1];

            if( params[0] == QString( "numberFilename" ))
                m_numberCsvFilename = params[1];

            if( params[0] == QString( "contactFilename" ))
                m_contactCsvFilename = params[1];
        }

        m_dbFilename = m_dataPath + m_dbFilename;
        if( m_dbManager != nullptr )
            m_dbManager->SetDbFilename( m_dbFilename );
    }

    file.close();
}

void MainWindow::CreateActions()
{
    qDebug() << __FUNCTION__;


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

    m_calendarWidgetAction = new QAction( QString::fromLocal8Bit("달력 화면"));
    m_calendarWidgetAction->setStatusTip( QString::fromLocal8Bit("달력 화면으로 변경"));
    m_calendarWidgetAction->setIcon( QIcon(":/images/calendar_button.png"));
    connect( m_calendarWidgetAction, SIGNAL( triggered(bool)), this, SLOT(ChangeToCalendarWidget()));

    m_clientWidgetAction = new QAction( QString::fromLocal8Bit("손님 화면"));
    m_clientWidgetAction->setStatusTip( QString::fromLocal8Bit("손님 화면으로 변경"));
    m_clientWidgetAction->setIcon( QIcon(":/images/client_button.png"));
    connect( m_clientWidgetAction, SIGNAL( triggered(bool)), this, SLOT(ChangeToClientWidget()));


    m_viewActionGroup = new QActionGroup( this );
    m_viewActionGroup->addAction( m_calendarWidgetAction );
    m_viewActionGroup->addAction( m_clientWidgetAction );
    m_viewActionGroup->setExclusive( true );
    m_calendarWidgetAction->setCheckable( true );
    m_clientWidgetAction->setCheckable( true );
    m_calendarWidgetAction->setChecked( true );
}


void MainWindow::CreateMenus()
{
    qDebug() << __FUNCTION__;

    // file menu
    m_fileMenu = menuBar()->addMenu( QString::fromLocal8Bit("파일") );
    m_fileMenu->addAction( m_saveCsvAction );
    m_fileMenu->addAction( m_loadCsvAction );
    m_fileMenu->addSeparator();
    m_fileMenu->addAction( m_quitAction );    

    // edit menu
    m_editMenu = menuBar()->addMenu( QString::fromLocal8Bit("편집") );
    m_editMenu->addAction( m_addClientAction );
    m_editMenu->addAction( m_addOperationAction );
    m_editMenu->addAction( m_editDbTablesAction );    

    m_viewMenu = menuBar()->addMenu( QString::fromLocal8Bit("뷰"));
    m_viewMenu->addAction( m_calendarWidgetAction );
    m_viewMenu->addAction( m_clientWidgetAction );

    // help menu
    m_helpMenu = menuBar()->addMenu( QString::fromLocal8Bit("도움") );
    m_helpMenu->addAction( m_helpAction );

    // font setting
    menuBar()->setFont( QFont( QString::fromLocal8Bit("맑은 고딕"), 10 ) );
    m_editMenu->setFont(QFont( QString::fromLocal8Bit("맑은 고딕"), 10 ));
    m_fileMenu->setFont(QFont( QString::fromLocal8Bit("맑은 고딕"), 10 ));
    m_helpMenu->setFont(QFont( QString::fromLocal8Bit("맑은 고딕"), 10 ));
    m_viewMenu->setFont(QFont( QString::fromLocal8Bit("맑은 고딕"), 10 ));
}

void MainWindow::CreateToolbars()
{
    qDebug() << __FUNCTION__;

    int iconSize = 36;
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


    m_viewToolBar = addToolBar( "View" );
    m_viewToolBar->addAction( m_calendarWidgetAction );
    m_viewToolBar->addAction( m_clientWidgetAction );
    m_viewToolBar->setMinimumHeight( 70 );
    m_viewToolBar->setIconSize( QSize( iconSize, iconSize));

}

void MainWindow::WriteCsvFile(const QStringList &_queryList, const QString &_filename)
{
    QFile file( _filename );

    if( !file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        QMessageBox::warning( this, QString::fromLocal8Bit("저장 에러"),
                              QString::fromLocal8Bit("파일 저장 에러 %1:\n%2.")
                              .arg( file.fileName() )
                              .arg( file.errorString() ));
        return;
    }

    QTextStream out( &file );

    foreach ( const QString& str, _queryList )
    {
        QStringList tmpList = str.split('|');

        int nCols = tmpList.size();
        for( int i = 0; i < nCols -1; ++i)
            out << tmpList[i] << ",";

        out << tmpList[nCols-1] <<"\n";
    }
}

QStringList MainWindow::ReadCsvFile(const QString &_filename)
{
    QStringList res;

    QFile file( _filename );

    if( !file.open( QIODevice::ReadOnly | QIODevice::Text) )
    {
        QMessageBox::warning( this, QString::fromLocal8Bit("저장 에러"),
                              QString::fromLocal8Bit("파일 저장 에러 %1:\n%2.")
                              .arg( file.fileName() )
                              .arg( file.errorString() ));
        return QStringList();
    }

    QTextStream in( &file );

    while( !in.atEnd() )
    {
        QString line = in.readLine();
        if( !line.isEmpty() )
            res << line;
    }

    return res;
}

void MainWindow::SaveCSV()
{
    qDebug() << __FUNCTION__;

    // client table
    if( m_dbManager != nullptr )
    {
        QStringList queryResult;
        QString filename;
        queryResult = m_dbManager->SelectClientAll();
        filename = m_dataPath + m_clientCsvFilename;
        WriteCsvFile( queryResult, filename );

        // operation table
        queryResult = m_dbManager->SelectOperationAll();
        filename = m_dataPath + m_operationCsvFilename;
        WriteCsvFile( queryResult, filename );

        // curl
        queryResult = m_dbManager->SelectAllSubTable( TABLE_CURL );
        filename = m_dataPath + m_curlCsvFilename;
        WriteCsvFile( queryResult, filename );

        // type
        queryResult = m_dbManager->SelectAllSubTable( TABLE_TYPE );
        filename = m_dataPath + m_typeCsvFilename;
        WriteCsvFile( queryResult, filename );

        // color
        queryResult = m_dbManager->SelectAllSubTable( TABLE_COLOR );
        filename = m_dataPath + m_colorCsvFilename;
        WriteCsvFile( queryResult, filename );

        // length
        queryResult = m_dbManager->SelectAllSubTable( TABLE_LENGTH );
        filename = m_dataPath + m_lengthCsvFilename;
        WriteCsvFile( queryResult, filename );

        // number
        queryResult = m_dbManager->SelectAllSubTable( TABLE_NUMBER );
        filename = m_dataPath + m_numberCsvFilename;
        WriteCsvFile( queryResult, filename );

        // contact way
        queryResult = m_dbManager->SelectAllSubTable( TABLE_CONTACT );
        filename = m_dataPath + m_contactCsvFilename;
        WriteCsvFile( queryResult, filename );
    }
}

void MainWindow::LoadCSV()
{
    qDebug() << __FUNCTION__;

    int res = QMessageBox::warning( this, QString::fromLocal8Bit("위험"), QString::fromLocal8Bit("CSV 파일로부터 데이터베이스를 초기화할꺼임?\n"
                                                                                                "데이터베이스 초기화는 되돌릴 수 없는 위험성이 있음.\n"
                                                                                                "데이터베이스 파일을 백업한 후 진행하길..부디..."),
                                    QMessageBox::Ok | QMessageBox::Cancel );

    if( res == QMessageBox::Ok )
    {
        QApplication::setOverrideCursor( Qt::WaitCursor );
        if( m_dbManager != nullptr )
            m_dbManager->DeleteAllTable();


        QStringList csvReadResult;
        QString filename;

        // client
        filename = m_dataPath + m_clientCsvFilename;
        csvReadResult = ReadCsvFile( filename );
        foreach( const QString& str, csvReadResult )
        {
            QStringList tmpList = str.split( ',' );
            if( m_dbManager != nullptr )
                m_dbManager->InsertClient( tmpList[0],
                                           tmpList[1],
                                           tmpList[2],
                                           tmpList[3],
                                           tmpList[4] );
        }


        // operation
        filename = m_dataPath + m_operationCsvFilename;
        csvReadResult = ReadCsvFile( filename );
        foreach( const QString& str, csvReadResult )
        {
            QStringList tmpList = str.split( ',' );
            if( m_dbManager != nullptr )
                m_dbManager->InsertOperation( tmpList[0], tmpList[1],tmpList[2],tmpList[3],tmpList[4], tmpList[5], tmpList[6], tmpList[7], tmpList[8], tmpList[9] );
        }


        // curl
        filename = m_dataPath + m_curlCsvFilename;
        csvReadResult = ReadCsvFile( filename );

        foreach( const QString& str, csvReadResult )
        {
            QStringList tmpList = str.split( ',' );
            if( m_dbManager != nullptr )
                m_dbManager->InsertSubTable( TABLE_CURL, tmpList[0], tmpList[1] );
        }

        // type
        filename = m_dataPath + m_typeCsvFilename;
        csvReadResult = ReadCsvFile( filename );

        foreach( const QString& str, csvReadResult )
        {
            QStringList tmpList = str.split( ',' );
            if( m_dbManager != nullptr )
                m_dbManager->InsertSubTable( TABLE_TYPE, tmpList[0], tmpList[1] );
        }

        // color
        filename = m_dataPath + m_colorCsvFilename;
        csvReadResult = ReadCsvFile( filename );

        foreach( const QString& str, csvReadResult )
        {
            QStringList tmpList = str.split( ',' );
            if( m_dbManager != nullptr )
                m_dbManager->InsertSubTable( TABLE_COLOR, tmpList[0], tmpList[1] );
        }

        // length
        filename = m_dataPath + m_lengthCsvFilename;
        csvReadResult = ReadCsvFile( filename );

        foreach( const QString& str, csvReadResult )
        {
            QStringList tmpList = str.split( ',' );
            if( m_dbManager != nullptr )
                m_dbManager->InsertSubTable( TABLE_LENGTH, tmpList[0], tmpList[1] );
        }

        // number
        filename = m_dataPath + m_numberCsvFilename;
        csvReadResult = ReadCsvFile( filename );

        foreach( const QString& str, csvReadResult )
        {
            QStringList tmpList = str.split( ',' );
            if( m_dbManager != nullptr )
                m_dbManager->InsertSubTable( TABLE_NUMBER, tmpList[0], tmpList[1] );
        }

        // contact way
        filename = m_dataPath + m_contactCsvFilename;
        csvReadResult = ReadCsvFile( filename );

        foreach( const QString& str, csvReadResult )
        {
            QStringList tmpList = str.split( ',' );
            if( m_dbManager != nullptr )
                m_dbManager->InsertSubTable( TABLE_CONTACT, tmpList[0], tmpList[1] );
        }

        m_clientWidget->UpdateClient();
        m_clientWidget->UpdateOperation();

        m_calendarWidget->UpdateCalendar();
        m_calendarWidget->UpdateSchedule();

        QApplication::restoreOverrideCursor();
    }
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
        m_clientWidget->UpdateClient();
    }
}

void MainWindow::AddOperation()
{
    OperationDialog diag;
    diag.SetDbManager( m_dbManager );
    diag.SetRole( OperationDialog::OPERATION_DIALOG_NEW );
    diag.Init();

    if( diag.exec() == QDialog::Accepted )
    {
        m_clientWidget->UpdateOperation();
    }


}

void MainWindow::EditDbTables()
{
    qDebug() << __FUNCTION__;

    EditDbTableDialog diag;
    diag.setWindowTitle( QString::fromLocal8Bit("참조 DB 편집"));
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
}

void MainWindow::About()
{
    QMessageBox::about( this, QString::fromLocal8Bit("LSH 프로그램 소개"),
                        QString::fromLocal8Bit("세상에서 제일 멋진 오빠가\n"
                                               "사랑하는 동생 선호의 사업 번창을 위해 만듦\n"
                                               "2016년 7월"));
}

void MainWindow::ChangeToCalendarWidget()
{
    qDebug() << __FUNCTION__;

    m_centralWidget->setCurrentWidget( m_calendarWidget );
    m_calendarWidget->UpdateCalendar();
    m_calendarWidget->UpdateSchedule();

}

void MainWindow::ChangeToClientWidget()
{
    qDebug() << __FUNCTION__;

    m_centralWidget->setCurrentWidget( m_clientWidget );
    m_clientWidget->UpdateClient();
    m_clientWidget->UpdateOperation();
}


