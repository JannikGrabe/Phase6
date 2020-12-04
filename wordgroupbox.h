#ifndef ADDWORD_H
#define ADDWORD_H

#include <QGroupBox>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <vector>
#include "Word.h"

class WordGroupBox : public QWidget
{
    Q_OBJECT
public:
    explicit WordGroupBox(QWidget *parent = nullptr);
    ~WordGroupBox();

    QGroupBox *getGroupBox() const;

    Word* getWord();

public slots:
    void on_pb_plus_lang1_clicked();

    void on_pb_plus_lang2_clicked();

private:
    QGroupBox* gb_word;
    QHBoxLayout* gb_layout;

    QVBoxLayout* vl_lang1_all;
    QVBoxLayout* vl_lang2_all;
    QVBoxLayout* vl_lang1;
    QVBoxLayout* vl_lang2;

    QHBoxLayout* hl_plus_lang1;
    QHBoxLayout* hl_plus_lang2;

    QPushButton* pb_plus_lang1;
    QPushButton* pb_plus_lang2;

    QLineEdit* le_lang1;
    QLineEdit* le_lang2;

    QSpacerItem* vsp_top_lang1;
    QSpacerItem* vsp_bottom_lang1;
    QSpacerItem* vsp_top_lang2;
    QSpacerItem* vsp_bottom_lang2;
    QSpacerItem* hsp_left_lang1;
    QSpacerItem* hsp_right_lang1;
    QSpacerItem* hsp_left_lang2;
    QSpacerItem* hsp_right_lang2;
};

#endif // ADDWORD_H
