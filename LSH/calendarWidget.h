#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QDate>

#include "dbmanager.h"

namespace Ui {
class Widget;
}

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarWidget(QWidget *parent = 0, DBManager* _dbManager = nullptr );
    ~CalendarWidget();

    void SetDbManager( DBManager* _dbManager );

private:
    Ui::Widget *ui;

    enum { NUM_TOTAL_CALENDAR_ELEMENT = 42 };

    QLabel* m_calendarTitle[ NUM_TOTAL_CALENDAR_ELEMENT ];
    QLabel* m_calendarBody[ NUM_TOTAL_CALENDAR_ELEMENT ];
    QDate   m_calendarDate;
    QDate   m_calendarToday;
    QDate   m_calendarSelectedDate;
    int     m_calendarDayOffset;

private slots:
    void onCalendarPrevMonthButtonPressed();
    void onCalendarNextMonthButtonPressed();
    void onCalendarPrevYearButtonPressed();
    void onCalendarNextYearButtonPressed();
    void onReturnToCurrentMonth();

    void onDateClicked();
private:
    void Initialize();
    void UpdateCalendar();    
    void UpdateMainDate();

    void UpdateSchedule();
    void UpdateScheduleDate();
    void ColorizeSelectedDay();

    // when a date is selected from calendar
    // request data to DB and show schedules of the selected day
    void UpdateScheduleWidget();

    QString GetNameOfDay( int i );

private:
    DBManager * m_dbManager;

};

#endif // WIDGET_H
