/*
 * main.cpp
 * Anh Hoang ahoang05
 * 3/7/2022
 * COMP 15 Project 3
 * zap
 *
 * main function for zap
 *
 */

#include "HuffmanCoder.h"
#include "HuffmanTreeNode.h"
#include <iostream>
#include <fstream>

using namespace std;

void errorMessage(string error_message);

template <typename streamtype>
void openFile(streamtype &stream, string file_name);

/*
 * main()
 * Purpose: main function for zap
 * Parameters: argument count and argument vector
 * Returns: 0
 * Effects:
 */
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        errorMessage("Usage: ./zap [zap | unzap] inputFile outputFile");
        return 0;
    }
    else
    {
        string call = argv[1];
        HuffmanCoder zap;
        if (call == "zap")
        {
            zap.encoder(argv[2], argv[3]);
        }
        else if (call == "unzap")
        {
            zap.decoder(argv[2], argv[3]);
        }
        else
        {
            errorMessage("Usage: ./zap [zap | unzap] inputFile outputFile");
            return 0;
        }
    }

    return 0;
}

/*
 * errorMessage()
 * Purpose: print out error message and exit program
 * Arguments: string error_message
 * Return: none
 * Effects: none
 */
void errorMessage(string error_message)
{
    std::cerr << error_message << std::endl;
    exit(EXIT_FAILURE);
}
