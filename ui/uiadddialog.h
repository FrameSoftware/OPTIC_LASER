#ifndef UIADDDIALOG_H
#define UIADDDIALOG_H

#include <QWidget>

namespace Ui {
class uiAddDialog;
}

class uiAddDialog : public QWidget
{
    Q_OBJECT

public:
    explicit uiAddDialog(QWidget *parent = 0);
    ~uiAddDialog();

private:
    Ui::uiAddDialog *ui;
};

#endif // UIADDDIALOG_H
