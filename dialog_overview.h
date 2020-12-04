#ifndef DIALOG_OVERVIEW_H
#define DIALOG_OVERVIEW_H

#include <QDialog>
#include "dialog_edit.h"

class Phase6_GUI;
class Word;

namespace Ui {
class Dialog_Overview;
}

class Dialog_Overview : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Overview(Phase6_GUI* gui);
    ~Dialog_Overview();

    void fill_table(std::vector<Word*> words);

    void only_table(bool only_table);

private slots:
    void on_pb_close_clicked();
    void on_le_search_textChanged(const QString &text);
    void on_word_edited(int id);

    void on_tw_overview_cellDoubleClicked(int row, int column);

private:
    Ui::Dialog_Overview *ui;
    Phase6_GUI* gui = nullptr;
    Dialog_Edit* dialog_edit = nullptr;

    int row_current_word = 0;

    void fill_row(int row, Word* word);

    int find_row_by_id(int id);
};

#endif // DIALOG_OVERVIEW_H
