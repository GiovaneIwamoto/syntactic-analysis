#include <iostream>
#include <ctype.h>
#include <string>

using namespace std;

enum Names
{
    UNDEF,
    ID,
    INTEGER_LITERAL,
    OP,
    SEP,
    RESERVED_KEYWORD,
    WHITESPACE,
    END_OF_FILE
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
