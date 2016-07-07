#ifndef MY_QLABEL_H
#define MY_QLABEL_H


#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include <QWidget>

#include <QDebug>

class my_qlabel : public QLabel
{
    Q_OBJECT
public:
    explicit my_qlabel( QWidget *parent = 0 );
    explicit my_qlabel( const QString & text = "", QWidget* parent = 0 );

protected:
    bool event(QEvent *e);


signals:
    void buttonReleased();

    void rightButtonReleased();
};

#endif // MY_QLABEL_H
