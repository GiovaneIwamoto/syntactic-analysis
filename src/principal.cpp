// #include "scanner.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: ./compiler file_name.mj\n";
        return 1;
    }

    // ---------- LEXICAL ANALYSIS ----------

    /*
        string input;

        getline(cin, input);

        Scanner *scanner = new Scanner(argv[1]);
        Token *t;

        do
        {
            t = scanner->nextToken();
            cout << t->name << " -> " << t->lexeme << endl;

        } while (t->name != END_OF_FILE);

        delete scanner;
    */

    // ---------- SYNTACTIC ANALYSIS ----------

    Parser *parser = new Parser(argv[1]);

    parser->run();

    return 0;
}