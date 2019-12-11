#include "dialog_overview.h"
#include "ui_dialog_overview.h"
#include "phase6_gui.h"
#include <chrono>
#include <iostream>

Dialog_Overview::Dialog_Overview(Phase6_GUI *gui) :
    QDialog(gui),
    ui(new Ui::Dialog_Overview)
{
    ui->setupUi(this);


    std::vector<const Word*> vocab = gui->vocab->getVocabulary();
    int counts[6] = {};

    this->ui->tw_overview->clear();
    this->ui->tw_overview->setHorizontalHeaderItem(0, new QTableWidgetItem("Türkisch"));
    this->ui->tw_overview->setHorizontalHeaderItem(1, new QTableWidgetItem("Deutsch"));
    this->ui->tw_overview->setHorizontalHeaderItem(2, new QTableWidgetItem("Phase"));
    this->ui->tw_overview->setHorizontalHeaderItem(3, new QTableWidgetItem("Zeit bis Abfrage"));
    this->ui->tw_overview->verticalHeader()->setVisible(false);
    this->ui->tw_overview->horizontalHeader()->setStyleSheet("font-weight: 600");


    foreach(const Word* word, vocab) {
        int phase = word->getPhase();
        int rowCount = this->ui->tw_overview->rowCount();
        this->ui->tw_overview->insertRow(rowCount);
        this->ui->tw_overview->setItem(rowCount, 0, new QTableWidgetItem(Word::toString(word->lang1)));
        this->ui->tw_overview->setItem(rowCount, 1, new QTableWidgetItem(Word::toString(word->lang2)));
        this->ui->tw_overview->setItem(rowCount, 2, new QTableWidgetItem(QString::number(phase)));

        int time_passed = std::chrono::duration_cast<std::chrono::hours>(std::chrono::system_clock::now().time_since_epoch()).count()
                - word->getTime();
        int hours_until_asked = Vocabulary::getHoursOfPhase(phase) - time_passed;
        hours_until_asked = hours_until_asked < 0 ? 0 : hours_until_asked;

        this->ui->tw_overview->setItem(rowCount, 3, new QTableWidgetItem(QString::number(hours_until_asked)));

        counts[phase-1]++;
    }

    int tableWidth = 0;

    for(int i = 0; i < 4; i++) {
        tableWidth += this->ui->tw_overview->columnWidth(i);
    }

    this->resize(tableWidth + 50, this->size().height());

    this->ui->l_total_count->setText(QString::number(vocab.size()));
    this->ui->l_phase1_count->setText(QString::number(counts[0]));
    this->ui->l_phase2_count->setText(QString::number(counts[1]));
    this->ui->l_phase3_count->setText(QString::number(counts[2]));
    this->ui->l_phase4_count->setText(QString::number(counts[3]));
    this->ui->l_phase5_count->setText(QString::number(counts[4]));
    this->ui->l_phase6_count->setText(QString::number(counts[5]));
}

Dialog_Overview::~Dialog_Overview()
{
    delete ui;
}

void Dialog_Overview::on_pb_close_clicked()
{
    this->close();
}
