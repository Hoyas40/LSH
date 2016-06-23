#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QDate>

namespace Ui {
class Widget;
}

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarWidget(QWidget *parent = 0);
    ~CalendarWidget();

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
    QString GetNameOfDay( int i );
    void UpdateMainDate();

    void UpdateSchedule();
    void UpdateScheduleDate();
    void ColorizeSelectedDay();

    // when a date is selected from calendar
    // request data to DB and show schedules of the selected day
    void UpdateScheduleWidget();

};

#endif // WIDGET_H
