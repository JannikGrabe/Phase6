#include "dialog_app.h"
#include "ui_dialog_app.h"
#include "phase6_gui.h"
#include <QMessageBox>

Dialog_App::Dialog_App(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_App)
{
    ui->setupUi(this);
}

Dialog_App::Dialog_App(Phase6_GUI *phase6_gui) :
    QDialog(phase6_gui),
    ui(new Ui::Dialog_App)
{
    ui->setupUi(this);
    this->phase6_gui = phase6_gui;
}

Dialog_App::~Dialog_App()
{
    delete ui;
}

void Dialog_App::on_pb_save_clicked()
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
                                  Word::toString(lang1_words) + " - " + Word::toString(lang2_words) + " hinzufügen?",
                                  QMessageBox::Yes|QMessageBox::Cancel);
    if (reply == QMessageBox::Yes) {
       this->phase6_gui->vocab->addWord(lang1_words, lang2_words);
       this->ui->le_lang1->clear();
       this->ui->le_lang2->clear();

        QLayoutItem* item;
        while((item = this->ui->vl_lang1->takeAt(1)) != nullptr) {
            item->widget()->setParent(nullptr);
            delete item;
        }
        while((item = this->ui->vl_lang2->takeAt(1)) != nullptr) {
            item->widget()->setParent(nullptr);
            delete item;
        }
    }

    this->ui->le_lang1->setFocus();
}

void Dialog_App::on_pb_cancel_clicked()
{
    this->hide();
}

void Dialog_App::on_pb_plus_lang1_clicked()
{
    QLineEdit* le = new QLineEdit();
    le->setAlignment(Qt::AlignCenter);
    QFont font("MS Shell Dlg 2", 10);
    le->setFont(font);

    this->ui->vl_lang1->addWidget(le);
    le->setFocus();
}

void Dialog_App::on_pb_plus_lang2_clicked()
{
    QLineEdit* le = new QLineEdit();
    le->setAlignment(Qt::AlignCenter);
    QFont font("MS Shell Dlg 2", 10);
    le->setFont(font);

    this->ui->vl_lang2->addWidget(le);
    le->setFocus();
}
