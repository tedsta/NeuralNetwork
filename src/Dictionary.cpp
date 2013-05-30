#include "Dictionary.h"

Dictionary::Dictionary()
{
    //ctor
}

Dictionary::~Dictionary()
{
    //dtor
}

Word *Dictionary::findWord(std::string name)
{
    for (WordIterator it = mWords.begin(); it != mWords.end(); it++)
    {
        if ((*it)->mName == name)
            return (*it);
    }

    return NULL;
}

Word *Dictionary::findWord(const float *code)
{
    for (WordIterator it = mWords.begin(); it != mWords.end(); it++)
    {
        if ((*it)->mCode == code)
            return (*it);
    }

    return NULL;
}
