#pragma once
#include <string>
#include <vector>
#include <QString>

class Word {
public :
    unsigned int id = 0;

    std::vector<QString> lang1;
    std::vector<QString> lang2;

	void setTime();
    void setTime(unsigned int time);
	void incPhase();
	void resetPhase();
	void setPhase(int phase);
    unsigned int getTime() const;
	int	getPhase() const;

    Word(std::vector<QString> lang1, std::vector<QString> lang2);

    QString toString();
    static QString toString(std::vector<QString> wordList);
private:
    unsigned int time = 0;
	int phase = 1;
};
