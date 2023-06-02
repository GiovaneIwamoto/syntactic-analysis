#include "scanner.h"

Scanner::Scanner(string input)
{
    // this->input = input;
    cout << "INPUT: " << input << endl
         << "SIZE: "
         << input.length() << endl
         << endl;

    pos = 0;
    line = 1;

    ifstream inputFile(input, ios::in);
    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else
        cout << "UNABLE TO OPEN FILE\n";

    cout << this->input << endl;
}

int Scanner::getLine()
{
    return line;
}

Token *
Scanner::nextToken()
{
    Token *tok;
    string lexeme;

    // ---------- WHITESPACE ----------
    while (pos < static_cast<int>(input.length()) && isspace(input[pos]))
    {
        if (input[pos] == '\n')
            line++;
        pos++;
    }

    // ---------- END_OF_FILE ----------
    if (pos >= static_cast<int>(input.length()))
        return new Token(END_OF_FILE);

    char currentChar = input[pos];

    // ---------- ID OR RESERVED_KEYWORD ----------
    if (isalpha(currentChar))
    {
        lexeme += currentChar;
        pos++;

        while (pos < static_cast<int>(input.length()) && (isalnum(input[pos]) || input[pos] == '_' || input[pos] == '.'))
        {
            lexeme += input[pos];
            pos++;
        }
        if (lexeme == "boolean" || lexeme == "class" || lexeme == "else" ||
            lexeme == "extends" || lexeme == "false" || lexeme == "if" ||
            lexeme == "int" || lexeme == "length" || lexeme == "main" ||
            lexeme == "new" || lexeme == "public" || lexeme == "return" ||
            lexeme == "static" || lexeme == "String" || lexeme == "this" ||
            lexeme == "true" || lexeme == "void" || lexeme == "while" ||
            lexeme == "System.out.println")
        {
            if (lexeme == "System.out.println")
                tok = new Token(RESERVED_KEYWORD, "System.out.println");
            else
                tok = new Token(ID, lexeme);
        }

        else
        {
            string::size_type dotPos = lexeme.find('.');
            if (dotPos != string::npos)
            {
                string errorMsg = "INVALID TOKEN: " + lexeme;
                lexicalError(errorMsg);
            }

            tok = new Token(ID, lexeme);
        }
    }

    // ---------- INTEGER_LITERAL ----------
    else if (isdigit(currentChar))
    {

        lexeme += currentChar;
        pos++;

        while (pos < static_cast<int>(input.length()) && isdigit(input[pos]))
        {
            lexeme += input[pos];
            pos++;
        }

        if (pos < static_cast<int>(input.length()) && (isalpha(input[pos]) && !isspace(input[pos])))
        {

            while (pos < static_cast<int>(input.length()) && (!isspace(input[pos])))
            {
                lexeme += input[pos];
                pos++;
            }

            string errorMsg = "INVALID TOKEN: " + lexeme;
            lexicalError(errorMsg);
        }

        tok = new Token(INTEGER_LITERAL, lexeme);
    }

    // ---------- COMMENT ----------
    else if (currentChar == '/')
    {
        // LINE COMMENT
        if (pos + 1 < static_cast<int>(input.length()) && input[pos + 1] == '/')
        {
            pos += 2;

            while (pos < static_cast<int>(input.length()) && input[pos] != '\n')
                pos++;

            return nextToken();
        }

        // BLOCK COMMENT
        else if (pos + 1 < static_cast<int>(input.length()) && input[pos + 1] == '*')
        {
            pos += 2;

            while (pos < static_cast<int>(input.length()) - 1 && (input[pos] != '*' || input[pos + 1] != '/'))
            {
                if (input[pos] == '\n')
                    line++;
                pos++;
            }

            if (pos >= static_cast<int>(input.length()) - 1)
                lexicalError("BLOCK COMMENT NOT CLOSED.");

            pos += 2;

            return nextToken();
        }

        // ---------- OP ----------
        else
        {
            tok = new Token(OP, "/");
            pos++;
        }
    }

    else if (currentChar == '<' || currentChar == '>' || currentChar == '+' || currentChar == '-' ||
             currentChar == '*' || currentChar == '=' || currentChar == '!' || currentChar == '&')
    {
        lexeme += currentChar;
        pos++;

        // Compund operator
        if (pos < static_cast<int>(input.length()) && ((input[pos - 1] == '&' && input[pos] == '&') ||
                                                       (input[pos - 1] == '=' && input[pos] == '=') ||
                                                       (input[pos - 1] == '!' && input[pos] == '=')))
        {
            lexeme += input[pos];
            pos++;
        }

        tok = new Token(OP, lexeme);
    }

    // ---------- SEP ----------
    else if (currentChar == '(' || currentChar == ')' ||
             currentChar == '[' || currentChar == ']' ||
             currentChar == '{' || currentChar == '}' ||
             currentChar == ';' || currentChar == '.' ||
             currentChar == ',')
    {
        lexeme += currentChar;
        pos++;

        tok = new Token(SEP, lexeme);
    }
    else
    {
        string errorMsg = "INVALID CHARACTER: ";
        errorMsg += currentChar;
        lexicalError(errorMsg);
    }
    return tok;
}

void Scanner::lexicalError(string msg)
{
    cout << endl
         << endl
         << "LINE " << line << ": " << msg << endl;

    exit(EXIT_FAILURE);
}
