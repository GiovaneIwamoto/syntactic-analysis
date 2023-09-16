# SYNTACTIC ANALYSIS

### **LEXICAL INTRO**

Implementation of the lexical analyzer for the MiniJava programming language with some extensions. MiniJava is a subset of Java, and its lexical analyzer should be able to recognize and return the tokens of the language specified in this document, which will later be terminal symbols of the grammar that specifies the language's accepted constructs.

### **LEXICAL TOKENS**

`1. IDENTIFIERS` A sequence of letters, digits, and underscores, always starting with a letter. The language distinguishes between uppercase and lowercase letters.

`2. INTEGER LITERALS` A sequence of decimal digits representing an integer number.

`3. OPERATORS`

`4. SEPARATORS`

`5. RESERVED WORDS` boolean, class, else, extends, false, if, int, length,
main, new, public, return, static, String, System.out.println, this, true, void, and while.

`6. COMMENTS` Comments should be ignored. There are two types: line comments and block comments.

`7. WHITESPACE` Whitespace should be ignored. It includes \n \t \r \f.

### **SYNTACTIC**

To build a predictive recursive descent parser, we need to:

`1. TRANSFORM GRAMMAR INTO LL(1):`

• Eliminate left recursion.

• Construct FIRST and FOLLOW sets.

• Left-factor, if necessary.

`2. DEFINE A PROCEDURE FOR EACH NON-TERMINAL:`

• Implement an option for each production right-hand side.

• Invoke procedures for non-terminals as needed.

### **GRAMMAR**

The following grammar.png uses the notation (N)\* to represent 0 or more repetitions of N and the notation (N)? to represent 0 or 1 repetition of N. The language tokens are represented in bold, and the non-terminals are represented in italics.

### **COMPILE / EXECUTE**

`g++ -Wall \*.cpp -o mjc`
`./mjc program.mj`

### **AUTHOR**

-   Giovane Hashinokuti Iwamoto - Computer Science student at UFMS - Brazil - MS

I am always open to receiving constructive criticism and suggestions for improvement in my developed code. I believe that feedback is an essential part of the learning and growth process, and I am eager to learn from others and make my code the best it can be. Whether it's a minor tweak or a major overhaul, I am willing to consider all suggestions and implement the changes that will benefit my code and its users.
