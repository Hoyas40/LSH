#include "calendarWidget.h"
#include "ui_calendarWidget.h"

#include <QDate>
#include <QMenu>
#include <QMessageBox>

#include "my_qlabel.h"
#include "operationdialog.h"



#include <QDebug>

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


    for( int i = 0; i < NUM_TOTAL_CALENDAR_ELEMENT; ++i )
    {
        m_calendarBody[i]->setContextMenuPolicy( Qt::CustomContextMenu );
        connect( m_calendarBody[i], &QTreeWidget::customContextMenuRequested, this, &CalendarWidget::RequestContextFromCalendar );
    }

    // Colorize sundays
    for( int i = 0; i < NUM_TOTAL_CALENDAR_ELEMENT; i = i+7 )
    {
        QPalette palette;
        palette.setColor(QPalette::Window,QColor( 254, 190, 190 ));
        palette.setColor(QPalette::WindowText,Qt::black);

        m_calendarTitle[i]->setAutoFillBackground( true );
        m_calendarTitle[i]->setPalette( palette );
    }

    // Colorize Saturdays
    for( int i = 6; i < NUM_TOTAL_CALENDAR_ELEMENT; i = i+7 )
    {
        QPalette palette;
        palette.setColor(QPalette::Window,QColor( 180, 180, 180 ));
        palette.setColor(QPalette::WindowText,Qt::black);

        m_calendarTitle[i]->setAutoFillBackground( true );
        m_calendarTitle[i]->setPalette( palette );
    }

    for( int i = 0; i < NUM_TOTAL_CALENDAR_ELEMENT; ++i )        
    {
        connect( m_calendarBody[i], SIGNAL(buttonReleased()), this, SLOT(onDateClicked()));
        connect( m_calendarBody[i], SIGNAL(rightButtonReleased()), this, SLOT(onRightButtonClicked()));
    }

    ui->treeWidget->setContextMenuPolicy( Qt::CustomContextMenu );
    connect( ui->treeWidget, &QTreeWidget::customContextMenuRequested, this, &CalendarWidget::RequestContextFromSchedule);

    ui->pushbutton_calendar_next_month->setStyleSheet(
                "QPushButton{image: url(:/images/arrow_next_month.png);border:0px;}"
                "QPushButton:hover{image:url(:/images/arrow_next_month_hover.png); color: lightgray; border:0px}"
                "QPushButton:pressed{image:url(:/images/arrow_next_month_pressed.png); position:absolute; top: 2px; left: 2px;}");


    ui->pushbutton_calendar_next_year->setStyleSheet(
                "QPushButton{image: url(:/images/arrow_next_year.png);border:0px;}"
                "QPushButton:hover{image:url(:/images/arrow_next_year_hover.png);border:0px}"
                "QPushButton:pressed{image:url(:/images/arrow_next_year_pressed.png); position:absolute; top: 2px; left: 2px;}");


    ui->pushbutton_calendar_prev_month->setStyleSheet(
                "QPushButton{image: url(:/images/arrow_prev_month.png);border:0px;}"
                "QPushButton:hover{image:url(:/images/arrow_prev_month_hover.png);border:0px}"
                "QPushButton:pressed{image:url(:/images/arrow_prev_month_pressed.png); position:absolute; top: 2px; left: 2px;}");


    ui->pushbutton_calendar_prev_year->setStyleSheet(
                "QPushButton{image: url(:/images/arrow_prev_year.png);border:0px;}"
                "QPushButton:hover{image:url(:/images/arrow_prev_year_hover.png);border:0px}"
                "QPushButton:pressed{image:url(:/images/arrow_prev_year_pressed.png); position:absolute; top: 2px; left: 2px;}");


    ui->pushbutton_home->setStyleSheet(
                "QPushButton{image: url(:/images/home_button.png);border:0px;}"
                "QPushButton:hover{image:url(:/images/home_button_hover.png);border:0px}"
                "QPushButton:pressed{image:url(:/images/home_button_pressed.png); position:absolute; top: 2px; left: 2px;}");


    ui->pushButton_new->setStyleSheet(
                "QPushButton{image: url(:/images/new_button.png);border:0px;}"
                "QPushButton:hover{image:url(:/images/new_button_hover.png);border:0px}"
                "QPushButton:pressed{image:url(:/images/new_button_pressed.png); position:absolute; top: 2px; left: 2px;}");


    ui->treeWidget->setAutoFillBackground( true );
    ui->treeWidget->setHeaderLabels( QStringList() << QString::fromLocal8Bit("시간")
                                     << QString::fromLocal8Bit("이름")
                                     << QString::fromLocal8Bit("컬")
                                     << QString::fromLocal8Bit("모")
                                     << QString::fromLocal8Bit("색상")  // 4
                                     << QString::fromLocal8Bit("길이")
                                     << QString::fromLocal8Bit("숱")
                                     << QString::fromLocal8Bit("가격")
                                     << QString::fromLocal8Bit("리터치")
                                     );

    ui->treeWidget->header()->resizeSection(0, 90);
    ui->treeWidget->header()->resizeSection(1, 70);
    ui->treeWidget->header()->resizeSection(2, 60);
    ui->treeWidget->header()->resizeSection(3, 60);
    ui->treeWidget->header()->resizeSection(4, 70);
    ui->treeWidget->header()->resizeSection(5, 80);
    ui->treeWidget->header()->resizeSection(6, 60);
    ui->treeWidget->header()->resizeSection(7, 80);
    ui->treeWidget->header()->resizeSection(8, 30);


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

        for( int i = 0; i < queryResultList.size(); ++i )
        {
            QString str = queryResultList[i];

            QStringList queryItemList = str.split('|');

            QStringList dateTimeList = queryItemList[2].split(' ');


            QStringList dateList = dateTimeList[0].split('-');

            QString timeStr = dateTimeList[1];


            int day = dateList[2].toInt();


            QString clientID = queryItemList[1];

            QString queryWithID = m_dbManager->SelectClientWithId( clientID );

            QString clientName = queryWithID.split( ':' )[1];


            QString text = m_calendarBody[ day + m_calendarDayOffset - 1 ]->text();
            if( !text.isEmpty() )
                text += "\n";
            text += " " + timeStr + "  " + clientName;
            m_calendarBody[ day + m_calendarDayOffset - 1 ]->setText( text );
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




void CalendarWidget::onDateClicked()
{
    qDebug() << __FUNCTION__;

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

void CalendarWidget::onRightButtonClicked()
{






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
    palette.setColor( QPalette::Window, QColor(225, 190, 231));
    palette.setColor( QPalette::WindowText, Qt::black );

    m_calendarBody[ index ]->setAutoFillBackground( true );
    m_calendarBody[ index ]->setPalette( palette );
}

void CalendarWidget::UpdateScheduleWidget()
{
    qDebug() << __FUNCTION__;
    UpdateScheduleDate();

    ui->treeWidget->clear();

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
            QStringList itemList = str.split('|');


            // time info
            QStringList dateTimeList = itemList[2].split(' ');
            QString timeStr = dateTimeList[1];


            // client info
            QString clientID = itemList[1];
            QString queryWithID = m_dbManager->SelectClientWithId( clientID );
            QString clientName = queryWithID.split( ':' )[1];



            // curl
            QString curlId = itemList[3];
            QString curlQuery = m_dbManager->SelectSubTableWithId( TABLE_CURL, curlId );

            // type
            QString typeId = itemList[4];
            QString typeQuery = m_dbManager->SelectSubTableWithId( TABLE_TYPE, typeId );

            // color
            QString colorId = itemList[5];
            QString colorQuery = m_dbManager->SelectSubTableWithId( TABLE_COLOR, colorId );

            //length
            QString lengthId = itemList[6];
            QString lengthQuery = m_dbManager->SelectSubTableWithId( TABLE_LENGTH, lengthId );


            //number
            QString numberId = itemList[7];
            QString numberQuery = m_dbManager->SelectSubTableWithId( TABLE_NUMBER, numberId );

            // price
            QString price = itemList[8];
            QString optionStr = itemList[9];

            int option = optionStr.toInt();

            bool bShown = option & 0x00000001;
            bool bRetouch = option & 0x00000002;

            QTreeWidgetItem * item = new QTreeWidgetItem(ui->treeWidget);
            item->setText(0, timeStr );
            item->setText(1, clientName );
            item->setText(2, curlQuery.split(':')[1] );
            item->setText(3, typeQuery.split(':')[1] );
            item->setText(4, colorQuery.split(':')[1] );
            item->setText(5, lengthQuery.split(':')[1] );
            item->setText(6, numberQuery.split(':')[1] );
            item->setText(7, price );
//            item->setTextAlignment(0, Qt::AlignCenter);
//            item->setTextAlignment(1, Qt::AlignCenter);
//            item->setTextAlignment(2, Qt::AlignCenter);
//            item->setTextAlignment(3, Qt::AlignCenter);

            if( bShown )
            {
                for( int i = 0; i < 4; ++i )
                {
                    item->setBackgroundColor( i, Qt::black );
                    item->setTextColor( i, Qt::white );
                }
            }

            item->setText(8, bRetouch ? "O" : "X" );

            item->setData(0, Qt::UserRole, itemList[0] );

            ui->treeWidget->addTopLevelItem( item );

            //qDebug() << clientName << timeStr << curlId << price << shown;


        }
    }

}

void CalendarWidget::on_pushbutton_home_clicked()
{
    m_calendarDate  = QDate( m_calendarToday.year(), m_calendarToday.month(), 1 );
    UpdateCalendar();
}

void CalendarWidget::on_pushButton_new_clicked()
{
    emit SignalAddOperation( m_calendarSelectedDate );
}

void CalendarWidget::on_calendar_context_clicked()
{
    emit SignalAddOperation( m_calendarContextDate );
}

void CalendarWidget::RequestContextFromCalendar(const QPoint &pos)
{
    qDebug() << __FUNCTION__;
    QLabel* selectedLabel = static_cast<QLabel*>( sender() );



    if( selectedLabel != nullptr )
    {
        QString senderName = selectedLabel->objectName();
        int selectedLabelNumber = senderName.right(2).toInt();

        int selectedYear = m_calendarDate.year();
        int selectedMonth = m_calendarDate.month();
        int selectedDay = selectedLabelNumber - m_calendarDayOffset + 1;

        m_calendarContextDate = QDate( selectedYear, selectedMonth, selectedDay );
        qDebug() << m_calendarContextDate;


        QAction *newAct = new QAction(QIcon(":/images/new_button.png"), QString::fromLocal8Bit("약속 추가"), selectedLabel );
        //newAct->setStatusTip(tr("new sth"));

        connect(newAct, SIGNAL(triggered()), this, SLOT(on_calendar_context_clicked()));

        QMenu menu(selectedLabel);
        menu.addAction(newAct);

        QPoint pt(pos);
        //menu.exec( selectedLabel->mapFromGlobal(pos) );
        menu.exec( selectedLabel->mapToGlobal( pos) );


    }


}

void CalendarWidget::RequestContextFromSchedule(const QPoint &pos)
{
    QTreeWidgetItem *item = ui->treeWidget->itemAt( pos );

    if( item != nullptr )
    {
        m_operationId = item->data( 0, Qt::UserRole ).toString();

        QAction *editAct = new QAction(QIcon(""), QString::fromLocal8Bit("약속 편집"), this);
        connect(editAct, SIGNAL(triggered()), this, SLOT( on_Schedule_Edited( ) ));

        QAction *deleteAct = new QAction(QIcon(""), QString::fromLocal8Bit("약속 삭제"), this);
        connect(deleteAct, SIGNAL(triggered()), this, SLOT( on_Schedule_Deleted() ));



        QMenu menu(this);
        menu.addAction(editAct);
        menu.addAction(deleteAct);

        //QPoint pt(pos);
        menu.exec( ui->treeWidget->mapToGlobal(pos) );
    }

}

void CalendarWidget::on_Schedule_Edited()
{
    qDebug() << __FUNCTION__;

    OperationDialog diag;
    diag.SetDbManager( m_dbManager );
    diag.SetRole( OperationDialog::OPERATION_DIALOG_EDIT );
    diag.SetOperationId( m_operationId );
    diag.Init();

    if( diag.exec() == QDialog::Accepted )
    {
        UpdateCalendar();
        UpdateSchedule();
    }
}

void CalendarWidget::on_Schedule_Deleted()
{
    int res = QMessageBox::warning( this, QString::fromLocal8Bit("위험"), QString::fromLocal8Bit("약속을 정말 정말 삭제하시겠습니까?"), QMessageBox::Ok | QMessageBox::Cancel );

    if( res == QMessageBox::Ok )
    {
        qDebug() << "OK";

        if( m_dbManager != nullptr )
        {
            m_dbManager->DeleteOperation( m_operationId );

            UpdateCalendar();
            UpdateSchedule();
        }
    }
    else
    {
        qDebug() << "Cancel";
    }

}
