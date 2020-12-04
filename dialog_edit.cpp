#include "dialog_edit.h"
#include "ui_dialog_edit.h"
#include "phase6_gui.h"

#include <QMessageBox>
#include <QLayout>

Dialog_Edit::Dialog_Edit(Phase6_GUI *phase6_gui, Word* word) :
    QDialog(phase6_gui),
    ui(new Ui::Dialog_Edit)
{
    ui->setupUi(this);
    this->phase6_gui = phase6_gui;
    this->word = word;

    this->ui->le_lang1->setText(this->word->lang1[0]);

    for(unsigned int i = 1; i < this->word->lang1.size(); i++) {
        QLineEdit* le = new QLineEdit();
        le->setAlignment(Qt::AlignCenter);
        QFont font("MS Shell Dlg 2", 10);
        le->setFont(font);
        le->setText(this->word->lang1[i]);

        this->ui->vl_lang1->addWidget(le);
        le->setFocus();
    }

    this->ui->le_lang2->setText(this->word->lang2[0]);

    for(unsigned int i = 1; i < this->word->lang2.size(); i++) {
        QLineEdit* le = new QLineEdit();
        le->setAlignment(Qt::AlignCenter);
        QFont font("MS Shell Dlg 2", 10);
        le->setFont(font);
        le->setText(this->word->lang2[i]);

        this->ui->vl_lang2->addWidget(le);
        le->setFocus();
    }

}

Dialog_Edit::~Dialog_Edit()
{
    delete ui;
}

void Dialog_Edit::on_pb_save_clicked()
{
    std::vector<QString> lang1_words;
    std::vector<QString> lang2_words;

    for(int i = 0; i < this->ui->vl_lang1->count(); i++) {
        QLineEdit* le = dynamic_cast<QLineEdit*>(this->ui->vl_lang1->itemAt(i)->widget());

        if(le == nullptr) {
            continue;
        }

        QString word = le->text();

        if(word == "") {
            continue;
        }

        lang1_words.push_back(word);
    }

    for(int i = 0; i < this->ui->vl_lang2->count(); i++) {
        QLineEdit* le = dynamic_cast<QLineEdit*>(this->ui->vl_lang2->itemAt(i)->widget());

        if(le == nullptr) {
            continue;
        }

        QString word = le->text();

        if(word == "") {
            continue;
        }

        lang2_words.push_back(word);
    }

    if(lang1_words.size() == 0 || lang2_words.size() == 0) {
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Bestätigung",
                                  Word::toString(lang1_words) + " - " + Word::toString(lang2_words) + " speichern?",
                                  QMessageBox::Yes|QMessageBox::Cancel);
    if (reply == QMessageBox::Yes) {
        this->phase6_gui->vocab->editWord(this->word, lang1_words, lang2_words);
        emit this->word_edited(this->word->id);
        this->close();
    }

}

void Dialog_Edit::on_pb_cancel_clicked()
{
    this->close();
}

void Dialog_Edit::on_pb_delete_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Bestätigung",
                                  "Dieses Wort löschen?",
                                  QMessageBox::Yes|QMessageBox::Cancel);
    if (reply == QMessageBox::Yes) {
        int id = this->word->id;
        this->phase6_gui->vocab->deleteWord(this->word);
        emit this->word_edited(id);
        this->close();
    }
}

void Dialog_Edit::on_pb_plus_lang1_clicked()
{
    QLineEdit* le = new QLineEdit();
    le->setAlignment(Qt::AlignCenter);
    QFont font("MS Shell Dlg 2", 10);
    le->setFont(font);

    this->ui->vl_lang1->addWidget(le);
    le->setFocus();
}

void Dialog_Edit::on_pb_plus_lang2_clicked()
{
    QLineEdit* le = new QLineEdit();
    le->setAlignment(Qt::AlignCenter);
    QFont font("MS Shell Dlg 2", 10);
    le->setFont(font);

    this->ui->vl_lang2->addWidget(le);
    le->setFocus();
}
