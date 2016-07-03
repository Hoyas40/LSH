#ifndef INSERTSUBTABLEDIALOG_H
#define INSERTSUBTABLEDIALOG_H

#include <QDialog>

namespace Ui {
class InsertSubTableDialog;
}

class InsertSubTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsertSubTableDialog(QWidget *parent = 0);
    ~InsertSubTableDialog();

    void SetId( const QString& _id );

    QString GetName() const;

private slots:


private:
    Ui::InsertSubTableDialog *ui;
};

#endif // INSERTSUBTABLEDIALOG_H
