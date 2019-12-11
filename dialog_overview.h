#ifndef DIALOG_OVERVIEW_H
#define DIALOG_OVERVIEW_H

#include <QDialog>

class Phase6_GUI;

namespace Ui {
class Dialog_Overview;
}

class Dialog_Overview : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Overview(Phase6_GUI* gui);
    ~Dialog_Overview();

private slots:
    void on_pb_close_clicked();

private:
    Ui::Dialog_Overview *ui;
};

#endif // DIALOG_OVERVIEW_H
