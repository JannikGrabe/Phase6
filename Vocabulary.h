#pragma once
#include "Word.h"
#include <vector>
#include <random>

/* TO DO:
	- FileErrorException 
	done - add Time
	done - impl updateReady
	done - impl readToFile
	done - impl writeToFile
*/

class Phase6_GUI;

// class that contains all the words
class Vocabulary {

private:
	std::vector<Word*> vocabulary;
	std::vector<Word*> ready;

	Phase6_GUI* gui = nullptr;

    std::random_device dev;
    std::mt19937 generator;

    bool file_read = false;

	//if time is expired add word ready
	void updateReady();

	// reads words from file "vocab.voc" and adds to vocab
	bool readVocabFromFile();

	// writes vocab to file "vocab.voc":
	// sprache1 sprache2 phase time ready \n
	bool writeVocabToFile();

	// choose a word from the ready list randomly
	Word* randomlyChooseWord();

public:
	Vocabulary(Phase6_GUI* gui);

	// add word to vocab and ready
    void addWord(std::vector<QString> lang1, std::vector<QString> lang2);

	// delete worb from vocab and ready
    void deleteWord(Word* word);

	// pick and remove one word from ready
    Word* drawWord();

    // receives the answer from the gui
    void giveAnswer(Word* word, bool answer);

	// done studying
	void finish();

    int getTimeUntilNext();

    bool isEmpty();

    std::vector<const Word *> getVocabulary() const;

    static int getHoursOfPhase(int phase);
};
