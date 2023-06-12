#include "parser.h"

Parser::Parser(string input)
{
	scanner = new Scanner(input);
}

void Parser::advance()
{
	lToken = scanner->nextToken();
	cout << lToken->lexeme << " "; // TODO: Remove Printing
}

void Parser::match(int token_name, string token_lexeme)
{

	if ((lToken->name == token_name && lToken->lexeme == token_lexeme) ||
		(lToken->name == 1 && token_lexeme == "ID") ||
		(lToken->name == 2 && token_lexeme == "INTEGER_LITERAL"))
		advance();
	else
		error("UNEXPECTED ERROR");
}

void Parser::run()
{
	advance();

	program();

	cout << "COMPILATION COMPLETED SUCCESSFULLY!\n";
}

// 1. Program → MainClass (ClassDeclaration)∗ EOF
void Parser::program()
{
	mainClass();

	while (lToken->name == 1)
	{
		classDeclaration();
	}

	// match(7, "END_OF_FILE");
}

// 2. MainClass → class ID { public static void main (String[ ] ID){ Statement } }
void Parser::mainClass()
{
	match(1, "class");
	match(1, "ID");
	match(4, "{");
	match(1, "public");
	match(1, "static");
	match(1, "void");
	match(1, "main");
	match(4, "(");
	match(1, "String");
	match(4, "[");
	match(4, "]");
	match(1, "ID");
	match(4, ")");
	match(4, "{");
	statement();
	match(4, "}");
	match(4, "}");
}

// 3. ClassDeclaration → class ID (extends ID)? { (VarDeclaration)∗ (MethodDeclaration)∗}
void Parser::classDeclaration()
{
	match(1, "class");
	match(1, "ID");

	if (lToken->name == 1 && lToken->lexeme == "extends")
	{
		advance();
		match(1, "ID");
	}

	match(4, "{");

	while (lToken->name == 1 && lToken->lexeme != "public")
		varDeclaration();

	while (lToken->name == 1 || lToken->lexeme == "public")
		methodDeclaration();

	match(4, "}");
}

// 4. VarDeclaration → Type ID ;
void Parser::varDeclaration()
{
	type();
	match(1, "ID");
	match(4, ";");
}

// 5. MethodDeclaration → public Type ID ((Type ID (, Type ID)*)?) { (VarDeclaration)* (Statement)* return Expression ; }
void Parser::methodDeclaration()
{
	match(1, "public");
	type();
	match(1, "ID");
	match(4, "(");

	if (lToken->name != 4)
	{
		type();
		match(1, "ID");
		while (lToken->name == 4 && lToken->lexeme == ",")
		{
			advance();
			type();
			match(1, "ID");
		}
	}

	match(4, ")");
	match(4, "{");

	// TODO: ID to VARDECLARATION and STATEMENT
	//  VarDeclaration
	while ((lToken->name == 1 && (lToken->lexeme == "int" || "boolean" || "ID")) || (lToken->lexeme == "int[]")) // FIRST VarDeclaration
	{
		advance();
		if (lToken->name == 1 && lToken->lexeme == "ID")
		{
			advance();
			match(4, ";");
		}
		else
		{
			break;
		}
	}

	// Statement
	while (lToken->lexeme != "return")
	{
		if ((lToken->name == 3 && lToken->lexeme == "="))
		{
			advance();
			expression();
			match(4, ";");
		}
		else if (lToken->name == 4 && lToken->lexeme == "[")
		{
			advance();
			expression();
			match(4, "]");
			match(3, "=");
			expression();
			match(4, ";");
		}
		else
		{
			statement();
		}
	}

	match(1, "return");

	expression();

	match(4, ";");
	match(4, "}");
}

// 6. Type → int[] | boolean | int | ID
void Parser::type()
{

	if (lToken->name == 1 && (lToken->lexeme == "int[]" || lToken->lexeme == "int" || lToken->lexeme == "boolean" || lToken->lexeme == "ID"))
	{
		advance();
	}
	else
	{
		error("INVALID TYPE");
	}
}

/*
7. Statement → { (Statement)*}
| if ( Expression ) Statement else Statement
| while ( Expression ) Statement
| System.out.println ( Expression ) ;
| ID = Expression ;
| ID [ Expression ] = Expression ;
*/

void Parser::statement()
{
	if (lToken->name == 4 && lToken->lexeme == "{")
	{
		advance();
		while ((lToken->name != 4 && lToken->lexeme != "}") &&
			   (lToken->name != 4 && lToken->lexeme != ";"))
			statement();
		match(4, "}");
	}
	else if (lToken->name == 1 && lToken->lexeme == "if")
	{
		advance();
		match(4, "(");
		expression();
		match(4, ")");
		statement();
		match(1, "else");
		statement();
	}
	else if (lToken->name == 1 && lToken->lexeme == "while")
	{
		advance();
		match(4, "(");
		expression();
		match(4, ")");
		statement();
	}
	else if (lToken->name == 5 && lToken->lexeme == "System.out.println")
	{
		advance();
		match(4, "(");
		expression();
		match(4, ")");
		match(4, ";");
	}
	else if (lToken->name == 1)
	{
		match(1, "ID");
		if (lToken->name == 3 && lToken->lexeme == "=")
		{
			advance();
			expression();
			match(4, ";");
		}
		else if (lToken->name == 4 && lToken->lexeme == "[")
		{
			advance();
			expression();
			match(4, "]");
			match(3, "=");
			expression();
			match(4, ";");
		}
		else
		{
			error("DECLARATION ERROR");
		}
	}
	else
	{
		error("INVALID DECLARATION");
	}
}

/*
8. Expression → Expression Op Expression
| Expression [ Expression ]
| Expression . length
| Expression . ID ( ( Expression (, Expression )∗)? )
| INTEGER_LITERAL
| true
| false
| ID
| this
| new int [ Expression ]
| new ID ( )
| ! Expression
| ( Expression )
*/

void Parser::expression()
{

	if (lToken->name == 1 && lToken->lexeme == "new")
	{
		advance();

		// Expression → new int [ Expression ]
		if (lToken->name == 1 && lToken->lexeme == "int")
		{
			advance();
			match(4, "[");
			expression();
			match(4, "]");
		}

		// Expression → new ID ( )
		else if (lToken->name == 1 && lToken->lexeme == "ID")
		{
			advance();
			match(4, "(");
			match(4, ")");
		}
		else
		{
			error("EXPRESSION ERROR");
		}
	}

	else if ((lToken->name == 1 && (lToken->lexeme == "ID" || lToken->lexeme == "true" || lToken->lexeme == "false" || lToken->lexeme == "this")) || (lToken->name == 2))
	{
		advance();

		// Expression → Expression [ Expression ]
		if (lToken->name == 4 && lToken->lexeme == "[")
		{
			advance();
			expression();
			match(4, "]");
		}

		if (lToken->name == 4 && lToken->lexeme == ".")
		{
			advance();

			// Expression → Expression . length
			if (lToken->name == 1 && lToken->lexeme == "length")
			{
				advance();
			}

			// Expression → Expression . ID ( ( Expression (, Expression )*)? )
			else if (lToken->name == 1 && lToken->lexeme == "ID")
			{
				advance();
				match(4, "(");

				if (lToken->lexeme != ")")
				{
					expression();

					while (lToken->name == 4 && lToken->lexeme == ",")
					{
						advance();
						expression();
					}
				}

				match(4, ")");
			}

			else
			{
				error("EXPRESSION ERROR");
			}
		}
	}

	// Expression → ! Expression
	else if (lToken->name == 3 && lToken->lexeme == "!")
	{
		advance();
		expression();
	}

	// Expression →  ( Expression )
	else if (lToken->name == 4 && lToken->lexeme == "(")
	{
		advance();
		expression();
		match(4, ")");
	}

	else
	{
		error("INVALID EXPRESSION");
	}
}

// 9. Op → && | < | > | == | != | + | - | * | /
void Parser::op()
{
	if (lToken->name == 3 && (lToken->lexeme == "&&" || lToken->lexeme == "<" ||
							  lToken->lexeme == ">" || lToken->lexeme == "==" ||
							  lToken->lexeme == "!=" || lToken->lexeme == "+" ||
							  lToken->lexeme == "-" || lToken->lexeme == "*" ||
							  lToken->lexeme == "/"))
	{
		advance();
	}
	else
	{
		error("INVALID OPERATOR");
	}
}

void Parser::error(string str)
{
	cout << "LINE " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
