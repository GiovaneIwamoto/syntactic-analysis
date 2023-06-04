#include "scanner.h"

class Parser
{
private:
	Scanner *scanner;
	Token *lToken;

	void advance();
	void match(int, string);

public:
	Parser(string);
	void run();
	void program();
	void mainClass();
	void classDeclaration();
	void varDeclaration();
	void methodDeclaration();
	void type();
	void statement();
	void expression();
	void op();
	void error(string);
};