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

private:
    Ui::Dialog_Overview *ui;
    Phase6_GUI* gui;
};

#endif // DIALOG_OVERVIEW_H
