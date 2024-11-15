/* LV Marlowe
SDEV-345: Data Structures & Algorithms
Week 10: Assignment
3 Nov 2024
This implementation file contains the methods for the 
ProgramManager class. It requires ProgramManager.h to 
run.
-------------------------------------------------- */

#include "ProgramManager.h"
#include <algorithm> // Provides string manipulation functions

const string ProgramManager::BORDER(72, '-');

// Runs program loop until user chooses to exit, allowing multiple text 
// compressions in one session
ProgramManager::ProgramManager() {
    bool continueProcessing = true;
    bool firstRun = true;

    while (continueProcessing) {
        if (firstRun) {
            displayWelcome();
            firstRun = false;
        }
        getInputText();
        processText();
        displayResults();
        continueProcessing = getContinueDecision();
    }
    displayExit();
}

ProgramManager::~ProgramManager() {}

// Adds borders and spacing to display box
void ProgramManager::displayLine(const string& message) {
    string paddedMessage = " " + message;
    cout << "|" << setw(DISPLAY_WIDTH) << left << paddedMessage << "|" << endl;
}

// Breaks long text into smaller pieces that fit within display box width
void ProgramManager::displayLongLine(const string& message) {
    string remainingText = message;
    const size_t maxChars = 60;

    while (!remainingText.empty()) {
        string chunk = remainingText.substr(0, maxChars);
        displayLine(chunk);
        remainingText = remainingText.length() > maxChars ?
            remainingText.substr(maxChars) : "";
    }
}

// Creates boxed sections to separate different types of text in the display
void ProgramManager::displaySection(const string& header, const string& content) {
    cout << BORDER << endl;
    displayLine(header);
    cout << BORDER << endl;
    if (header == "Encoded Binary String") {
        displayLongLine(content);
    }
    else {
        displayLine(content);
    }
    cout << BORDER << endl << endl;
}

// Shows starting screen to explain what the program does
void ProgramManager::displayWelcome() {
    cout << BORDER << endl;
    displayLine("Welcome to Huffman Tree Text Processor!");
    displayLine("This program will encode and decode text using a Huffman tree.");
    displayLine("Please enter a sentence to process.");
    cout << BORDER << endl << endl;
}

// Gets the text that user wants to compress
void ProgramManager::getInputText() {
    cout << "Enter your text: ";
    getline(cin, inputText);
    cout << endl;
}

// Uses Huffman tree to compress and decompress the text, catching any errors
void ProgramManager::processText() {
    try {
        huffmanTree.buildTree(inputText);
        encodedText = huffmanTree.encode(inputText);
        decodedText = huffmanTree.decode(encodedText);
    }
    catch (const exception& e) {
        cout << "Error processing text: " << e.what() << endl;
        inputText = "";
        encodedText = "";
        decodedText = "";
    }
}

// Shows the original text, its compressed form, and the recovered text
void ProgramManager::displayResults() {
    if (inputText.empty()) return;

    displaySection("Original Text", inputText);
    displaySection("Encoded Binary String", encodedText);
    displaySection("Decoded Text", decodedText);
}

// Shows goodbye message when program finishes
void ProgramManager::displayExit() {
    cout << endl;
    cout << BORDER << endl;
    displayLine("Thank you for using Huffman Tree Text Processor!");
    displayLine("Goodbye!");
    cout << BORDER << endl;
}

// Checks if user wants to compress another piece of text
bool ProgramManager::getContinueDecision() {
    cout << "Would you like to process another sentence? (Y/N): ";
    char decision;
    cin >> decision;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (toupper(decision) == 'Y') {
        cout << endl;
    }
    return (toupper(decision) == 'Y');
}