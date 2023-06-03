#include <iostream>
#include <ctype.h>
#include <string>

using namespace std;

enum Names
{
    UNDEF,            // 0
    ID,               // 1
    INTEGER_LITERAL,  // 2
    OP,               // 3
    SEP,              // 4
    RESERVED_KEYWORD, // 5
    WHITESPACE,       // 6
    END_OF_FILE       // 7
};

class Token
{
public:
    int name;
    int attribute;
    string lexeme;

    Token(int name)
    {
        this->name = name;
        attribute = UNDEF;
    }

    Token(int name, string l)
    {
        this->name = name;
        attribute = UNDEF;
        lexeme = l;
    }

    Token(int name, int attr)
    {
        this->name = name;
        attribute = attr;
    }
};
