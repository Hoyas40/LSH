#include "my_qlabel.h"



my_qlabel::my_qlabel(QWidget *parent)
    : QLabel( parent )
{

}

my_qlabel::my_qlabel(const QString &text, QWidget *parent)
    : QLabel( parent )
{
    setText( text );
}

bool my_qlabel::event(QEvent *e)
{
    switch( e->type() )
    {
        case QEvent::MouseButtonRelease :
        {
            QMouseEvent * mouseEvent = static_cast<QMouseEvent*>( e );
            if( mouseEvent->button() == Qt::LeftButton )
                emit buttonReleased();
        }
    }


    return QWidget::event( e );
}

