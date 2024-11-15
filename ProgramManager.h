/* LV Marlowe
SDEV-345: Data Structures & Algorithms
Week 10: Assignment
3 Nov 2024
This header file defines the ProgramManager class 
which handles all program operations and user interaction.
-------------------------------------------------- */

#ifndef PROGRAMMANAGER_H
#define PROGRAMMANAGER_H

#include "HuffmanTree.h"
#include <iostream>
#include <iomanip> // Provides text formatting for display
#include <string>
#include <vector>
#include <limits> // Provides input stream clearing

using namespace std;

class ProgramManager {
private:
    HuffmanTree<char> huffmanTree;
    string inputText;
    string encodedText;
    string decodedText;
    static const string BORDER;
    static const int DISPLAY_WIDTH = 72;

    void displayLine(const string& message);
    void displayLongLine(const string& message);
    void displaySection(const string& header, const string& content);
    void displayWelcome();
    void displayResults();
    void displayExit();

    void getInputText();
    void processText();
    bool getContinueDecision();

public:
    ProgramManager();
    ~ProgramManager();
};

#endif // PROGRAMMANAGER_H