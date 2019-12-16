#include "Vocabulary.h"
#include "Phase6_GUI.h"

#include <chrono>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QMessageBox>

//if time is expired add word ready

void Vocabulary::updateReady() {
    unsigned int now = std::chrono::duration_cast<std::chrono::hours>(std::chrono::system_clock::now().time_since_epoch()).count();
	this->ready.clear();

    for (unsigned int i = 0; i < this->vocabulary.size(); i++) {
		Word* word = vocabulary[i];

		bool add = false;
		switch (word->getPhase()) {
		case 1:
			add = true;
            break;
		case 2:
			// 1 day wait = 24h
			if (now - word->getTime() >= 24) {
				add = true;
			}
				
			break;
		case 3:
			// 3 days wait = 72h
			if (now - word->getTime() >= 72) {
				add = true;
			}
			break;
		case 4:
			// 9 days wait = 216h
			if (now - word->getTime() >= 216) {
				add = true;
			}
			break;
		case 5:
			// 29 days wait = 696h
			if (now - word->getTime() >= 696) {
				add = true;
			}
			break;
		case 6:
            // 90 days wait = 2160h
            if (now - word->getTime() >= 2160) {
				add = true;
			}
			break;
		}

		if (add) {
			this->ready.push_back(word);
		}
	}
}

// reads words from file "vocab.voc" and adds to vocab

bool Vocabulary::readVocabFromFile() {

    QString path = QCoreApplication::applicationDirPath();
    QFile* file = new QFile(path + "/vocab.voc");

    if (!file->open(QFile::ReadOnly)) return false;

    try {
        QTextStream in(file);
        in.setCodec("UTF-16");

        while (!in.atEnd()) {

            QString line = in.readLine();
            QStringList fields = line.split(";");

            QStringList lang1 = fields[0].split(":", QString::SkipEmptyParts);
            QStringList lang2 = fields[1].split(":", QString::SkipEmptyParts);

            Word* word = new Word(lang1.toVector().toStdVector(), lang2.toVector().toStdVector());
            word->setPhase(fields[2].toInt());
            word->setTime(fields[3].toUInt());

            this->vocabulary.push_back(word);
        }

        file->close();

    } catch (std::exception e) {
        return false;
    }

	return true;
}

// writes vocab to file "vocab.voc":
// sprache1 sprache2 phase time \n

bool Vocabulary::writeVocabToFile() {

    QString path = QCoreApplication::applicationDirPath();
    QFile* file = new QFile(path + "/vocab.voc");

    if (!file->open(QFile::WriteOnly))
		return false;

    QTextStream out(file);
    out.setCodec("UTF-16");

    for (unsigned int i = 0; i < vocabulary.size(); i++) {
        foreach(QString s, vocabulary[i]->lang1) {
            out << s << ":";
        }
        out << ";";
        foreach(QString s, vocabulary[i]->lang2) {
            out << s << ":";
        }
        out << ";";
        out << vocabulary[i]->getPhase() << ";";
        out << vocabulary[i]->getTime();
		if (i + 1 != vocabulary.size())
            out << "\n";
        out.flush();
	}
    file->close();
    return true;
}

// choose a word from the ready list randomly

Word * Vocabulary::randomlyChooseWord() {
    unsigned int size = this->ready.size();

	if (size == 0) {
		return nullptr;
	}

    std::uniform_int_distribution<unsigned int> distribution(0, size - 1 );

    return ready[distribution(generator)];
}

Vocabulary::Vocabulary(Phase6_GUI * gui) {
	this->gui = gui;

	// init vocab and ready
    this->readVocabFromFile();

    this->generator.seed(time(0));
}


// add word to vocab and ready

void Vocabulary::addWord(std::vector<QString> lang1, std::vector<QString> lang2) {
    Word* word = new Word(lang1, lang2);
	this->vocabulary.push_back(word);
}

void Vocabulary::deleteWord(Word *word) {
    std::vector<Word*>::iterator position = std::find(this->vocabulary.begin(), this->vocabulary.end(), word);
    if (position != this->vocabulary.end()) // == myVector.end() means the element was not found
        this->vocabulary.erase(position);
}

// pick and remove one word from ready
// update phase according to answer

Word* Vocabulary::drawWord() {
    this->updateReady();

    Word* word = this->randomlyChooseWord();

    if (word == nullptr) {
        return nullptr;
    }
    return word;
}

void Vocabulary::giveAnswer(Word* word, bool answer) {
    if (answer) {
        word->incPhase();
        word->setTime();
    }
    else {
        word->resetPhase();
    }
}

// done studying

void Vocabulary::finish() {
    this->writeVocabToFile();
}

int Vocabulary::getTimeUntilNext()
{
    unsigned int now = std::chrono::duration_cast<std::chrono::hours>(std::chrono::system_clock::now().time_since_epoch()).count();
    int minTime = 2160;

    foreach(Word* word, this->vocabulary) {
        int waitTime = getHoursOfPhase(word->getPhase());
        int time_passed = now - word->getTime();

        int time_to_wait = waitTime - time_passed;

        if(time_to_wait < minTime)
            minTime = time_to_wait;
    }

    return minTime;
}

bool Vocabulary::isEmpty()
{
    return this->vocabulary.size() == 0;
}

std::vector<const Word *> Vocabulary::getVocabulary() const
{
    std::vector<const Word*> constVocab;

    foreach(Word * word, this->vocabulary) {
        constVocab.push_back(dynamic_cast<const Word*>(word));
    }

    return constVocab;
}

int Vocabulary::getHoursOfPhase(int phase)
{
    switch(phase) {
    case 1:
        return 0;
    case 2:
        return 24;
    case 3:
        return 72;
    case 4:
        return 216;
    case 5:
        return 696;
    case 6:
        return 2160;
    }

    return 0;
}
