#ifndef DIALOG_APP_H
#define DIALOG_APP_H

#include <QDialog>
#include <QLineEdit>
#include <vector>

class Phase6_GUI;

namespace Ui {
class Dialog_App;
}

class Dialog_App : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_App(QWidget *parent = nullptr);
     Dialog_App(Phase6_GUI* phase6_gui);
    ~Dialog_App();

private slots:

    void on_pb_save_clicked();

    void on_pb_cancel_clicked();

    void on_pb_plus_lang1_clicked();

    void on_pb_plus_lang2_clicked();

private:
    Ui::Dialog_App *ui;

    Phase6_GUI* phase6_gui;
};

#endif // DIALOG_APP_H
