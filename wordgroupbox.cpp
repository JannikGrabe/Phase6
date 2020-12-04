#include "wordgroupbox.h"

WordGroupBox::WordGroupBox(QWidget*)
{
    this->gb_word = new QGroupBox();
    this->gb_layout = new QHBoxLayout();

    this->vl_lang1_all = new QVBoxLayout();
    this->vl_lang2_all = new QVBoxLayout();
    this->vl_lang1 = new QVBoxLayout();
    this->vl_lang2 = new QVBoxLayout();

    this->hl_plus_lang1 = new QHBoxLayout();
    this->hl_plus_lang2 = new QHBoxLayout();

    this->pb_plus_lang1 = new QPushButton("+");
    this->pb_plus_lang2 = new QPushButton("+");

    this->le_lang1 = new QLineEdit();
    le_lang1->setAlignment(Qt::AlignCenter);
    QFont font("MS Shell Dlg 2", 10);
    le_lang1->setFont(font);

    this->le_lang2 = new QLineEdit();
    le_lang2->setAlignment(Qt::AlignCenter);
    le_lang2->setFont(font);

    this->vsp_top_lang1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->vsp_bottom_lang1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->vsp_top_lang2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->vsp_bottom_lang2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->hsp_left_lang1 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
    this->hsp_right_lang1 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
    this->hsp_left_lang2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
    this->hsp_right_lang2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

    // horizontal layout for buttons
    this->hl_plus_lang1->addSpacerItem(this->hsp_left_lang1);
    this->hl_plus_lang1->addWidget(this->pb_plus_lang1);
    this->hl_plus_lang1->addSpacerItem(this->hsp_right_lang1);

    this->hl_plus_lang2->addSpacerItem(this->hsp_left_lang2);
    this->hl_plus_lang2->addWidget(this->pb_plus_lang2);
    this->hl_plus_lang2->addSpacerItem(this->hsp_right_lang2);

    // vertical layout for line edits
    this->vl_lang1->addWidget(this->le_lang1);
    this->vl_lang2->addWidget(this->le_lang2);

    // vertical layout for all items for lang1/lang2
    this->vl_lang1_all->addSpacerItem(this->vsp_top_lang1);
    this->vl_lang1_all->addLayout(this->vl_lang1);
    this->vl_lang1_all->addLayout(this->hl_plus_lang1);
    this->vl_lang1_all->addSpacerItem(this->vsp_bottom_lang1);

    this->vl_lang2_all->addSpacerItem(this->vsp_top_lang2);
    this->vl_lang2_all->addLayout(this->vl_lang2);
    this->vl_lang2_all->addLayout(this->hl_plus_lang2);
    this->vl_lang2_all->addSpacerItem(this->vsp_bottom_lang2);

    // group box
    this->gb_layout->addLayout(this->vl_lang1_all);
    this->gb_layout->addLayout(this->vl_lang2_all);
    this->gb_word->setLayout(this->gb_layout);

    // Connects
    QObject::connect(this->pb_plus_lang1, &QPushButton::pressed, this, &WordGroupBox::on_pb_plus_lang1_clicked);
    QObject::connect(this->pb_plus_lang2, &QPushButton::pressed, this, &WordGroupBox::on_pb_plus_lang2_clicked);
}

WordGroupBox::~WordGroupBox() {
    delete this->gb_word;
}

QGroupBox *WordGroupBox::getGroupBox() const
{
    return this->gb_word;
}

Word* WordGroupBox::getWord()
{
    std::vector<QString> lang1_words;
    std::vector<QString> lang2_words;

    for(int i = 0; i < this->vl_lang1->count(); i++) {
        QLineEdit* le = dynamic_cast<QLineEdit*>(this->vl_lang1->itemAt(i)->widget());

        if(le == nullptr) {
            continue;
        }

        QString word = le->text();

        if(word == "") {
            continue;
        }

        lang1_words.push_back(word);
    }

    for(int i = 0; i < this->vl_lang2->count(); i++) {
        QLineEdit* le = dynamic_cast<QLineEdit*>(this->vl_lang2->itemAt(i)->widget());

        if(le == nullptr) {
            continue;
        }

        QString word = le->text();

        if(word == "") {
            continue;
        }

        lang2_words.push_back(word);
    }

    if(lang1_words.size() == 0 || lang2_words.size() == 0)
        return nullptr;

    return new Word(lang1_words, lang2_words);
}

void WordGroupBox::on_pb_plus_lang1_clicked()
{
    QLineEdit* le = new QLineEdit();
    le->setAlignment(Qt::AlignCenter);
    QFont font("MS Shell Dlg 2", 10);
    le->setFont(font);

    this->vl_lang1->addWidget(le);
    le->setFocus();
}

void WordGroupBox::on_pb_plus_lang2_clicked()
{
    QLineEdit* le = new QLineEdit();
    le->setAlignment(Qt::AlignCenter);
    QFont font("MS Shell Dlg 2", 10);
    le->setFont(font);

    this->vl_lang2->addWidget(le);
    le->setFocus();
}
