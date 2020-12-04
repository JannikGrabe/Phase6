#include "dialog_overview.h"
#include "ui_dialog_overview.h"
#include "phase6_gui.h"
#include <chrono>

Dialog_Overview::Dialog_Overview(Phase6_GUI *gui) :
    QDialog(gui),
    ui(new Ui::Dialog_Overview)
{
    ui->setupUi(this);

    this->gui = gui;

    this->fill_table(gui->vocab->getVocabulary());

    const std::vector<int> counts = gui->vocab->get_words_per_phase();
    this->ui->l_total_count->setText(QString::number(counts[0]));
    this->ui->l_phase1_count->setText(QString::number(counts[1]));
    this->ui->l_phase2_count->setText(QString::number(counts[2]));
    this->ui->l_phase3_count->setText(QString::number(counts[3]));
    this->ui->l_phase4_count->setText(QString::number(counts[4]));
    this->ui->l_phase5_count->setText(QString::number(counts[5]));
    this->ui->l_phase6_count->setText(QString::number(counts[6]));
}

void Dialog_Overview::fill_table(std::vector<Word*> words){

    this->ui->tw_overview->clear();
    this->ui->tw_overview->setRowCount(0);
    this->ui->tw_overview->setHorizontalHeaderItem(0, new QTableWidgetItem("Englisch"));
    this->ui->tw_overview->setHorizontalHeaderItem(1, new QTableWidgetItem("Deutsch"));
    this->ui->tw_overview->setHorizontalHeaderItem(2, new QTableWidgetItem("Phase"));
    this->ui->tw_overview->setHorizontalHeaderItem(3, new QTableWidgetItem("Zeit bis Abfrage"));
    this->ui->tw_overview->insertColumn(4);
    this->ui->tw_overview->setColumnHidden(4, true);
    this->ui->tw_overview->verticalHeader()->setVisible(false);
    this->ui->tw_overview->horizontalHeader()->setStyleSheet("font-weight: 600");

    foreach(Word* word, words) {
        this->fill_row(this->ui->tw_overview->rowCount(), word);
    }

    int tableWidth = 0;

    for(int i = 0; i < 4; i++) {
        tableWidth += this->ui->tw_overview->columnWidth(i);
    }

    this->resize(tableWidth + 50, this->size().height());
}

void Dialog_Overview::only_table(bool only_table)
{
    if(only_table) {

        this->ui->gb_total->setHidden(true);
        this->ui->gb_phase1->setHidden(true);
        this->ui->gb_phase2->setHidden(true);
        this->ui->gb_phase3->setHidden(true);
        this->ui->gb_phase4->setHidden(true);
        this->ui->gb_phase5->setHidden(true);
        this->ui->gb_phase6->setHidden(true);
        this->ui->l_search->setHidden(true);
        this->ui->le_search->setHidden(true);
    } else {
        this->ui->gb_total->setHidden(false);
        this->ui->gb_phase1->setHidden(false);
        this->ui->gb_phase2->setHidden(false);
        this->ui->gb_phase3->setHidden(false);
        this->ui->gb_phase4->setHidden(false);
        this->ui->gb_phase5->setHidden(false);
        this->ui->gb_phase6->setHidden(false);
        this->ui->l_search->setHidden(false);
        this->ui->le_search->setHidden(false);
    }
}

void Dialog_Overview::fill_row(int row, Word *word)
{
    if(row < 0) {
        return;
    }

    int row_count = this->ui->tw_overview->rowCount();
    if(row >= row_count) {
        row = row_count;
        this->ui->tw_overview->insertRow(row_count);
    }

    int phase = word->getPhase();

    QTableWidgetItem* item = new QTableWidgetItem(Word::toString(word->lang1));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    this->ui->tw_overview->setItem(row, 0, item);

    item = new QTableWidgetItem(Word::toString(word->lang2));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    this->ui->tw_overview->setItem(row, 1, item);

    item = new QTableWidgetItem(QString::number(phase));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    this->ui->tw_overview->setItem(row, 2, item);

    int time_passed = std::chrono::duration_cast<std::chrono::hours>(std::chrono::system_clock::now().time_since_epoch()).count()
            - word->getTime();
    int hours_until_asked = Vocabulary::getHoursOfPhase(phase) - time_passed;
    hours_until_asked = hours_until_asked < 0 ? 0 : hours_until_asked;

    item = new QTableWidgetItem(QString::number(hours_until_asked));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    this->ui->tw_overview->setItem(row, 3, item);

    item = new QTableWidgetItem(QString::number(word->id));
    this->ui->tw_overview->setItem(row, 4, item);
}

int Dialog_Overview::find_row_by_id(int id)
{
    if(id < 0) {
        return -1;
    }

    int row_count = this->ui->tw_overview->rowCount();

    for(int i = 0; i < row_count; i++) {
        QTableWidgetItem* item = this->ui->tw_overview->item(i, 4);
        if(item->text() == QString::number(id)) {
            return item->row();
        }
    }

    return -1;
}

Dialog_Overview::~Dialog_Overview()
{
    delete ui;
    if(this->dialog_edit != nullptr) {
        delete this->dialog_edit;
    }
}

void Dialog_Overview::on_pb_close_clicked()
{
    this->close();
}

void Dialog_Overview::on_le_search_textChanged(const QString &text)
{
    if(text.isEmpty()) {
        this->fill_table(this->gui->vocab->getVocabulary());
        return;
    }

    std::vector<Word*> exact = this->gui->vocab->find(text, false, false);

    std::vector<Word*> contains = this->gui->vocab->find(text, false, true);

    std::vector<Word*> results = exact;

    for(Word* word : contains) {
        std::vector<Word*>::iterator it = std::find(exact.begin(), exact.end(), word);
        if(it != exact.end()) {
            // skip
        } else {
            results.push_back(word);
        }
    }

    this->fill_table(results);
}

void Dialog_Overview::on_word_edited(int id) {

    int row = this->find_row_by_id(id);

    if(row < 0) {
        return;
    }

    Word* word = this->gui->vocab->find(id);

    if(word == nullptr) {
        this->ui->tw_overview->removeRow(row);
        return;
    }

    this->fill_row(row, word);
}

void Dialog_Overview::on_tw_overview_cellDoubleClicked(int row, int)
{
    QTableWidgetItem * item = this->ui->tw_overview->item(row, 4);
    if(item == nullptr) {
        return;
    }

    Word* word = this->gui->vocab->find(item->text().toInt());

    if(word != nullptr) {
        if(this->dialog_edit != nullptr)
            delete this->dialog_edit;
        this->dialog_edit = new Dialog_Edit(this->gui, word);
        QObject::connect(this->dialog_edit, &Dialog_Edit::word_edited, this, &Dialog_Overview::on_word_edited);
        this->dialog_edit->show();
        this->row_current_word = row;
    }
}
