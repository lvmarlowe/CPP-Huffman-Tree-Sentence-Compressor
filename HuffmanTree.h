/* LV Marlowe
SDEV-345: Data Structures & Algorithms
Week 10: Assignment
3 Nov 2024
This header file defines the template class for Huffman
Tree operations.
-------------------------------------------------- */

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <memory> // Provides smart pointers for automated memory management
#include <string>
#include <unordered_map> // Provides hash maps for efficient code lookup
#include <queue> // Provides priority queue for tree building
#include <stdexcept> // Provides exception handling for input validation

using namespace std;

template <typename T>
class HuffmanTree {
private:
    struct HuffmanNode {
        T data;
        int frequency;
        shared_ptr<HuffmanNode> left;
        shared_ptr<HuffmanNode> right;

        HuffmanNode(T data, int frequency)
            : data(data),
            frequency(frequency),
            left(nullptr),
            right(nullptr) {}
    };

    struct Compare {
        bool operator()(const shared_ptr<HuffmanNode>& left,
            const shared_ptr<HuffmanNode>& right) const {
            return left->frequency > right->frequency;
        }
    };

    shared_ptr<HuffmanNode> root;
    unordered_map<T, string> huffmanCodes;
    unordered_map<string, T> reverseHuffmanCodes;

    void buildCodes(shared_ptr<HuffmanNode> node, const string& code);
    void clearTree();

public:
    void buildTree(const string& text);
    string encode(const string& text);
    string decode(const string& binaryCode);
};

#endif // HUFFMANTREE_H