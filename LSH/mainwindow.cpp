#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calendarWidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , m_calendarWidget( nullptr )
{
    ui->setupUi(this);

    m_calendarWidget = new CalendarWidget;

    setCentralWidget( m_calendarWidget );
}

MainWindow::~MainWindow()
{
    delete ui;
}
