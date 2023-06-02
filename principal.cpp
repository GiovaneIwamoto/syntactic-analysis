#include "scanner.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: ./compiler file_name.mj\n";
        return 1;
    }

    string input;

    // getline(cin, input);

    Scanner *scanner = new Scanner(argv[1]);

    Token *t;

    do
    {
        t = scanner->nextToken();
        cout << t->name << " -> " << t->lexeme << endl;

    } while (t->name != END_OF_FILE);

    delete scanner;

    return 0;
}