/*
Collection of utilities that are beneficial while testing / debugging the
various steps of zapping / unzapping.

This module provides functions to:
- Make a tree based on the tree in figure 1
- Print a tree in a hierarchical fashion
- Determine if two trees are equal

Please read the function headers below for more information.

Author: Chami Lamelas (slamel01)
Date: Jan 2023
*/

#ifndef _ZAP_UTIL_H
#define _ZAP_UTIL_H

#include "HuffmanTreeNode.h"

/*
Constructs a tree that looks like the tree in figure 1 of the spec.

Frequencies are set in the nodes of the tree that are possible for the tree to
look as it does in the spec as if it were built using the build Huffman tree
algorithm outlined in the spec.

In particular, we suppose characters a, b, e, and f have frequency 1 and
characters c and d have frequency 2.

Hence the tree constructed by this algorithm, if printed, would look something
like this:

                            []|8

            []|4                            []|4

    []|2            []|2            c |2            d |2

a |1    b |1    e |1    f |1

Parameters:
    internalNodeVal - The character that is used as the value for internal
nodes. You have to choose this when writing your build Huffman tree function.
'\0' is a good choice for example.

Returns:
    The root to a tree created as described above. Note, the root is a pointer
to memory on the heap, so you will need to free this if you're testing your code
with valgrind.
*/
HuffmanTreeNode *makeFigure1Tree(char internalNodeVal);

/*
Prints a tree in a nice manner, level by level with structure and both node
values and frequency.

Given that the internal node value can be set to non-printable characters, their
value is replaced by the string []. So, an internal node with frequency 10 would
appear in the printed output as []|10.

Output is printed to stdout.

WARNING: It is recommended this function is only used on smaller trees as
eventually, with deeper trees, the width of text that is printed to stdout will
quickly increase and will most likely wrap around in your terminal.

Parameters:
    root - Pointer to the root of the tree to print.
    internalNodeVal - The value used in internal nodes of the tree. You have to
choose this when writing your build Huffman tree function. '\0' is a good choice
for example.

Returns:
    Nothing (void).
*/
void printTree(HuffmanTreeNode *root, char internalNodeVal);

/*
Determines whether the trees rooted at two nodes are equal.

Tree equality is defined recursively as follows.
    1. If both trees are empty, they're equal. If one is empty and the other
isn't, they are not.
    2. If both trees are not empty, the roots of the two trees must have equal
value and frequency (depending on checkFrequency) as well as having equal left
and right subtrees.

Parameters:
    root1 - Pointer to the root of a tree.
    root2 - Pointer to the root of another tree.
    checkFrequency - If set to true, the frequency must also be equal in step 2
above.

Returns:
    true if the two trees are equal as defined above and false otherwise.
*/
bool treeEquals(HuffmanTreeNode *root1, HuffmanTreeNode *root2,
                bool checkFrequency);

#endif