/* LV Marlowe
SDEV-345: Data Structures & Algorithms
Week 10: Assignment
3 Nov 2024
This implementation file contains the methods for 
the HuffmanTree template class. It requires 
HuffmanTree.h to run. It is based on code from
https://www.geeksforgeeks.org/huffman-coding-in-cpp/ .
-------------------------------------------------- */

#include "HuffmanTree.h"

// Creates unique binary codes for each character by walking through the tree. 
// Uses 0 for left paths and 1 for right paths so common characters get shorter codes
template <typename T>
void HuffmanTree<T>::buildCodes(shared_ptr<HuffmanNode> node, const string& code) {
    if (!node) return;

    if (!node->left && !node->right) {
        huffmanCodes[node->data] = code;
        reverseHuffmanCodes[code] = node->data;
        return;
    }

    buildCodes(node->left, code + "0");
    buildCodes(node->right, code + "1");
}

// Cleans up old data before processing new text
template <typename T>
void HuffmanTree<T>::clearTree() {
    root.reset();
    huffmanCodes.clear();
    reverseHuffmanCodes.clear();
}

// Builds a tree where frequently used characters are placed closer to the top, 
// which makes the compressed text smaller because common characters get shorter codes
template <typename T>
void HuffmanTree<T>::buildTree(const string& text) {
    clearTree();

    unordered_map<T, int> frequencyMap;
    for (const auto& ch : text) {
        frequencyMap[ch]++;
    }

    priority_queue<shared_ptr<HuffmanNode>,
        vector<shared_ptr<HuffmanNode>>,
        Compare> priorityQueue;

    for (const auto& pair : frequencyMap) {
        priorityQueue.push(make_shared<HuffmanNode>(pair.first, pair.second));
    }

    while (priorityQueue.size() > 1) {
        auto leftNode = priorityQueue.top();
        priorityQueue.pop();
        auto rightNode = priorityQueue.top();
        priorityQueue.pop();

        auto parentNode = make_shared<HuffmanNode>(T{},
            leftNode->frequency + rightNode->frequency);
        parentNode->left = leftNode;
        parentNode->right = rightNode;
        priorityQueue.push(parentNode);
    }

    if (!priorityQueue.empty()) {
        root = priorityQueue.top();
        buildCodes(root, "");
    }
}

// Compresses text by replacing each character with its binary code from the tree
template <typename T>
string HuffmanTree<T>::encode(const string& text) {
    string encodedText;

    for (const auto& ch : text) {
        encodedText += huffmanCodes[ch];
    }

    return encodedText;
}

// Uncompresses text by following the 0s and 1s through the tree until reaching a 
// character, then starting over at the top for the next character
template <typename T>
string HuffmanTree<T>::decode(const string& binaryCode) {
    if (!root || binaryCode.empty()) {
        return "";
    }

    string decodedText;
    auto currentNode = root;

    for (const char bit : binaryCode) {
        currentNode = (bit == '0') ? currentNode->left : currentNode->right;

        if (!currentNode->left && !currentNode->right) {
            decodedText += currentNode->data;
            currentNode = root;
        }
    }

    return decodedText;
}

template class HuffmanTree<char>;