#include "dialog_add.h"
#include "ui_dialog_app.h"
#include "phase6_gui.h"
#include "dialog_overview.h"
#include <QMessageBox>
#include <QLayout>
#include <iostream>
#include <QScrollArea>

Dialog_Add::Dialog_Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_App)
{
    ui->setupUi(this);
}

Dialog_Add::Dialog_Add(Phase6_GUI *phase6_gui) :
    QDialog(phase6_gui),
    ui(new Ui::Dialog_App)
{
    ui->setupUi(this);
    this->phase6_gui = phase6_gui;

    this->vl_words = new QVBoxLayout;

    QVBoxLayout *layout_spacer = new QVBoxLayout;
    layout_spacer->addLayout(this->vl_words);
    layout_spacer->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QWidget *scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout( layout_spacer );
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    scrollArea->setWidgetResizable( true );
    scrollArea->setWidget( scrollAreaContent );
    this->ui->vl_widget->addWidget(scrollArea);

    this->word_group_boxes.push_back(new WordGroupBox());
    this->vl_words->addWidget(this->word_group_boxes[0]->getGroupBox());
}

Dialog_Add::~Dialog_Add()
{
    delete ui;
    if(this->dialog_overview != nullptr) {
       delete this->dialog_overview;
    }

    for(int i = 0; i < this->word_group_boxes.size(); i++) {
        delete this->word_group_boxes[i];
    }
}

void Dialog_Add::on_pb_save_clicked()
{
    std::vector<Word*> words;

    for(int i = 0; i < this->word_group_boxes.size(); i++) {

        Word* word = this->word_group_boxes[i]->getWord();

        if(word != nullptr) {
            this->phase6_gui->vocab->addWord(word);
            words.push_back(word);
        }
    }

    if(words.size() > 0) {
        if(this->dialog_overview == nullptr) {
            this->dialog_overview = new Dialog_Overview(this->phase6_gui);
        }
        this->dialog_overview->only_table(true);
        this->dialog_overview->fill_table(words);
        this->dialog_overview->show();

        this->clear();
        this->hide();
    }
}

void Dialog_Add::on_pb_cancel_clicked()
{
    this->clear();
    this->hide();
}


void Dialog_Add::on_pushButton_pressed()
{
    this->word_group_boxes.push_back(new WordGroupBox());
    this->vl_words->addWidget(this->word_group_boxes.back()->getGroupBox());
}

void Dialog_Add::clear()
{
    for(int i = 0; i < this->word_group_boxes.size(); i++) {
        delete this->word_group_boxes[i];
    }

    this->word_group_boxes.clear();

    this->word_group_boxes.push_back(new WordGroupBox());
    this->vl_words->addWidget(this->word_group_boxes.back()->getGroupBox());
}
