#pragma once
#include "Word.h"
#include <vector>
#include <random>
#include <QDomDocument>

class Phase6_GUI;

// class that contains all the words
class Vocabulary {

private:
	std::vector<Word*> vocabulary;
	std::vector<Word*> ready;
    unsigned int current_id = 0;
    QDomDocument doc;

    std::vector<int> words_per_phase;

	Phase6_GUI* gui = nullptr;

    std::random_device dev;
    std::mt19937 generator;

	//if time is expired add word ready
	void updateReady();

	// reads words from file "vocab.voc" and adds to vocab
	bool readVocabFromFile();

     bool readVocabFromFileXML();

	// writes vocab to file "vocab.voc":
	// sprache1 sprache2 phase time ready \n
	bool writeVocabToFile();

     bool writeVocabToFileXML();

	// choose a word from the ready list randomly
	Word* randomlyChooseWord();


    bool writeDomDocumentToFile();
    QDomElement createXMLWordElement(Word *word);
public:
	Vocabulary(Phase6_GUI* gui);

	// add word to vocab and ready
    void addWord(std::vector<QString> lang1, std::vector<QString> lang2);
    void addWord(Word *word);

    // edit word
    void editWord(Word* word, std::vector<QString> lang1, std::vector<QString> lang2);

	// delete worb from vocab and ready
    void deleteWord(Word* word);

	// pick and remove one word from ready
    Word* drawWord();

    std::vector<Word *> find(QString text, bool case_sensitive = true, bool partial = false);

    Word* find(int id) {
        for(Word* word : this->vocabulary) {
            if(word->id == id) {
                return word;
            }
        }

        return nullptr;
    }

    // receives the answer from the gui
    void giveAnswer(Word* word, bool answer);

	// done studying
	void finish();

    int getTimeUntilNext();

    const std::vector<int> get_words_per_phase();

    bool isEmpty();

    std::vector<Word *> getVocabulary();

    static int getHoursOfPhase(int phase);

};
