#include "phase6_gui.h"
#include "ui_phase6_gui.h"

Phase6_GUI::Phase6_GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Phase6_GUI)
{
    ui->setupUi(this);
    this->vocab = new Vocabulary(this);
    this->ui->te_solution->hide();
    this->ui->te_solution->setReadOnly(true);
    this->ui->te_solution->setAlignment(Qt::AlignCenter);
    this->ui->pb_next->setFocus();
}

Phase6_GUI::~Phase6_GUI()
{
    delete this->vocab;
    delete ui;
}

void Phase6_GUI::on_pb_add_clicked()
{
    this->dialog_add = new Dialog_App(this);
    dialog_add->show();
}

bool Phase6_GUI::compare(QString w1, std::vector<QString> w2) {
    foreach(QString s, w2) {
        if(w1 == s) {
            return true;
        }
    }
    return w1 == Word::toString(w2);
}

QString Phase6_GUI::pickRandom(std::vector<QString> list)
{
    unsigned int size = list.size();

    std::default_random_engine generator(this->dev());
    std::uniform_int_distribution<unsigned int> distribution(0, size - 1 );

    return list[distribution(generator)];
}

void Phase6_GUI::closeEvent(QCloseEvent *event) {
    this->vocab->finish();
}

void Phase6_GUI::on_pb_edit_clicked()
{
    if(this->currentWord == nullptr) {
        return;
    }

    this->dialog_edit = new Dialog_Edit(this, this->currentWord);
    dialog_edit->show();
}

void Phase6_GUI::on_pb_next_clicked()
{
    this->ui->le_answer->clear();
    this->ui->le_answer->setReadOnly(false);
    this->ui->le_answer->setFocus();
    this->ui->pb_next->setText("Nächstes Wort");
    this->ui->pb_edit->setDisabled(true);
    this->ui->pb_overview->setDisabled(true);
    this->ui->te_solution->hide();
    this->ui->le_answer->show();
    this->ui->le_question->show();

    this->currentWord = this->vocab->drawWord();

    if(this->vocab->isEmpty()) {
        this->ui->le_question->setText(QString("keine Wörter eingetragen"));
        return;
    }

    if(this->currentWord == nullptr) {
        int time_to_next = this->vocab->getTimeUntilNext();
        this->ui->le_answer->hide();
        this->ui->le_question->hide();

        QTextEdit* te = this->ui->te_solution;
        te->show();
        te->setFontPointSize(10);
        te->clear();
        te->setAlignment(Qt::AlignCenter);
        te->setStyleSheet("background-color: white");

        te->append("\n\nDas nächste Wort wird in\n");
        te->setFontPointSize(18);
        te->append(QString::number(time_to_next) + " Stunden");
        te->setFontPointSize(10);
        te->append("\nabgefragt.");
        return;
    }

    QString wordToShow;

    if(this->lang1) {
        wordToShow = this->pickRandom(this->currentWord->lang1);
    } else {
        wordToShow = this->pickRandom(this->currentWord->lang2);
    }

    this->currentStateLang1 = this->lang1;

    this->ui->le_question->setText(wordToShow);
    this->ui->le_info->setText("Phase " + QString::number(this->currentWord->getPhase()));
}

void Phase6_GUI::on_rb_lang1_clicked()
{
    this->lang1 = true;
}

void Phase6_GUI::on_rb_lang2_clicked()
{
    this->lang1 = false;
}

void Phase6_GUI::on_le_answer_returnPressed()
{
    if(this->currentWord == nullptr || this->ui->le_answer->text().toStdString() == "") {
        return;
    }

    this->ui->pb_edit->setDisabled(false);
    this->ui->pb_overview->setDisabled(false);

    QString enteredWord = this->ui->le_answer->text();
    std::vector<QString> right_answer;
    std::vector<QString> questioned_words;

    if(this->currentStateLang1) {
        right_answer = this->currentWord->lang2;
        questioned_words = this->currentWord->lang1;
    } else {
        right_answer = this->currentWord->lang1;
        questioned_words = this->currentWord->lang2;
    }

    bool answer = this->compare(enteredWord, right_answer);

    this->ui->le_answer->hide();
    this->ui->le_question->hide();

    QTextEdit* te = this->ui->te_solution;
    te->show();
    te->setFontPointSize(10);
    te->clear();
    te->setAlignment(Qt::AlignCenter);

    te->append("\n" + this->currentWord->toString() + "\n");

    te->setFontPointSize(17);

    if(answer) {
        int phase = this->currentWord->getPhase();
        phase = phase == 6? 6 : phase + 1;

        this->ui->le_info->setText("weiter nach Phase " + QString::number(phase));
        this->ui->te_solution->setStyleSheet("background-color:#aaff7f");

        te->append("Richtig!\n");
        te->setFontPointSize(10);


        te->append("Das Wort ist nun in Phase " + QString::number(phase) + ".");

        QString wait;
        switch(phase) {
        case 2:
            wait = "einem Tag";
            break;
        case 3:
            wait = "3 Tagen";
            break;
        case 4:
            wait = "9 Tagen";
            break;
        case 5:
            wait = "29 Tagen";
            break;
        case 6:
            wait = "90 Tagen";
            break;
        }

        te->append("Es wird in "+ wait + " erneut abgefragt.");

    } else {
        this->ui->le_info->setText("zurück in Phase 1");
        this->ui->te_solution->setStyleSheet("background-color:#ff5c5c");

        te->append("Falsch!");
        te->setFontPointSize(10);
        te->append("\nDeine Antwort: " + enteredWord);
        te->append("Richtige Antwort: " + Word::toString(right_answer));
        te->append("Das Wort ist nun wieder in Phase 1 und wird bald erneut abgefragt.");
    }
    this->vocab->giveAnswer(this->currentWord, answer);
}


void Phase6_GUI::on_pb_overview_clicked()
{
    this->dialog_overview = new Dialog_Overview(this);
    this->dialog_overview->show();
}
