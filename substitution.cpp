#include "substitution.h"

/*
 * The main function of the program. For usage information run the program without parameters.
 */
int main(int argc, char** argv){
    bool o = false, d = false;
    initialize(argc,argv,o,d);
    int cyphier = 0;
    char* mapping = nullptr;
    if(isdigit(argv[argc-1][0]))
        cyphier = atoi(argv[argc-1]);
    else
        mapping = argv[argc-1];
    encrypt(cyphier, o, d, mapping);
}

/*
 * This function encrypts or decrypts stdin to stdout.
 */
void encrypt(int cyphier, bool o, bool d, char *mapping){
    string input = readFromStdIn(d);
    string output = "";
    char newChar = '\0';
    for (int i = 0; i < input.length(); ++i) {
        if (isalpha(input[i])) {
            int index = tolower(input[i]) - 'a';
            if(mapping!= nullptr)
                newChar = convert(mapping, d, index);
            else{
                index = convert(cyphier, d, index);
                newChar = (char) ((index) + (int)'a');
            }
            if (o&&isupper(input[i]))newChar = toupper(newChar);
        } else if (o) {
            newChar = input[i];
        }else{
            continue;
        }
        output += newChar;
    }
    cout << (d?"Decrypted":"Encrypted")<<" text:\n"<<  output << endl;

}

/*
 * This method converts a decrypted character to an encrypted character and vica versa. This is done according to a cyphier
 */
inline int convert(int cyphier, bool d,int index){
    if(d)cyphier = -cyphier;//Reverse the cyphier to decrypt the text
    return mod((index - cyphier),26);
}

/*
 * This method converts a decrypted character to an encrypted character and vica versa. This is done according to a mapping.
 */
inline char convert(char* mapping, bool d,int index){
    if(!d)
        return mapping[index];
    char c = 'a' + index;
    int i = 0;
    while(mapping[i]!=c)i++;
    return i + 'a';
}

/*
 * Reads lines from the stdin until an eof is encountered. This can be simulated in the terminal by ctrl d (linux) or ctrl z (windows
 */
string readFromStdIn(bool d) {
    cout << "Enter text to " << (d ? "decrypt" : "encrypt") << endl;
    string total;
    string input;
    while (getline(cin, input) && !input.empty())
        total += input + "\n";
    return total;
}

/*
 * Returns the remainder of a division. This function is guaranteed to return a positive value.
 */
int mod (int a, int b)
{
    int ret = a % b;
    if(ret < 0)
        ret+=b;
    return ret;
}

/*
 * Initializes the program. It checks the command line parameters and sets the o and d references accordingly
 */
void initialize(int argc, char** argv,bool& o, bool& d){
    if(argc==1) {
        cout << info << endl;
        exit(2);
    }else{
        if(strcmp(argv[1],"-o")==0)
            o = true;
        if (strcmp(argv[1], "-d") == 0 || (argc >= 3 && strcmp(argv[2], "-d") == 0))
            d = true;
    }
}