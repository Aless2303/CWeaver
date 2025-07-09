
%{
#include <stack>
#include "proiectulmeu.tab.h"
int lineNo = 1;
int colNo = 1;

int braceCount = 0; // Contor pentru acolade
char functionBody[65536]; // Buffer pentru corpul funcției
int bodyIndex = 0; // Index pentru buffer

void addToBuffer(const char* text) {
    size_t len = strlen(text);
    if (bodyIndex + len < sizeof(functionBody)) {
        strcpy(&functionBody[bodyIndex], text);
        bodyIndex += len;
    }
}


std::stack<YY_BUFFER_STATE> bufferStack;



// Funcție pentru a schimba la un buffer nou (string)
void switch_to_string(const char* str) {
    // Salvează bufferul curent
    bufferStack.push(YY_CURRENT_BUFFER);

    // Creează un nou buffer pentru string
    YY_BUFFER_STATE newBuffer = yy_scan_string(str);

    // Schimbă la bufferul nou
    yy_switch_to_buffer(newBuffer);
}

// Funcție pentru a reveni la bufferul precedent
void restore_previous_buffer() {
    if (!bufferStack.empty()) {
        // Obține bufferul precedent
        YY_BUFFER_STATE prevBuffer = bufferStack.top();
        bufferStack.pop();

        // Schimbă la bufferul precedent
        yy_switch_to_buffer(prevBuffer);
    } else {
        fprintf(stderr, "Error: No previous buffer to restore.\n");
    }
}

%}

%x FUNCTION_BODY


%%

(int|void|float|double)[ \t]*[a-zA-Z_][a-zA-Z0-9_]*[ \t]*\([^)]*\)[ \t]*\n?[ \t]*\{ {
    yylloc.first_line = lineNo;
    yylloc.first_column = colNo;
    colNo += strlen(yytext);
    braceCount = 1; // Pornim contorizarea acoladelor
    bodyIndex = 0; // Resetăm bufferul
    addToBuffer(yytext); // Adăugăm partea deja procesată
    BEGIN(FUNCTION_BODY); // Trecem în starea FUNCTION_BODY
}

<FUNCTION_BODY>{
    "{" { 
        braceCount++; 
        colNo++; 
        addToBuffer(yytext); 
    } // Creștem contorul pentru o acoladă deschisă
    "}" { 
        braceCount--; 
        colNo++;
        addToBuffer(yytext);
        if (braceCount == 0) { // Dacă am închis toate acoladele
            BEGIN(INITIAL); // Revenim la starea inițială
            functionBody[bodyIndex] = '\0'; // Terminăm string-ul
            yylval.sir = strdup(functionBody); // Stocăm tot corpul funcției
            return TOK_FUNCTION_BODY;
        }
    }
    \n { 
        lineNo++; 
        colNo = 1; 
        addToBuffer("\n"); 
    } // Gestionăm newline
    [^{}\n]+ { 
        colNo += strlen(yytext); 
        addToBuffer(yytext); 
    } // Capturăm alte caractere, excluzând {, } și \n
}


"int" {
    colNo += 3; 
    return TOK_INT; 
}
"float" { colNo+=5; return TOK_FLOAT; }
"double" { colNo+=6; return TOK_DOUBLE; }
"void" { colNo+=4; return TOK_VOID; }
"if" { colNo += 2; return TOK_IF; }
"else" { colNo += 4; return TOK_ELSE; }
"while" { colNo += 5; return TOK_WHILE; }
"printf" { colNo +=6;  
    return TOK_PRINTF; }
"scanf" { colNo+=5; return TOK_SCANF;}
"&" { colNo++; return '&'; }
"return" { colNo+=6; return TOK_RETURN;}
\"[^"]*\" {
    yylloc.first_line = lineNo;
    yylloc.first_column = colNo;
    colNo += strlen(yytext);
    yylval.sir = strdup(yytext + 1); // Eliminăm ghilimelele de început și de sfârșit
    yylval.sir[strlen(yylval.sir) - 1] = '\0';
    return TOK_TEXT_PRINTF; // Returnăm un token special pentru textul din printf
}

"{" { colNo++; return TOK_LBRACE; }
"}" { colNo++; return TOK_RBRACE; }
">" { colNo++; return TOK_GT; }
"<" { colNo++; return TOK_LT; }
">=" { colNo += 2; return TOK_GE; }
"<=" { colNo += 2; return TOK_LE; }
"==" { colNo += 2; return TOK_EQ; }
"!=" { colNo += 2; return TOK_NE; }
"+" { colNo++; return TOK_PLUS; }
"-" { colNo++; return TOK_MINUS; }
"*" { colNo++; return TOK_MULTIPLY; }
"/" { colNo++; return TOK_DIVIDE; }
"(" { colNo++; return TOK_LEFT; }
")" { colNo++; return TOK_RIGHT; }
";" { colNo++; return ';'; }
"=" { colNo++; return '='; }
"," { colNo++; return ','; }




[0-9]+ {
    yylloc.first_line = lineNo;
    yylloc.first_column = colNo;
    colNo += strlen(yytext);
    yylval.dval = strtod(yytext, NULL); // Conversie la int
    return TOK_NUMBER_INT;
}

[0-9]+\.[0-9]+f {
    yylloc.first_line = lineNo;
    yylloc.first_column = colNo;
    colNo += strlen(yytext);
    yylval.dval = strtod(yytext, NULL); // Conversie sigură la float
    return TOK_NUMBER_FLOAT;
}

[0-9]+\.[0-9]+ {
    yylloc.first_line = lineNo;
    yylloc.first_column = colNo;
    colNo += strlen(yytext);
    yylval.dval = strtod(yytext, NULL); // Conversie sigură la double
    return TOK_NUMBER_DOUBLE;
}

"var" { colNo+=3; return TOK_DECLARE; }
"print" { colNo+=5; return TOK_PRINT; }
[a-zA-Z][a-zA-Z0-9]* { 
    yylloc.first_line = lineNo;
    yylloc.first_column = colNo;
    colNo+=strlen(yytext);
    yylval.sir = new char[strlen(yytext)+1];
    strcpy(yylval.sir,yytext);
    return TOK_VARIABLE;
}

"//"[^\n]*        { /* Ignoră comentariile pe o linie */ }

"/*"([^*]|\*+[^*/])*\*+"/" { /* Ignoră comentariile pe mai multe linii */ }




[ ] { colNo++; }
\r\n { lineNo++; colNo=1; }
\n { lineNo++; colNo=1; }
. { colNo++; return TOK_ERROR; }
%%



int yywrap() {
    return 1; // Flex cere această funcție
}