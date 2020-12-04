#include "Word.h"
#include <chrono>

void Word::setTime() {
    this->time = std::chrono::duration_cast<std::chrono::hours>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Word::setTime(unsigned int time)
{
    this->time = time;
}

void Word::incPhase()
{
	if (this->phase < 6) {
		this->phase++;
	}
}

void Word::resetPhase()
{
	this->phase = 1;
}

void Word::setPhase(int phase)
{
	if (phase > 0 && phase < 7)
		this->phase = phase;
}

unsigned int Word::getTime() const
{
	return this->time;
}

int Word::getPhase() const
{
	return this->phase;
}

Word::Word(std::vector<QString> lang1, std::vector<QString> lang2) : lang1(lang1), lang2(lang2)
{
}

bool Word::compare(QString text, bool case_sensitiv, bool partial) {

    for(QString word : this->lang1) {
        if(partial) {
            if(case_sensitiv && word.contains(text, Qt::CaseSensitive)) {
                return true;
            } else if (word.contains(text, Qt::CaseInsensitive)) {
                return true;
            }
        } else if(case_sensitiv && word.compare(text, Qt::CaseSensitive) == 0) {
            return true;
        } else if(word.compare(text, Qt::CaseInsensitive) == 0) {
            return true;
        }
    }

    for(QString word : this->lang2) {
        if(partial) {
            if(case_sensitiv && word.contains(text, Qt::CaseSensitive)) {
                return true;
            } else if (word.contains(text, Qt::CaseInsensitive)) {
                return true;
            }
        } else if(case_sensitiv && word.compare(text, Qt::CaseSensitive) == 0) {
            return true;
        } else if(word.compare(text, Qt::CaseInsensitive) == 0) {
            return true;
        }
    }
    return false;
}

QString Word::toString(std::vector<QString> wordList)
{
    QString s = "";

    for(unsigned int i = 0; i < wordList.size(); i++) {
        s += wordList[i];
        if(i + 1 != wordList.size()) {
            s += ", ";
        }
    }

    return s;
}

QString Word::toString()
{
    return toString(this->lang1) + " - " + toString(this->lang2);
}
