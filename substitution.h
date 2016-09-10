//
// Created by Laurens on 10-9-2016.
//

#ifndef WEEK_1_SUBSTITUTION_H
#define WEEK_1_SUBSTITUTION_H

#include <iostream>
#include <string.h>
#include <stdlib.h>

using std::cout;
using std::cin;
using std::string;
using std::endl;


constexpr char* info = "Usage: substitution [-o] [-d] mapping\n"
        "Where:\n"
        "   -o: keep non-letters as is, honor letter casing\n"
        "   -d: decrypt\n"
        "   mapping: 26 letter char-mapping\n"
        "            or an int-value\n"
        "\n"
        "En/Decrypts stdin to stdout. Only letters are encrypted,\n"
        "all other characters are silently ignored, unless -o was\n"
        "specified, in which case they are used as-is.\n"
        "When -o is specified, letter casing is honored, otherwise all\n"
        "letters are converted to lower-case letters.\n"
        "Use an int-value to to a letter shift (% 26, 0: a = a)\n"
        "Shift 3 is the classical Caesar encryption";

void initialize(int argc, char** argv,bool& o, bool& d);
void encrypt(int cyphier, bool o, bool d, char *mapping);
string readFromStdIn(bool d);
int mod (int a, int b);
inline int convert(int cyphier, bool d,int index);
inline char convert(char* mapping, bool d,int index);

#endif //WEEK_1_SUBSTITUTION_H
