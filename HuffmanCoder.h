/*
 * HuffmanCoder.h
 * Anh Hoang ahoang05
 * 3/7/2022
 * COMP 15 Project 3
 * zap
 *
 * Define the interface of the HuffmanCoder class, which comprises the main
 * logic of the Huffman coding algorithm.
 *
 */

#ifndef HUFFMAN_CODER
#define HUFFMAN_CODER

#include "HuffmanTreeNode.h"
#include <string>
#include <map>

class HuffmanCoder
{
public:
    void encoder(const std::string &input_file, const std::string &output_file);
    void decoder(const std::string &input_file, const std::string &output_file);

    // // Functions to make temporarily public
    // HuffmanTreeNode *buildHuffmanTree();
    // void count_freqs(std::istream &text);
    // std::map<char, int> countLetterFreq;
    // std::map<char, std::string> charCode;
    // void deleteTree(HuffmanTreeNode *curr);
    // std::string serialize_tree(HuffmanTreeNode *root);
    // HuffmanTreeNode *deserialize_tree(std::string serial_tree);
    // void generateCode(HuffmanTreeNode *root);
    // std::string decodeBinaryString(HuffmanTreeNode *root,
    //                                std::string binary_encoding);
private:
    template <typename streamtype>
    void openFile(streamtype &stream, std::string file_name);
    std::map<char, int> countLetterFreq;
    std::map<char, std::string> charCode;
    HuffmanTreeNode *buildHuffmanTree();
    void count_freqs(std::istream &text);
    std::string serialize_tree(HuffmanTreeNode *root);
    std::string traverse_tree(HuffmanTreeNode *curr, std::string &tree);
    HuffmanTreeNode *deserialize_tree(std::string serial_tree);
    HuffmanTreeNode *deserialize_tree_helper(std::string tree, int index,
                                             HuffmanTreeNode *hehe);
    void generateCode(HuffmanTreeNode *root);
    void generateCodeHelper(HuffmanTreeNode *curr, std::string code);
    std::string encodeText(std::istream &text);
    std::string decodeBinaryString(HuffmanTreeNode *root,
                                   std::string binary_encoding);
    void deleteTree(HuffmanTreeNode *curr);
};

#endif