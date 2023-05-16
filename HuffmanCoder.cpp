/*
 * HuffmanCoder.cpp
 * Anh Hoang ahoang05
 * 3/7/2022
 * COMP 15 Project 3
 * zap
 *
 *
 * Define the implementation of the HuffmanCoder class, which comprises the
 * main logic of the Huffman coding algorithm.
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

using namespace std;

/*
 * encoder()
 * Purpose: encode a given ASCII text file into compressed binary code
 * Parameters: a reference to input_file and output_file strings
 * Returns: none
 * Effects: encode the ASCII text file, write the encoded text into a new file,
 *          and print out the size of the encoded text.
 */
void HuffmanCoder::encoder(const std::string &input_file,
                           const std::string &output_file)
{
     ifstream instream;
     instream.open(input_file);
     if (not instream.is_open())
     {
          throw runtime_error("Unable to open file " + input_file);
          instream.close();
     }
     count_freqs(instream);
     instream.close();
     HuffmanTreeNode *root = buildHuffmanTree();
     generateCode(root);

     openFile(instream, input_file);
     string encoded_text = encodeText(instream);
     string serial_tree = serialize_tree(root);
     BinaryIO binary;
     binary.writeFile(output_file, serial_tree, encoded_text);

     cout << "Success! Encoded given text using ";
     cout << encoded_text.size() << " bits.\n";
     instream.close();
     deleteTree(root);
}

/*
 * openFile()
 * Purpose: open filestream
 * Arguments: streamtype &stream, string file_name
 * Returns: none
 * Effects: throw runtime_error if fail to open file
 */
template <typename streamtype>
void HuffmanCoder::openFile(streamtype &stream, string file_name)
{
     stream.open(file_name);
     if (not stream.is_open())
     {
          throw std::runtime_error("Unable to open file " + file_name);
     }
}

/*
 * decoder()
 * Purpose:  take the compressed binary code and turns it back into text.
 * Parameters: string &input_file, string &output_file
 * Returns: none
 * Effects: decode the zap file and write the decoded text into a new .txt file
 */
void HuffmanCoder::decoder(const std::string &input_file,
                           const std::string &output_file)
{
     ifstream instream;
     openFile(instream, input_file);

     BinaryIO binary;
     pair<string, string> decoding = binary.readFile(input_file);
     string serialized_tree = decoding.first;
     string binary_encoding = decoding.second;
     HuffmanTreeNode *root = deserialize_tree(serialized_tree);
     string decoded_text = decodeBinaryString(root, binary_encoding);
     ofstream outstream;
     openFile(outstream, output_file);
     outstream << decoded_text;
     instream.close();
     outstream.close();
     deleteTree(root);
}

/*
 * decodeBinaryString()
 * Purpose: decode the encoded binary string
 * Parameters: pointer to the root of a HuffmanTree, a binary code string
 * Returns: the decoded text string
 * Effects: throw runtime error if encoding does not match Huffman tree
 */
string HuffmanCoder::decodeBinaryString(HuffmanTreeNode *root,
                                        string binary_encoding)
{
     string decoded_text = "";
     HuffmanTreeNode *curr = root;
     for (int i = 0; i < (int)binary_encoding.size(); i++)
     {
          if (curr == nullptr)
          {
               return "";
          }
          if (binary_encoding[i] == '0')
          {
               curr = curr->get_left();
          }
          else if (binary_encoding[i] == '1')
          {
               curr = curr->get_right();
          }
          if (curr->isLeaf())
          {
               decoded_text += curr->get_val();
               curr = root;
          }
     }
     if (curr != root)
     {
          throw runtime_error("Encoding did not match Huffman tree.");
     }
     return decoded_text;
}

/*
 * encodeText()
 * Purpose: encode the given text into binary
 * Parameters: reference to given text
 * Returns: encoded string
 * Effects: iterate over the original text, look up each character’s code, and
 *          append that code to the final encoded binary string
 */
string HuffmanCoder::encodeText(std::istream &text)
{
     char c;
     string encoded_text = "";
     // Read in stream from file (use the get() function)
     while (text.get(c))
     {
          encoded_text += charCode[c];
     }
     return encoded_text;
}

/*
 * buildHuffmanTree()
 * Purpose: build the Huffman code binary tree
 * Parameters: none
 * Returns: A pointer to HuffmanTreeNode class
 * Effects: none
 */
HuffmanTreeNode *HuffmanCoder::buildHuffmanTree()
{
     priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>,
                    NodeComparator>
         my_pq;
     map<char, int>::iterator it = countLetterFreq.begin();

     // create new HuffmanTreeNodes according to the letter frequency and push
     // them onto the priority queue
     while (it != countLetterFreq.end())
     {
          char letter = it->first;
          int freq = it->second;
          HuffmanTreeNode *node = new HuffmanTreeNode(letter, freq);
          my_pq.push(node);
          it++;
     }
     if (my_pq.size() == 0)
     {
          return nullptr;
     }

     // pop queue members to create the HuffmanTree
     while (my_pq.size() > 1)
     {
          HuffmanTreeNode *left = my_pq.top();
          my_pq.pop();
          HuffmanTreeNode *right = my_pq.top();
          my_pq.pop();
          int tempFreq = left->get_freq() + right->get_freq();
          HuffmanTreeNode *temp = new HuffmanTreeNode('\0', tempFreq, left, 
                                                      right);
          my_pq.push(temp);
     }
     HuffmanTreeNode *root = my_pq.top();
     my_pq.pop();
     return root;
}

/*
 * generateCode()
 * Purpose: generate the binary codes for each character
 * Parameters: A pointer to the root of a HuffmanTreeNode
 * Returns: none
 * Effects: none
 */
void HuffmanCoder::generateCode(HuffmanTreeNode *root)
{
     string code = "";
     if (root == nullptr)
     {
          return;
     }
     if (root->isLeaf())
     {
          charCode[root->get_val()] = "0";
     }
     generateCodeHelper(root, code);
}

/*
 * generateCodeHelper()
 * Purpose: helper function for generateCode()
 * Parameters: A pointer to a HuffmanTreeNode's root, a character code string
 * Returns: none
 * Effects: none
 */
void HuffmanCoder::generateCodeHelper(HuffmanTreeNode *curr, string code)
{
     if (curr->isLeaf())
     {
          charCode[curr->get_val()] += code;
     }
     else
     {
          string left = code + "0";
          generateCodeHelper(curr->get_left(), left);
          string right = code + "1";
          generateCodeHelper(curr->get_right(), right);
     }
}

/*
 * deleteTree()
 * Purpose: recursive function to delete tree memory
 * Parameters: A pointer to a HuffmanTreeNode's
 * Returns: none
 * Effects: tree memory deleted
 */
void HuffmanCoder::deleteTree(HuffmanTreeNode *curr)
{
     if (curr)
     {
          deleteTree(curr->get_left());
          deleteTree(curr->get_right());
          delete curr;
     }
}

/*
 * count_freqs()
 * Purpose: count frequencies of characters
 * Parameters: a reference to the text from istream
 * Returns: none
 * Effects: print out the frequencies of characters
 */
void HuffmanCoder::count_freqs(std::istream &text)
{
     char c;
     // Read in stream from file (use the get() function)
     while (text.get(c))
     {
          countLetterFreq[c]++;
     }
}

/*
 * serialize_tree()
 * Purpose: serialize andsave the tree in a file such that it can later be
 *          reconstructed as a string.
 * Parameters: a pointer to the HuffmanTreeNode's root
 * Returns: a serialized version of the tree
 * Effects: generate a serialized string of a tree
 */
std::string HuffmanCoder::serialize_tree(HuffmanTreeNode *root)
{
     string tree;
     if (root == nullptr)
     {
          return "";
     }
     return traverse_tree(root, tree);
}

/*
 * traverse_tree()
 * Purpose: recursive helper function for serialize_tree()
 * Parameters: HuffmanTreeNode *curr, string &tree
 * Returns: a serialized version of the tree
 * Effects: none
 */
std::string HuffmanCoder::traverse_tree(HuffmanTreeNode *curr, string &tree)
{
     if (curr->isLeaf())
     {
          char leaf = curr->get_val();
          tree += "L" + string(1, leaf); // convert char to string
     }
     else
     {
          tree += "I";
          traverse_tree(curr->get_left(), tree);
          traverse_tree(curr->get_right(), tree);
     }
     return tree;
}

/*
 * deserialize_tree()
 * Purpose: deserialize the tree, convert it from its serialized string format
 *          back into a tree data structure composed of HuffmanTreeNodes.
 * Parameters: the serial_tree string
 * Returns: a pointer to HuffmanTreeNode
 * Effects: none
 */
HuffmanTreeNode *HuffmanCoder::deserialize_tree(std::string serial_tree)
{
     HuffmanTreeNode *hehe = nullptr;
     if (serial_tree.empty())
     {
          return nullptr;
     }
     return deserialize_tree_helper(serial_tree, 0, hehe);
}

/*
 * deserialize_tree_helper()
 * Purpose: helper function for deserialize_tree()
 * Parameters: pointer to HuffmanTreeNode, tree string, index integer
 * Returns: a pointer to HuffmanTreeNode
 * Effects: none
 */
HuffmanTreeNode *HuffmanCoder::deserialize_tree_helper(std::string tree,
                                             int index, HuffmanTreeNode *hehe)
{
     char curr = tree[index];
     if (curr == 'L')
     {
          hehe = new HuffmanTreeNode(tree[index + 1], 0);
          return hehe;
     }
     if (curr == 'I')
     {
          string str_left = tree.substr(1, tree.length() - 1);
          HuffmanTreeNode *left = deserialize_tree(str_left);
          string str_right = tree.substr(1 + serialize_tree(left).length(),
                         tree.length() - 1 - serialize_tree(left).length());
          HuffmanTreeNode *right = deserialize_tree(str_right);
          hehe = new HuffmanTreeNode('\0', 0, left, right);
          return hehe;
     }
     return hehe;
}
