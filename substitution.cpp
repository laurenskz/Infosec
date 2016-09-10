#include "substitution.h"

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
inline int convert(int cyphier, bool d,int index){
    if(d)cyphier = -cyphier;//Reverse the cyphier to decrypt the text
    return mod((index - cyphier),26);
}

inline char convert(char* mapping, bool d,int index){
    if(!d)
        return mapping[index];
    char c = 'a' + index;
    int i = 0;
    while(mapping[i]!=c)i++;
    return i + 'a';
}

string readFromStdIn(bool d) {
    cout << "Enter text to " << (d ? "decrypt" : "encrypt") << endl;
    string total;
    string input;
    while (getline(cin, input) && !input.empty())
        total += input + "\n";
    return total;
}

int mod (int a, int b)
{
    int ret = a % b;
    if(ret < 0)
        ret+=b;
    return ret;
}

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