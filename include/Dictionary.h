#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <cstddef>
#include <vector>
#include <string>

struct Word
{
    /// The actual name of this word.
    std::string mName;

    /// The array that encodes this word.
    float mCode[16];
};

class Dictionary
{
    public:
        Dictionary();
        virtual ~Dictionary();

        /// \brief Adds a new word to the dictionary.
        /// \param word The word to add to the dictionary.
        void addWord(Word *word){mWords.push_back(word);}

        /// \brief Finds a word based on its name.
        /// \return The word with the name supplied
        Word *findWord(std::string name);

        /// \brief Find the word whose code most closely matches the code supplied
        /// \return The word whose code most closely matches the code supplied
        Word *findWord(const float *code);

    private:
        /// All of the words this dictionary contains
        std::vector <Word*> mWords;

        typedef std::vector<Word*>::iterator WordIterator;
};

#endif // DICTIONARY_H
