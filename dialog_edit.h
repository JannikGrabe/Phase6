#ifndef DIALOG_EDIT_H
#define DIALOG_EDIT_H

#include <QDialog>
#include "Word.h"

class Phase6_GUI;

namespace Ui {
class Dialog_Edit;
}

class Dialog_Edit : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Edit(Phase6_GUI* phase6_gui, Word* word);
    ~Dialog_Edit();


private slots:

    void on_pb_save_clicked();

    void on_pb_cancel_clicked();

    void on_pb_delete_clicked();

    void on_pb_plus_lang1_clicked();

    void on_pb_plus_lang2_clicked();

private:
    Ui::Dialog_Edit *ui;

    Phase6_GUI* phase6_gui;

    Word* word = nullptr;
};

#endif // DIALOG_EDIT_H
