/*
 *  unit_test_p2.h
 *  Anh Hoang ahoang05
 *  2/10/2023
 *
 *  CS 15 proj3
 *
 *  Unit testing for PhaseTwo
 *
 */

#include "HuffmanTreeNode.h"
#include "HuffmanCoder.h"
#include "ZapUtil.h"
#include "BinaryIO.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <utility>
#include <cassert>

using namespace std;

// // Test buildHuffmanTree in banana_apple.txt
// void test_buildHuffmanTree() {
//     HuffmanCoder coder;
//     ifstream instream;
//     instream.open("banana_apple.txt");
//     coder.count_freqs(instream);
//     instream.close();
//     HuffmanTreeNode *root = coder.buildHuffmanTree();
//     printTree(root, '\0');
//     coder.deleteTree(root);
// }

// // Test buildHuffmanTree in banana_apple.txt
// void test_generateCode() {
//     HuffmanCoder coder;
//     ifstream instream;
//     instream.open("banana_apple.txt");
//     HuffmanTreeNode *root = coder.buildHuffmanTree();
//     coder.generateCode(root);

//     //Get an iterator pointing to the first element in the map
//     map<char, string>::iterator it = coder.charCode.begin();
//     //Iterate through the map and print the elements
//     while (it != coder.charCode.end()) {
//         cout << it->first << ": " << it->second << endl;
//         it++;
//     }
// }

// // Test decodeBinaryString with banana_apple.zap
// void test_decodeBinaryString() {
//     HuffmanCoder coder;
//     ifstream instream;
//     instream.open("banana_apple.zap");
//     BinaryIO binary;
//     pair<string, string> decoding = binary.readFile("banana_apple.zap");
//     string serialized_tree = decoding.first;
//     string binary_encoding = decoding.second;
//     HuffmanTreeNode *root = coder.deserialize_tree(serialized_tree);
//     string decoded_text = coder.decodeBinaryString(root, binary_encoding);
//     assert(decoded_text == "Apple apple.\nBanana?");
//     instream.close();
//     coder.deleteTree(root);
// }

// // Test count_freqs in banana.txt
// void test_count_freqs1() {
//     HuffmanCoder coder;
//     ifstream instream;
//     instream.open("banana.txt");
//     coder.count_freqs(instream);

//     // Get an iterator pointing to the first element in the map
//     map<char, int>::iterator it = coder.countLetterFreq.begin();

//     // Iterate through the map and print the elements
//     while (it != coder.countLetterFreq.end()) {
//         cout << it->first << ": " << it->second << endl;
//         it++;
//     }
// }

// // Test count_freqs in hi.txt
// void test_count_freqs2() {
//     HuffmanCoder coder;
//     ifstream instream;
//     instream.open("hi.txt");
//     coder.count_freqs(instream);

//     // Get an iterator pointing to the first element in the map
//     map<char, int>::iterator it = coder.countLetterFreq.begin();

//     // Iterate through the map and print the elements
//     while (it != coder.countLetterFreq.end()) {
//         cout << it->first << ": " << it->second << endl;
//         it++;
//     }
// }

// // Test count_freqs in banana_apple.txt
// void test_count_freqs3() {
//     HuffmanCoder coder;
//     ifstream instream;
//     instream.open("banana_apple.txt");
//     coder.count_freqs(instream);

//     // Get an iterator pointing to the first element in the map
//     map<char, int>::iterator it = coder.countLetterFreq.begin();

//     // Iterate through the map and print the elements
//     while (it != coder.countLetterFreq.end()) {
//         cout << it->first << ": " << it->second << endl;
//         it++;
//     }
// }

// // Test count_freqs in test_text.txt
// void test_count_freqs4() {
//     HuffmanCoder coder;
//     ifstream instream;
//     instream.open("test_text.txt");
//     coder.count_freqs(instream);

//     // Get an iterator pointing to the first element in the map
//     map<char, int>::iterator it = coder.countLetterFreq.begin();

//     // Iterate through the map and print the elements
//     while (it != coder.countLetterFreq.end()) {
//         cout << it->first << ": " << it->second << endl;
//         it++;
//     }
// }

// // Test serialize_tree in a single-node tree
// void test_serialize_tree1() {
//     HuffmanCoder coder;
//     HuffmanTreeNode test_tree('a',3);
//     string serialized_tree = coder.serialize_tree(&test_tree);
//     assert(serialized_tree == "La");
// }

// // Test serialize_tree in a 2-leaf tree
// void test_serialize_tree2() {
//     HuffmanCoder coder;
//     HuffmanTreeNode leaf1('b',4);
//     HuffmanTreeNode leaf2('c', 7);
//     HuffmanTreeNode test_tree('a',3, &leaf1, &leaf2);
//     string serialized_tree = coder.serialize_tree(&test_tree);
//     assert(serialized_tree == "ILbLc");
// }

// // Test serialize_tree in a 4-leaf tree
// void test_serialize_tree3() {
//     HuffmanCoder coder;
//     HuffmanTreeNode hehe1('b',4);
//     HuffmanTreeNode hehe2('c', 7);
//     HuffmanTreeNode hihi1('o', 8);
//     HuffmanTreeNode hihi2('m', 3);
//     HuffmanTreeNode test_tree1('a', 3, &hehe1, &hehe2);
//     HuffmanTreeNode test_tree2('o', 8, &hihi1, &hihi2);
//     HuffmanTreeNode test_tree3('m', 3, &test_tree1, &test_tree2);
//     string serialized_tree = coder.serialize_tree(&test_tree3);
//     assert(serialized_tree == "IILbLcILoLm");
// }

// // Test deserialize_tree in the string generated in test_serialize_tree3()
// void test_deserialize_tree1() {
//     HuffmanCoder coder;
//     string serial_tree = "IILbLcILoLm";
//     HuffmanTreeNode *root = coder.deserialize_tree(serial_tree);
//     printTree(root, '\0');
//     coder.deleteTree(root);
// }

// // Test deserialize_tree by comparing the Figure 1 tree with the deserialized
// // tree from the Figure 1 serial tree
// void test_deserialize_tree2() {
//     HuffmanCoder coder;
//     string serial_tree = "IIILaLbILeLfILcLd";
//     HuffmanTreeNode *root = coder.deserialize_tree(serial_tree);
//     printTree(root, '\0');
//     // Calling makeFigure1Tree() reports memory leak so I commented it out
//     // assert(treeEquals(makeFigure1Tree('\0'), root, false) == true);
//     coder.deleteTree(root);
// }
