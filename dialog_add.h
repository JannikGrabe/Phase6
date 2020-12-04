#ifndef DIALOG_APP_H
#define DIALOG_APP_H

#include <QDialog>
#include <QLineEdit>
#include <vector>
#include "wordgroupbox.h"

class Phase6_GUI;
class Dialog_Overview;

namespace Ui {
class Dialog_App;
}

class Dialog_Add : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Add(QWidget *parent = nullptr);
     Dialog_Add(Phase6_GUI* phase6_gui);
    ~Dialog_Add();

private slots:

    void on_pb_save_clicked();

    void on_pb_cancel_clicked();

    void on_pushButton_pressed();

private:
    Ui::Dialog_App *ui;

    Phase6_GUI* phase6_gui = nullptr;
    Dialog_Overview* dialog_overview = nullptr;

    std::vector<WordGroupBox*> word_group_boxes;
    QVBoxLayout* vl_words = nullptr;

    void clear();
};

#endif // DIALOG_APP_H
