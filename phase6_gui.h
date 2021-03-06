#ifndef PHASE6_GUI_H
#define PHASE6_GUI_H

#include <QMainWindow>
#include <Vocabulary.h>
#include "dialog_add.h"
#include "dialog_edit.h"
#include "dialog_overview.h"

namespace Ui {
class Phase6_GUI;
}

class Phase6_GUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit Phase6_GUI(QWidget *parent = nullptr);
    ~Phase6_GUI();

    Vocabulary* vocab = nullptr;

private slots:
    void on_pb_add_clicked();

    void on_pb_edit_clicked();

    void on_pb_next_clicked();

    void on_rb_lang1_clicked();

    void on_rb_lang2_clicked();

    void on_le_answer_returnPressed();

    void on_pb_overview_clicked();

private:
    Ui::Phase6_GUI *ui;

    Word* currentWord = nullptr;

    Dialog_Add* dialog_add = nullptr;
    Dialog_Edit* dialog_edit = nullptr;
    Dialog_Overview* dialog_overview = nullptr;

    std::random_device dev;

    bool lang1 = false;
    bool currentStateLang1 = true;

    bool compare(QString w1, std::vector<QString> w2);

    QString pickRandom(std::vector<QString> list);

    void closeEvent(QCloseEvent *event);
};

#endif // PHASE6_GUI_H
