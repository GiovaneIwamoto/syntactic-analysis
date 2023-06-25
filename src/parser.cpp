#include "parser.h"

Parser::Parser(string input)
{
	scanner = new Scanner(input);

	cout << endl;
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

	cout << endl
		 << "COMPILATION COMPLETED SUCCESSFULLY!\n";
}

// 1. Program → MainClass (ClassDeclaration)∗ EOF
void Parser::program()
{
	mainClass();

	while (lToken->name == 5)
	{
		classDeclaration();
	}

	// match(7, "END_OF_FILE");
}

// 2. MainClass → class ID { public static void main (String[ ] ID){ Statement } }
void Parser::mainClass()
{
	match(5, "class");
	match(1, "ID");
	match(4, "{");
	match(5, "public");
	match(5, "static");
	match(5, "void");
	match(5, "main");
	match(4, "(");
	match(5, "String");
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
	match(5, "class");
	match(1, "ID");

	if (lToken->name == 5 && lToken->lexeme == "extends")
	{
		advance();
		match(1, "ID");
	}

	match(4, "{");

	// TODO:
	while (lToken->lexeme != "public" && "}")
		varDeclaration();

	while (lToken->lexeme == "public")
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
	match(5, "public");
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

	//  (VarDeclaration)*
	while ((((lToken->name == 5) && (lToken->lexeme == "int" || "boolean")) || (lToken->name == 1)) && (lToken->lexeme != "return"))
	{
		if (lToken->name == 1)
		{
			advance();

			if (lToken->name == 1)
			{
				advance();
				match(4, ";");
			}

			// Statement case inside Method Declaration
			if (lToken->name == 3 && lToken->lexeme == "=")
			{
				break;
			}

			if (lToken->name == 4 && lToken->lexeme == "[")
			{
				break;
			}
		}
		else if ((lToken->name == 5) && (lToken->lexeme == "int" || "boolean"))
		{
			advance();
			if (lToken->name == 4 && lToken->lexeme == "[")
			{
				match(4, "[");
				match(4, "]");

				if (lToken->name == 1)
				{
					advance();
					match(4, ";");
				}
			}
			else if (lToken->name == 1)
			{
				advance();
				match(4, ";");
			}
		}
	}

	// (Statement)*
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

	match(5, "return");

	expression();

	match(4, ";");
	match(4, "}");
}

// 6. Type → int[] | boolean | int | ID
void Parser::type()
{
	if (lToken->name == 5 && lToken->lexeme == "int")
	{
		match(5, "int");
		if (lToken->name == 4 && lToken->lexeme == "[")
		{
			match(4, "[");
			match(4, "]");
		}
	}
	else if ((lToken->name == 5 && lToken->lexeme == "boolean") || (lToken->name == 1))
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
	else if (lToken->name == 5 && lToken->lexeme == "if")
	{
		advance();
		match(4, "(");
		expression();
		match(4, ")");
		statement();
		match(5, "else");
		statement();
	}
	else if (lToken->name == 5 && lToken->lexeme == "while")
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
	// Expression →  ( Expression )
	if (lToken->name == 4 && lToken->lexeme == "(")
	{
		advance();
		expression();
		match(4, ")");

		// Expression → Expression Op Expression
		if (lToken->name == 3 && lToken->lexeme != "!")
		{
			advance();
			expression();
		}

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
			if (lToken->name == 5 && lToken->lexeme == "length")
			{
				advance();
			}

			// Expression → Expression . ID ( ( Expression (, Expression )*)? )
			else if (lToken->name == 1)
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
		}
	}

	// Expression → ! Expression
	else if (lToken->name == 3 && lToken->lexeme == "!")
	{
		advance();
		expression();
	}

	else if (lToken->name == 5 && lToken->lexeme == "new")
	{
		advance();

		// Expression → new int [ Expression ]
		if (lToken->name == 5 && lToken->lexeme == "int")
		{
			advance();
			match(4, "[");
			expression();
			match(4, "]");

			// Expression → Expression Op Expression
			if (lToken->name == 3 && lToken->lexeme != "!")
			{
				advance();
				expression();
			}

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
				if (lToken->name == 5 && lToken->lexeme == "length")
				{
					advance();
				}

				// Expression → Expression . ID ( ( Expression (, Expression )*)? )
				else if (lToken->name == 1)
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
			}
		}

		// Expression → new ID ( )
		else if (lToken->name == 1)
		{
			advance();
			match(4, "(");
			match(4, ")");

			// Expression → Expression Op Expression
			if (lToken->name == 3 && lToken->lexeme != "!")
			{
				advance();
				expression();
			}

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
				if (lToken->name == 5 && lToken->lexeme == "length")
				{
					advance();
				}

				// Expression → Expression . ID ( ( Expression (, Expression )*)? )
				else if (lToken->name == 1)
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
			}
		}
	}

	else if (((lToken->name == 1)) || (lToken->name == 5 && (lToken->lexeme == "true" || lToken->lexeme == "false" || lToken->lexeme == "this")) || (lToken->name == 2))
	{
		advance();

		// Expression → Expression Op Expression
		if (lToken->name == 3 && lToken->lexeme != "!")
		{
			advance();
			expression();
		}

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
			if (lToken->name == 5 && lToken->lexeme == "length")
			{
				advance();
			}

			// Expression → Expression . ID ( ( Expression (, Expression )*)? )
			else if (lToken->name == 1)
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
		}
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

// TODO: Fix Errors messages and remove this printing
void Parser::error(string str)
{
	cout << endl
		 << endl
		 << "LINE " << scanner->getLine() << ": " << str << endl
		 << "============================================================================" << endl;

	exit(EXIT_FAILURE);
}
