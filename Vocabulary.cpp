#include "Vocabulary.h"
#include "Phase6_GUI.h"

#include <chrono>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QMessageBox>
#include <QDir>
#include <QXmlStreamWriter>

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

    QString dir_path = QCoreApplication::applicationDirPath();
    QDir dir(dir_path);
    QString path = dir.relativeFilePath("../vocab.voc");
    QFile* file = new QFile(path);

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

bool Vocabulary::readVocabFromFileXML() {
    QString dir_path = QCoreApplication::applicationDirPath();
    QDir dir(dir_path);
    QString path = dir.relativeFilePath("../vocab.xml");

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this->gui,
            "Load XML File Problem",
            "Couldn't load the vocabulary",
            QMessageBox::Ok);
        return false;
    }

   if (!doc.setContent(&file)) {
       QMessageBox::warning(this->gui,
           "Parsing Problem",
           "Couldn't read the vocabulary file",
           QMessageBox::Ok);
       return false;
   }

   file.close();

   QDomNode root = doc.namedItem("Vocabulary");
   QDomNodeList wordElements = root.childNodes();


   for(int i = 0; i < wordElements.count(); i++) {

       QDomNode wordElement = wordElements.at(i);

       QDomNodeList langElements = wordElement.childNodes();

       std::vector<QString> lang1;
       std::vector<QString> lang2;
       for(int j = 0; j < langElements.count(); j++) {
           QDomElement elem = langElements.at(j).toElement();
           if(elem.tagName() == "lang1") {
               lang1.push_back(elem.text());
           }
           if(elem.tagName() == "lang2") {
               lang2.push_back(elem.text());
           }
       }

       Word* word = new Word(lang1, lang2);
       word->id = wordElement.attributes().namedItem("id").nodeValue().toUInt();
       word->setTime(wordElement.attributes().namedItem("time").nodeValue().toUInt());
       word->setPhase(wordElement.attributes().namedItem("phase").nodeValue().toInt());
       this->vocabulary.push_back(word);
       this->current_id = i;
   }

   this->current_id++;
   return true;
}


// writes vocab to file "vocab.voc":
// sprache1 sprache2 phase time \n

bool Vocabulary::writeVocabToFile() {

    QString dir_path = QCoreApplication::applicationDirPath();
    QDir dir(dir_path);
    QString path = dir.relativeFilePath("../vocab.voc");
    QFile* file = new QFile(path);

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

bool Vocabulary::writeVocabToFileXML() {
    // open normal file
    QString dir_path = QCoreApplication::applicationDirPath();
    QDir dir(dir_path);
    QString path = dir.relativeFilePath("../vocab.xml");
    QFile file(path);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("Vocabulary");
    for(unsigned int i = 0; i < this->vocabulary.size(); i++) {
        xml.writeStartElement("word");
        xml.writeAttribute("id", QString::number(i));
        xml.writeAttribute("phase", QString::number(this->vocabulary[i]->getPhase()));
        xml.writeAttribute("time", QString::number(this->vocabulary[i]->getTime()));

        for(unsigned int j = 0; j < this->vocabulary[i]->lang1.size(); j++) {
            xml.writeTextElement("lang1",  this->vocabulary[i]->lang1[j]);
        }

        for(unsigned int j = 0; j < this->vocabulary[i]->lang2.size(); j++) {
            xml.writeTextElement("lang2",  this->vocabulary[i]->lang2[j]);
        }

        xml.writeEndElement();
    }

    xml.writeEndElement();

    xml.writeEndDocument();

    file.close();
    return true;
}

bool Vocabulary::writeDomDocumentToFile() {
    QString dir_path = QCoreApplication::applicationDirPath();
    QDir dir(dir_path);
    QString path = dir.relativeFilePath("../vocab.xml");
    QFile file(path);

    // Save content back to the file
    if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        QMessageBox::warning(this->gui,
            "Writing Problem",
            "Couldn't write Vocabulary to file",
            QMessageBox::Ok);
        return false;
    }

    QByteArray xml = this->doc.toByteArray();
    file.write(xml);
    file.close();

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
    this->readVocabFromFileXML();

    this->generator.seed(time(0));
}


// add word to vocab and ready

void Vocabulary::addWord(std::vector<QString> lang1, std::vector<QString> lang2) {
    Word* word = new Word(lang1, lang2);
    word->id = this->current_id;
    this->vocabulary.push_back(word);

    QDomNode root = doc.namedItem("Vocabulary");

    QDomElement wordElement = this->doc.createElement("word");
    wordElement.setAttributeNode(doc.createAttribute("id"));
    wordElement.setAttributeNode(doc.createAttribute("time"));
    wordElement.setAttributeNode(doc.createAttribute("phase"));

    wordElement.setAttribute("id", QString::number(this->current_id));
    wordElement.setAttribute("time", QString::number(0));
    wordElement.setAttribute("phase", QString::number(1));

    for(int i = 0; i < lang1.size(); i++) {
        QDomElement langElement = this->doc.createElement("lang1");
        langElement.setNodeValue(lang1[i]);
        wordElement.appendChild(langElement);
    }

    for(int i = 0; i < lang1.size(); i++) {
        QDomElement langElement = this->doc.createElement("lang2");
        langElement.setNodeValue(lang2[i]);
        wordElement.appendChild(langElement);
    }

    current_id++;
}

void Vocabulary::editWord(Word* word, std::vector<QString> lang1, std::vector<QString> lang2)
{
    word->lang1 = lang1;
    word->lang2 = lang2;
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
    this->writeVocabToFileXML();
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
