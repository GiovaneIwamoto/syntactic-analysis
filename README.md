# SYNTACTIC ANALYSIS

### **LEXICAL AND SYNTATIC OVERVIEW**

> [!NOTE]
> This project involves the implementation of both a predictive descending parser and a lexical analyzer for the modified MiniJava programming language. MiniJava is a subset of Java with certain extensions, and the goal is to create tools that can effectively parse and analyze this language.

The predictive descending parser will be capable of traversing the source program, detecting, and reporting errors. This parser will utilize a top-down approach, using a set of recursive procedures to process the input based on the grammar rules defined for MiniJava. It should efficiently handle the syntax of the language, ensuring that all constructs are validated against the specified grammar. The lexical analyzer will recognize and return the tokens of the modified MiniJava language as specified. These tokens will later serve as the terminal symbols in the grammar that defines the accepted constructs of the language. The lexical analyzer should efficiently scan the input program, identify lexical elements, and categorize them into appropriate token types, ensuring that the input is appropriately prepared for the parsing stage.

[![Icons](https://skillicons.dev/icons?i=cpp,java,regex&theme=dark)](https://skillicons.dev)

---

### **TOKENS**

> [!IMPORTANT]
> System.out.println should be treated as a single reserved word and not as a method call.

```ruby
[IDENTIFIERS] A sequence of letters, digits, and underscores, always starting with a letter.

[INTEGER LITERALS] A sequence of decimal digits representing an integer number.

[RESERVED WORDS] boolean, class, else, extends, false, if, int, length, main, new, public, return, static, String, System.out.println, this, true, void, and while.

[COMMENTS] Comments should be ignored. There are two types: line comments and block comments.

[WHITESPACE] Whitespace should be ignored. It includes \n \t \r \f.

[OPERATORS] and [SEPARATORS]
```

> [!WARNING]
> Reserved words are recognized as identifiers, except for System.out.println because it doesn't match the pattern of identifiers.

---

### **SYNTACTIC OVERVIEW**

Build a predictive recursive descent parser:

`1. TRANSFORM GRAMMAR INTO LL(1):`

• Eliminate left recursion.

• Construct FIRST and FOLLOW sets.

• Left-factor if necessary.

`2. DEFINE A PROCEDURE FOR EACH NON-TERMINAL:`

• Implement an option for each production right-hand side.

• Invoke procedures for non-terminals as needed.

---

### **GRAMMAR**

> [!TIP]
> The following grammar uses the notation (N)\* to represent 0 or more repetitions of N and the notation (N)? to represent 0 or 1 repetition of N. The language tokens are represented in bold, and the non-terminals are represented in italics.

```java
1. Program -> MainClass (ClassDeclaration)* EOF

2. MainClass -> class ID { public static void main (String[ ] ID ){ Statement } }

3. ClassDeclaration -> class ID (extendsID)? { (VarDeclaration)* (MethodDeclaration)* }

4. VarDeclaration -> Type ID ;

5. MethodDeclaration -> public Type ID ( ( Type ID ( , Type ID)* ) ? ) { (VarDeclaration)* (Statement)* return Expression ; }

6. Type -> int[] | boolean | int | ID

7. Statement -> { (Statement)* }
    | if ( Expression ) Statement else Statement
    | while ( Expression ) Statement
    | System.out.println ( Expression ) ;
    | ID = Expression ;
    | ID[ Expression ] = Expression ;

8. Expression -> Expression Op Expression
    | Expression [ Expression ]
    | Expression . length
    | Expression . ID ( ( Expression (, Expression )* ) ? )
    | INTEGER_LITERAL
    | true
    | false
    | ID
    | this
    | newint [ Expression ]
    | newID ()
    | ! Expression
    | ( Expression )

9. Op -> && | < | > | == | != | + | - | * | /
```

---

### **COMPILE AND EXECUTE**

```ruby
$ g++ -Wall \*.cpp -o mjc
$ ./mjc program.mj
```

---

### **AUTHOR**

- Giovane Hashinokuti Iwamoto - Computer Science student at UFMS - Brazil - MS

I am always open to receiving constructive criticism and suggestions for improvement in my developed code. I believe that feedback is an essential part of the learning and growth process, and I am eager to learn from others and make my code the best it can be. Whether it's a minor tweak or a major overhaul, I am willing to consider all suggestions and implement the changes that will benefit my code and its users.
