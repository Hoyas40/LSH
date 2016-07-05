#include "calendarWidget.h"
#include "ui_calendarWidget.h"
#include <QDebug>
#include <QDate>

#include "my_qlabel.h"



CalendarWidget::CalendarWidget(QWidget *parent,DBManager* _dbManager) :
    QWidget(parent),
    ui(new Ui::Widget)
  , m_dbManager( _dbManager )
{
    ui->setupUi(this);

    // Initilize variables
    m_calendarDayOffset = 0;

    // Connections
    connect( ui->pushbutton_calendar_prev_month, SIGNAL(clicked(bool)), this, SLOT(onCalendarPrevMonthButtonPressed()) );
    connect( ui->pushbutton_calendar_prev_year, SIGNAL(clicked(bool)), this, SLOT(onCalendarPrevYearButtonPressed()) );
    connect( ui->pushbutton_calendar_next_month, SIGNAL(clicked(bool)), this, SLOT(onCalendarNextMonthButtonPressed()));
    connect( ui->pushbutton_calendar_next_year, SIGNAL(clicked(bool)), this, SLOT(onCalendarNextYearButtonPressed()) );

    connect( ui->pushButton_new, SIGNAL(clicked(bool)), this, SLOT(onReturnToCurrentMonth()));

    // Initialize
    Initialize();





}

CalendarWidget::~CalendarWidget()
{
    delete ui;
}

void CalendarWidget::SetDbManager(DBManager *_dbManager)
{
    m_dbManager = _dbManager;
}



void CalendarWidget::onCalendarPrevMonthButtonPressed()
{
    m_calendarDate = m_calendarDate.addMonths( -1 );

    UpdateCalendar();
}



void CalendarWidget::onCalendarNextMonthButtonPressed()
{
    m_calendarDate = m_calendarDate.addMonths( 1 );

    UpdateCalendar();
}



void CalendarWidget::onCalendarPrevYearButtonPressed()
{
    m_calendarDate = m_calendarDate.addYears( -1 );

    UpdateCalendar();
}



void CalendarWidget::onCalendarNextYearButtonPressed()
{
    m_calendarDate = m_calendarDate.addYears( 1 );

    UpdateCalendar();
}



void CalendarWidget::Initialize()
{
    // assign ui control to variables
    m_calendarBody[0] = ui->label_body_00;    m_calendarBody[1] = ui->label_body_01;    m_calendarBody[2] = ui->label_body_02;    m_calendarBody[3] = ui->label_body_03;    m_calendarBody[4] = ui->label_body_04;    m_calendarBody[5] = ui->label_body_05;    m_calendarBody[6] = ui->label_body_06;
    m_calendarBody[7] = ui->label_body_07;    m_calendarBody[8] = ui->label_body_08;    m_calendarBody[9] = ui->label_body_09;    m_calendarBody[10] = ui->label_body_10;    m_calendarBody[11] = ui->label_body_11;    m_calendarBody[12] = ui->label_body_12;    m_calendarBody[13] = ui->label_body_13;
    m_calendarBody[14] = ui->label_body_14;    m_calendarBody[15] = ui->label_body_15;    m_calendarBody[16] = ui->label_body_16;    m_calendarBody[17] = ui->label_body_17;    m_calendarBody[18] = ui->label_body_18;    m_calendarBody[19] = ui->label_body_19;    m_calendarBody[20] = ui->label_body_20;
    m_calendarBody[21] = ui->label_body_21;    m_calendarBody[22] = ui->label_body_22;    m_calendarBody[23] = ui->label_body_23;    m_calendarBody[24] = ui->label_body_24;    m_calendarBody[25] = ui->label_body_25;    m_calendarBody[26] = ui->label_body_26;    m_calendarBody[27] = ui->label_body_27;
    m_calendarBody[28] = ui->label_body_28;    m_calendarBody[29] = ui->label_body_29;    m_calendarBody[30] = ui->label_body_30;    m_calendarBody[31] = ui->label_body_31;    m_calendarBody[32] = ui->label_body_32;    m_calendarBody[33] = ui->label_body_33;    m_calendarBody[34] = ui->label_body_34;
    m_calendarBody[35] = ui->label_body_35;    m_calendarBody[36] = ui->label_body_36;    m_calendarBody[37] = ui->label_body_37;    m_calendarBody[38] = ui->label_body_38;    m_calendarBody[39] = ui->label_body_39;    m_calendarBody[40] = ui->label_body_40;    m_calendarBody[41] = ui->label_body_41;

    m_calendarTitle[0] = ui->label_title_00;    m_calendarTitle[1] = ui->label_title_01;    m_calendarTitle[2] = ui->label_title_02;    m_calendarTitle[3] = ui->label_title_03;    m_calendarTitle[4] = ui->label_title_04;    m_calendarTitle[5] = ui->label_title_05;    m_calendarTitle[6] = ui->label_title_06;
    m_calendarTitle[7] = ui->label_title_07;    m_calendarTitle[8] = ui->label_title_08;    m_calendarTitle[9] = ui->label_title_09;    m_calendarTitle[10] = ui->label_title_10;    m_calendarTitle[11] = ui->label_title_11;    m_calendarTitle[12] = ui->label_title_12;    m_calendarTitle[13] = ui->label_title_13;
    m_calendarTitle[14] = ui->label_title_14;    m_calendarTitle[15] = ui->label_title_15;    m_calendarTitle[16] = ui->label_title_16;    m_calendarTitle[17] = ui->label_title_17;    m_calendarTitle[18] = ui->label_title_18;    m_calendarTitle[19] = ui->label_title_19;    m_calendarTitle[20] = ui->label_title_20;
    m_calendarTitle[21] = ui->label_title_21;    m_calendarTitle[22] = ui->label_title_22;    m_calendarTitle[23] = ui->label_title_23;    m_calendarTitle[24] = ui->label_title_24;    m_calendarTitle[25] = ui->label_title_25;    m_calendarTitle[26] = ui->label_title_26;    m_calendarTitle[27] = ui->label_title_27;
    m_calendarTitle[28] = ui->label_title_28;    m_calendarTitle[29] = ui->label_title_29;    m_calendarTitle[30] = ui->label_title_30;    m_calendarTitle[31] = ui->label_title_31;    m_calendarTitle[32] = ui->label_title_32;    m_calendarTitle[33] = ui->label_title_33;    m_calendarTitle[34] = ui->label_title_34;
    m_calendarTitle[35] = ui->label_title_35;    m_calendarTitle[36] = ui->label_title_36;    m_calendarTitle[37] = ui->label_title_37;    m_calendarTitle[38] = ui->label_title_38;    m_calendarTitle[39] = ui->label_title_39;    m_calendarTitle[40] = ui->label_title_40;    m_calendarTitle[41] = ui->label_title_41;

    // caculate current date
    m_calendarToday = QDate::currentDate();

    // calendar date = 1st day of the current date
    m_calendarDate  = QDate( m_calendarToday.year(), m_calendarToday.month(), 1 );

    m_calendarSelectedDate = m_calendarToday;

    // Colorize sundays
    for( int i = 0; i < NUM_TOTAL_CALENDAR_ELEMENT; i = i+7 )
    {
        QPalette palette;
        palette.setColor(QPalette::Window,QColor( 254, 190, 190 ));
        palette.setColor(QPalette::WindowText,Qt::black);

        m_calendarTitle[i]->setAutoFillBackground( true );
        m_calendarTitle[i]->setPalette( palette );

//        m_calendarBody[i]->setAutoFillBackground( true );
//        m_calendarBody[i]->setPalette( palette );
    }

    // Colorize Saturdays
    for( int i = 6; i < NUM_TOTAL_CALENDAR_ELEMENT; i = i+7 )
    {
        QPalette palette;
        palette.setColor(QPalette::Window,QColor( 180, 180, 180 ));
        palette.setColor(QPalette::WindowText,Qt::black);

        m_calendarTitle[i]->setAutoFillBackground( true );
        m_calendarTitle[i]->setPalette( palette );

//        m_calendarBody[i]->setAutoFillBackground( true );
//        m_calendarBody[i]->setPalette( palette );
    }

    for( int i = 0; i < NUM_TOTAL_CALENDAR_ELEMENT; ++i )
        connect( m_calendarBody[i], SIGNAL(buttonReleased()), this, SLOT(onDateClicked()));


    QPixmap pixNextMonth(":/images/arrow_next_month.png");
    QIcon iconNextMonth( pixNextMonth );
    ui->pushbutton_calendar_next_month->setIcon( iconNextMonth );
    ui->pushbutton_calendar_next_month->setIconSize( ui->pushbutton_calendar_next_month->iconSize() );
    ui->pushbutton_calendar_next_month->setStyleSheet("QPushButton{border: none;outline: none;}");


    QPixmap pixNextYear("D:/Dev/Qt/LSH/LSH/arrow_next_year.png");
    QIcon iconNextYear( pixNextYear );
    ui->pushbutton_calendar_next_year->setIcon( iconNextYear );
    ui->pushbutton_calendar_next_year->setIconSize( ui->pushbutton_calendar_next_year->iconSize() );
    ui->pushbutton_calendar_next_year->setStyleSheet("QPushButton{border: none;outline: none;}");

    QPixmap pixPrevMonth(":/images/arrow_prev_month.png");
    QIcon iconPrevMonth( pixPrevMonth );
    ui->pushbutton_calendar_prev_month->setIcon( iconPrevMonth );
    ui->pushbutton_calendar_prev_month->setIconSize( ui->pushbutton_calendar_prev_month->iconSize() );
    ui->pushbutton_calendar_prev_month->setStyleSheet("QPushButton{border: none;outline: none;}");


    QPixmap pixPrevYear("D:/Dev/Qt/LSH/LSH/arrow_prev_year.png");
    QIcon iconPrevYear( pixPrevYear );
    ui->pushbutton_calendar_prev_year->setIcon( iconPrevYear );
    ui->pushbutton_calendar_prev_year->setIconSize( ui->pushbutton_calendar_prev_year->iconSize() );
    ui->pushbutton_calendar_prev_year->setStyleSheet("QPushButton{border: none;outline: none;}");


    UpdateCalendar();
    UpdateSchedule();
}

void CalendarWidget::UpdateCalendar()
{
    qDebug() << __FUNCTION__;

    m_calendarDayOffset = m_calendarDate.dayOfWeek();


    UpdateMainDate();


    for( int i = 0; i < NUM_TOTAL_CALENDAR_ELEMENT; ++i )
    {
        m_calendarTitle[i]->clear();
        m_calendarBody[i]->clear();

        m_calendarTitle[i]->setEnabled( true );
        m_calendarBody[i]->setEnabled( true );

        m_calendarTitle[i]->setHidden( false );
        m_calendarBody[i]->setHidden( false );

        QPalette palette;
        palette.setColor( QPalette::Window, Qt::white );
        palette.setColor( QPalette::WindowText, Qt::black );

        m_calendarBody[ i ]->setAutoFillBackground( true );
        m_calendarBody[ i ]->setPalette( palette );
    }

    ColorizeSelectedDay();


    // For each canlendar title, give name of day ( Sunday to Saturday )
    for( int i = 0; i < NUM_TOTAL_CALENDAR_ELEMENT; ++ i )
        m_calendarTitle[i]->setText( GetNameOfDay(i) );


    if( 7 == m_calendarDayOffset)
        m_calendarDayOffset = 0;

    int lastDayOfMonth = m_calendarDate.daysInMonth();

    bool shouldHideLastRow = lastDayOfMonth + m_calendarDayOffset < 36 ? true : false;

    if( shouldHideLastRow )
    {
        for( int i = 35; i < NUM_TOTAL_CALENDAR_ELEMENT; ++i )
        {
            m_calendarTitle[ i ]->setHidden( true );
            m_calendarBody[ i ]->setHidden( true );
        }
    }

    // write text of day in calendar title widgets
    for( int i = 0; i < lastDayOfMonth; ++i )
    {
        int realIndex = i + m_calendarDayOffset;
        m_calendarTitle[ realIndex ]->setText( QString::number(i + 1) + "  (" + m_calendarTitle[ realIndex ]->text() + ")" );
    }


    // disable calendar item, for date < 1st day of month
    for( int i = 0; i < m_calendarDayOffset; ++i )
    {
        m_calendarTitle[ i ]->clear();
        m_calendarTitle[ i ]->setEnabled( false );
        m_calendarBody[ i ]->setEnabled( false );
    }


    // disable calendar item, for date > last day of month
    for( int i = lastDayOfMonth; i + m_calendarDayOffset < NUM_TOTAL_CALENDAR_ELEMENT; ++i )
    {
        int realIndex = i + m_calendarDayOffset;
        m_calendarTitle[ realIndex ]->clear();

        m_calendarTitle[ realIndex ]->setEnabled( false );
        m_calendarBody[ realIndex ]->setEnabled( false );
    }


    if( m_dbManager != nullptr )
    {
        QString firstTime = QString( "%1-%2-%3 %4:%5")
                .arg( m_calendarDate.year() )
                .arg( m_calendarDate.month(),2, 10, QChar('0') )
                .arg( 1, 2, 10, QChar('0') )
                .arg( 8, 2, 10, QChar('0') )
                .arg( 0, 2, 10, QChar('0') );

        QString lastTime = QString( "%1-%2-%3 %4:%5")
                .arg( m_calendarDate.year() )
                .arg( m_calendarDate.month(),2, 10, QChar('0') )
                .arg( m_calendarDate.daysInMonth(), 2, 10, QChar('0') )
                .arg( 23, 2, 10, QChar('0') )
                .arg( 0, 2, 10, QChar('0') );

        QStringList queryResultList = m_dbManager->SelectOperationBetweenTwoDates(firstTime, lastTime);

        foreach( const QString& str, queryResultList )
        {
            qDebug() << str;
        }
    }


}

QString CalendarWidget::GetNameOfDay( int i )
{
    int remainder = i % 7;
    switch( remainder )
    {
        case 0 :
            return QString::fromLocal8Bit( "일" );
            break;
        case 1 :
            return QString::fromLocal8Bit( "월" );
            break;
        case 2 :
            return QString::fromLocal8Bit( "화" );
            break;
        case 3 :
            return QString::fromLocal8Bit( "수" );
            break;
        case 4 :
            return QString::fromLocal8Bit( "목" );
            break;
        case 5 :
            return QString::fromLocal8Bit( "금" );
            break;
        case 6 :
            return QString::fromLocal8Bit( "토" );
            break;
        default :
            return QString::fromLocal8Bit( "???" );
            break;
    }
}



void CalendarWidget::UpdateMainDate()
{
    QString text = QString::number( m_calendarDate.year() )  + QString::fromLocal8Bit("년 ") +
                   QString::number( m_calendarDate.month() ) + QString::fromLocal8Bit("월");

    ui->label_main_date->setText( text );
}



void CalendarWidget::UpdateSchedule()
{
    ColorizeSelectedDay();

    UpdateScheduleWidget();
}



void CalendarWidget::UpdateScheduleDate()
{
    QString text = QString::number( m_calendarSelectedDate.year() )  + QString::fromLocal8Bit("년 ") +
                   QString::number( m_calendarSelectedDate.month() ) + QString::fromLocal8Bit("월 ") +
                   QString::number( m_calendarSelectedDate.day() ) + QString::fromLocal8Bit("일");

    ui->label_schedule_date->setText( text );
}



void CalendarWidget::onReturnToCurrentMonth()
{
    m_calendarDate  = QDate( m_calendarToday.year(), m_calendarToday.month(), 1 );
    UpdateCalendar();
}



void CalendarWidget::onDateClicked()
{

    QString senderName = QObject::sender()->objectName();

    qDebug() << senderName;
    QString index = senderName.right(2);

    int day = index.toInt() - m_calendarDayOffset + 1;
    if( day <= 0 )
        return;

    int lastDayOfMonth = m_calendarDate.daysInMonth();


    if( day > lastDayOfMonth )
        return;

    m_calendarSelectedDate = QDate( m_calendarDate.year(), m_calendarDate.month(), day );

    UpdateSchedule();
}

void CalendarWidget::ColorizeSelectedDay()
{
    if( m_calendarDate.month() != m_calendarSelectedDate.month() ||
        m_calendarDate.year() != m_calendarSelectedDate.year() )
        return;

    for( int i = 0; i < NUM_TOTAL_CALENDAR_ELEMENT; ++i)
    {
        QPalette palette;
        palette.setColor( QPalette::Window, Qt::white );
        palette.setColor( QPalette::WindowText, Qt::black );

        m_calendarBody[ i ]->setAutoFillBackground( true );
        m_calendarBody[ i ]->setPalette( palette );
    }

    int index = m_calendarSelectedDate.day() + m_calendarDayOffset - 1;

    QPalette palette;
    palette.setColor( QPalette::Window, QColor(130, 228, 130));
    palette.setColor( QPalette::WindowText, Qt::black );

    m_calendarBody[ index ]->setAutoFillBackground( true );
    m_calendarBody[ index ]->setPalette( palette );
}

void CalendarWidget::UpdateScheduleWidget()
{
    qDebug() << __FUNCTION__;
    UpdateScheduleDate();

    if( m_dbManager != nullptr )
    {
        QString firstTime = QString( "%1-%2-%3 %4:%5")
                .arg( m_calendarSelectedDate.year() )
                .arg( m_calendarSelectedDate.month(),2, 10, QChar('0') )
                .arg( m_calendarSelectedDate.day(), 2, 10, QChar('0') )
                .arg( 8, 2, 10, QChar('0') )
                .arg( 0, 2, 10, QChar('0') );

        QString lastTime = QString( "%1-%2-%3 %4:%5")
                .arg( m_calendarSelectedDate.year() )
                .arg( m_calendarSelectedDate.month(),2, 10, QChar('0') )
                .arg( m_calendarSelectedDate.day(), 2, 10, QChar('0') )
                .arg( 23, 2, 10, QChar('0') )
                .arg( 0, 2, 10, QChar('0') );

        QStringList queryResultList = m_dbManager->SelectOperationBetweenTwoDates(firstTime, lastTime);

        foreach( const QString& str, queryResultList )
        {
            qDebug() << str;
        }
    }

}
