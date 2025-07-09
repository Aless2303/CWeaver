/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "ex1lab12.y"

using namespace std;


#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
#include <variant>
#include <unordered_map>

#include <stack>
#include <sstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <cctype>
#include <locale>


#include <limits>


extern void switch_to_string(const char* str); // Declarația funcției din Flex
extern void restore_previous_buffer();        // Declarația funcției din Flex

extern int yylex();
extern int yyparse();
extern int yyerror(const char *msg);

void yyrestart(FILE *input_file);



int EsteCorecta = 1;
char msg[500];
int valoareif = -2;

const int INT_MIN_LIMIT = std::numeric_limits<int>::min();
const int INT_MAX_LIMIT = std::numeric_limits<int>::max();
const float FLOAT_MIN_LIMIT = std::numeric_limits<float>::lowest();
const float FLOAT_MAX_LIMIT = std::numeric_limits<float>::max();
const double DOUBLE_MIN_LIMIT = std::numeric_limits<double>::lowest();
const double DOUBLE_MAX_LIMIT = std::numeric_limits<double>::max();





enum VarType { INT_TYPE, FLOAT_TYPE, DOUBLE_TYPE }; // Tipurile de variabile suportate


class TVAR {
    char* nume;
    VarType tip;        // Tipul variabilei
    union {             // Valorile variabilei
        int val_int;
        float val_float;
        double val_double;
    };
    TVAR* next;

public:
    TVAR* head;
    TVAR* tail;
    TVAR(char* n, VarType t, double v); // Constructor
    TVAR();
    int exists(const char* n);
    void add(char* n, VarType t, double v);
    double getValue(const char* n);
    VarType getType(const char* n);
    void setValue(const char* n, double v, VarType t);
    void printVars();
    void remove(const char* n);
};

void TVAR::remove(const char* n) {
    TVAR* prev = nullptr;
    TVAR* curr = TVAR::head;

    // Parcurgem lista pentru a găsi variabila cu numele specificat
    while (curr != nullptr) {
        if (strcmp(curr->nume, n) == 0) {
            // Variabila găsită
            if (prev == nullptr) {
                // Dacă este primul element
                TVAR::head = curr->next;
            } else {
                // Legăm elementul anterior de următorul
                prev->next = curr->next;
            }

            if (curr == TVAR::tail) {
                // Dacă este ultimul element
                TVAR::tail = prev;
            }

            // Eliberăm memoria pentru variabilă
            delete[] curr->nume;
            delete curr;

            return;
        }

        prev = curr;
        curr = curr->next;
    }

    std::cerr << "Variable " << n << " not found! Cannot remove.\n";
}


TVAR::TVAR(char* n, VarType t, double v) {
    this->nume = new char[strlen(n) + 1];
    strcpy(this->nume, n);
    this->tip = t;
    switch (t) {
        case INT_TYPE: val_int = (int)v; break;
        case FLOAT_TYPE: val_float = (float)v; break;
        case DOUBLE_TYPE: val_double = v; break;
    }
    this->next = NULL;
}

TVAR::TVAR() {
    TVAR::head = NULL;
    TVAR::tail = NULL;
}

int TVAR::exists(const char* n) {
    TVAR* tmp = TVAR::head;
    while (tmp != NULL) {
        if (strcmp(tmp->nume, n) == 0)
            return 1;
        tmp = tmp->next;
    }
    return 0;
}

void TVAR::add(char* n, VarType t, double v) {
    if (exists(n)) {
        cout << "Variable " << n << " already exists. Skipping addition.\n";
        return;
    }
    TVAR* elem = new TVAR(n, t, v);
    if (head == NULL) {
        TVAR::head = TVAR::tail = elem;
    } else {
        TVAR::tail->next = elem;
        TVAR::tail = elem;
    }
}

double TVAR::getValue(const char* n) {
    TVAR* tmp = TVAR::head;
    while (tmp != NULL) {
        if (strcmp(tmp->nume, n) == 0) {
            switch (tmp->tip) {
                case INT_TYPE: return tmp->val_int;
                case FLOAT_TYPE: return tmp->val_float;
                case DOUBLE_TYPE: return tmp->val_double;
            }
        }
        tmp = tmp->next;
    }
    cerr << "Variable " << n << " not found!\n";
    return 0.0;
}

VarType TVAR::getType(const char* n) {
    TVAR* tmp = TVAR::head;
    while (tmp != NULL) {
        if (strcmp(tmp->nume, n) == 0) {
            return tmp->tip;
        }
        tmp = tmp->next;
    }
    cerr << "Variable " << n << " not found!\n";
    return INT_TYPE; // Default, dacă variabila nu există
}

void TVAR::setValue(const char* n, double v, VarType t) {
    TVAR* tmp = TVAR::head;
    while (tmp != NULL) {
        if (strcmp(tmp->nume, n) == 0) {
            tmp->tip = t; // Actualizează tipul variabilei
            switch (t) {
                case INT_TYPE:
                    tmp->val_int = static_cast<int>(v); // Conversie sigură la int
                    break;
                case FLOAT_TYPE:
                    tmp->val_float = static_cast<float>(v); // Conversie sigură la float
                    break;
                case DOUBLE_TYPE:
                    tmp->val_double = v; // Fără conversie pentru double
                    break;
                default:
                    cerr << "Eroare: Tip necunoscut pentru variabila " << n << "!\n";
            }
            return;
        }
        tmp = tmp->next;
    }
    cerr << "Variable " << n << " not found! Cannot set value.\n";
}


void TVAR::printVars() {
    cout << "\nPrinting table of variables...\n";
    TVAR* tmp = TVAR::head;
    while (tmp != NULL) {
        cout << tmp->nume << " = ";
        switch (tmp->tip) {
            case INT_TYPE: cout << tmp->val_int << " (int)"; break;
            case FLOAT_TYPE: cout << tmp->val_float << " (float)"; break;
            case DOUBLE_TYPE: cout << tmp->val_double << " (double)"; break;
        }
        cout << "\n";
        tmp = tmp->next;
    }
}

TVAR* ts = new TVAR();

std::stack<TVAR*> tsStack;


void enterScope() {
    tsStack.push(new TVAR());
}


void exitScope() {
    if (!tsStack.empty()) {
        delete tsStack.top();
        tsStack.pop();
    } else {
        std::cerr << "Error: Attempt to exit nonexistent scope!" << std::endl;
        exit(1);
    }
}

TVAR* currentScope() {
    if (!tsStack.empty()) {
        return tsStack.top();
    }
    return ts;
}

void addVariable(const char* n, VarType t, double v) {
    TVAR* scope = currentScope();
    if (scope) {
        scope->add(const_cast<char*>(n), t, v);
    } else {
        std::cerr << "Error: No active scope to add variable!" << std::endl;
    }
}

int existsInCurrentScope(const char* n) {
    TVAR* scope = currentScope();
    return scope ? scope->exists(n) : 0;
}

void setValue(const char* n, double v, VarType t) {
    TVAR* scope = currentScope();
    if (scope && scope->exists(n)) {
        scope->setValue(n, v, t);
    } else if (ts && ts->exists(n)) {
        ts->setValue(n, v, t);
    } else {
        std::cerr << "Error: Variable " << n << " not declared!" << std::endl;
    }
}


VarType GetTypeLocal(const char* n)
{
    TVAR* scope=currentScope();
    return scope->getType(n);
}

int test_exist_local_var(const char* n)
{
    if(tsStack.empty())
    {
        return 0;
    } else if(existsInCurrentScope(n)==1)
    {
        return 1;
    }
    return 0;
}



double getValueLocal(const char* n) {
    TVAR* scope=currentScope();
    return scope->getValue(n);
}

// Funcție pentru a elimina spațiile albe dintr-un șir
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n");
    if (first == std::string::npos) return ""; // Dacă șirul este gol
    size_t last = str.find_last_not_of(" \t\n");
    return str.substr(first, (last - first + 1));
}

void handle_scanf(const std::vector<std::string>& formats, const std::vector<std::string>& variables) {

    std::cout << "Introduceti valorile pentru scanf: ";

    // Salvează file descriptor-ul original pentru stdin
    int original_stdin = dup(fileno(stdin));
    // Redirectează stdin către tastatură
    freopen("/dev/tty", "r", stdin);

    std::string input;
    std::getline(std::cin, input);
    printf("\n\n%s\n\n",input.c_str());

    // Restaurează stdin-ul original
    fflush(stdin);
    dup2(original_stdin, fileno(stdin));
    close(original_stdin);
    clearerr(stdin);



    // Împărțim inputul la spații pentru a obține valorile
    std::istringstream stream(input);
    std::vector<std::string> inputValues;
    std::string value;

    while (stream >> value) {
        inputValues.push_back(value); // Adăugăm fiecare valoare citită în vector
    }

    // Verificăm dacă numărul de valori introduse corespunde cu numărul de formate
    if (inputValues.size() != formats.size()) {
        std::cerr << "Eroare: Numărul de valori introduse (" << inputValues.size()
                  << ") nu corespunde cu numărul de variabile așteptate (" << formats.size() << ")." << std::endl;
        return;  // Terminăm funcția dacă numărul de valori nu corespunde
    }

    // Acum setăm valorile variabilelor conform tipurilor de date
    for (size_t i = 0; i < formats.size(); ++i) {
        std::string format = formats[i];
        std::string var = variables[i];

        // Verificăm dacă variabila începe cu '&' și o eliminăm
        if (var[0] == '&') {
            var = var.substr(1); // Eliminăm '&' din variabilă
        }
        std::string inputValue = inputValues[i];



        // Verificăm tipul de format și validăm fiecare valoare introdusă
        if (format == "d") { // Așteptăm un int
            try {
                double value = std::stod(inputValue); // Convertim valoarea introdusă în double
                std::cout << "Setăm valoarea pentru " << var << ": " << value << std::endl;
                ts->setValue(var.c_str(), value, INT_TYPE); // Fără conversie (este deja double)


            } catch (const std::invalid_argument& e) {
                std::cerr << "Eroare: Variabila " << var << " trebuie să fie de tip int." << std::endl;
                return;
            } catch (const std::out_of_range& e) {
                std::cerr << "Eroare: Valoare prea mare pentru int." << std::endl;
                return;
            }
        } else if (format == "f") { // Așteptăm un float
            try {
                double value = std::stod(inputValue); // Convertim valoarea introdusă în double
                std::cout << "Setăm valoarea pentru " << var << ": " << value << std::endl;
                ts->setValue(var.c_str(), value, FLOAT_TYPE); // Fără conversie (este deja double)

            } catch (const std::invalid_argument& e) {
                std::cerr << "Eroare: Variabila " << var << " trebuie să fie de tip float." << std::endl;
                return;
            } catch (const std::out_of_range& e) {
                std::cerr << "Eroare: Valoare prea mare pentru float." << std::endl;
                return;
            }
        } else if (format == "lf") { // Așteptăm un double
            try {
                double value = std::stod(inputValue); // Convertim valoarea introdusă în double
                std::cout << "Setăm valoarea pentru " << var << ": " << value << std::endl;
                ts->setValue(var.c_str(), value, DOUBLE_TYPE); // Fără conversie (este deja double)

            } catch (const std::invalid_argument& e) {
                std::cerr << "Eroare: Variabila " << var << " trebuie să fie de tip double." << std::endl;
                return;
            } catch (const std::out_of_range& e) {
                std::cerr << "Eroare: Valoare prea mare pentru double." << std::endl;
                return;
            }
        } else {
            std::cerr << "Eroare: Format necunoscut pentru " << var << "." << std::endl;
            return;
        }   
    }

    std::cout << "Input procesat cu succes!" << std::endl;
}


double valoare_globala_returnata_functie=0;

class TFUNCTIE {
    char* nume;
    VarType tip;                    // Tipul returnat de funcție
    std::vector<std::pair<char*, VarType>> parametri; // Listă de parametri cu numele și tipul lor
    std::vector<std::string> corp; // Corpul funcției (instrucțiunile în format text)


public:
    TFUNCTIE* next;

    using Parametru = std::variant<int, float, double>;

    TFUNCTIE(char* n, VarType t) : nume(strdup(n)), tip(t), next(nullptr) {}

    void adauga_parametru(char* nume_parametru, VarType tip_parametru) {
        parametri.emplace_back(strdup(nume_parametru), tip_parametru);
    }

    void adauga_instructiune(std::string instructiune) {
        corp.push_back(instructiune);
    }

    VarType get_tip() {
        return tip;
    }

    const char* get_nume() {
        return nume;
    }

    const std::vector<std::pair<char*, VarType>>& get_parametri() {
        return parametri;
    }

    const std::vector<std::string>& get_corp() {
        return corp;
    }

    

    void CallFunctie(const std::vector<Parametru>& parametrii) {
        // Verificăm dacă numărul parametrilor corespunde
        if (parametrii.size() != this->parametri.size()) {
            throw std::runtime_error("Număr incorect de parametri pentru funcție.");
        }

        // Verificăm tipurile parametrilor
        for (size_t i = 0; i < parametrii.size(); ++i) {
            const auto& param_declarat = this->parametri[i];
            const auto& param_primit = parametrii[i];

            // Determinăm tipul parametrului primit
            VarType tip_primit = std::visit([](auto&& value) -> VarType {
                using T = std::decay_t<decltype(value)>;
                if constexpr (std::is_same_v<T, int>) return INT_TYPE;
                else if constexpr (std::is_same_v<T, float>) return FLOAT_TYPE;
                else if constexpr (std::is_same_v<T, double>) return DOUBLE_TYPE;
                else throw std::runtime_error("Tip necunoscut de parametru primit.");
            }, param_primit);

            // Comparăm tipurile
            if (tip_primit != param_declarat.second) {
                throw std::runtime_error("Tipul parametrului primit nu corespunde cu cel declarat.");
            }
        }


        // Creăm un map pentru parametrii cu numele, tipul și valoarea lor
        std::unordered_map<std::string, std::pair<VarType, Parametru>> parametrii_map;

        for (size_t i = 0; i < parametrii.size(); ++i) {
            const auto& param_declarat = this->parametri[i];
            const auto& param_primit = parametrii[i];

            // Determinăm tipul parametrului primit
            VarType tip_primit = std::visit([](auto&& value) -> VarType {
                using T = std::decay_t<decltype(value)>;
                if constexpr (std::is_same_v<T, int>) return INT_TYPE;
                else if constexpr (std::is_same_v<T, float>) return FLOAT_TYPE;
                else if constexpr (std::is_same_v<T, double>) return DOUBLE_TYPE;
                else throw std::runtime_error("Tip necunoscut de parametru primit.");
            }, param_primit);

            // Comparăm tipurile
            if (tip_primit != param_declarat.second) {
                throw std::runtime_error("Tipul parametrului primit nu corespunde cu cel declarat.");
            }

            // Mapăm numele cu tipul și valoarea
            parametrii_map[param_declarat.first] = {param_declarat.second, param_primit};
        }

        // Adăugăm variabilele în TVAR* ts (sau în scopul curent dacă se folosește o stivă de scopuri)
        //std::cout << "Adăugăm variabilele în tabelul de simboluri:" << std::endl;

        for (const auto& [nume, info] : parametrii_map) {
            VarType tip = info.first;
            double valoare = std::visit([](auto&& value) { return static_cast<double>(value); }, info.second);

            // Adăugăm variabila în TVAR
            if (currentScope()) {
                currentScope()->add(const_cast<char*>(nume.c_str()), tip, valoare);
            } else {
                ts->add(const_cast<char*>(nume.c_str()), tip, valoare);
            }
        }


        for (const std::string& instr : corp) {
                // Intercalăm analiza unui string
                switch_to_string(instr.c_str()); // Trecem la string
                yyparse();
                restore_previous_buffer(); // Revenim la fișier
        }


        for (const auto& [nume, info] : parametrii_map) {
            // Verificăm dacă suntem într-un scope local sau global
            if (currentScope()) {
                if (currentScope()->exists(nume.c_str())) {
                    currentScope()->remove(nume.c_str());
                }
            } else if (ts->exists(nume.c_str())) {
                ts->remove(nume.c_str());
            }
        }

    }

};

// Lista globală de funcții
TFUNCTIE* functii_head = nullptr;
std::vector<TFUNCTIE::Parametru> parametrii;


// Adaugă o funcție în lista globală
void adauga_functie(TFUNCTIE* functie) {
    if (!functii_head) {
        functii_head = functie;
    } else {
        TFUNCTIE* temp = functii_head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = functie;
    }
}

// Găsește o funcție după nume
TFUNCTIE* gaseste_functie(const char* nume) {
    TFUNCTIE* temp = functii_head;
    while (temp) {
        if (strcmp(temp->get_nume(), nume) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}


void print_functie_by_name(const char* nume_functie) {
    // Găsim funcția după nume
    TFUNCTIE* functie = gaseste_functie(nume_functie);
    if (!functie) {
        std::cerr << "Funcția " << nume_functie << " nu a fost găsită!" << std::endl;
        return;
    }

    // Determinăm tipul funcției ca text
    std::string tip_functie;
    switch (functie->get_tip()) {
        case INT_TYPE: tip_functie = "int"; break;
        case FLOAT_TYPE: tip_functie = "float"; break;
        case DOUBLE_TYPE: tip_functie = "double"; break;
        default: tip_functie = "unknown"; break;
    }

    // Afișăm antetul funcției
    std::cout << tip_functie << " " << functie->get_nume() << "(";

    // Afișăm parametrii funcției
    const auto& parametri = functie->get_parametri();
    for (size_t i = 0; i < parametri.size(); ++i) {
        const auto& param = parametri[i];
        std::string param_type = (param.second == INT_TYPE ? "int" :
                                  param.second == FLOAT_TYPE ? "float" :
                                  param.second == DOUBLE_TYPE ? "double" : "unknown");
        std::cout << param_type << " " << param.first;
        if (i < parametri.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << ")" << std::endl;

    // Afișăm corpul funcției
    std::cout << "{" << std::endl;
    const auto& corp = functie->get_corp();
    for (const auto& linie : corp) {
        std::cout << "    " << linie<<std::endl; // Indentăm pentru lizibilitate
    }
    std::cout << "}" << std::endl;
}

std::string getFunctionNameFromVariable(const std::string& variable) {
    size_t len = variable.length();
    if (len == 0) {
        return ""; // Dacă șirul este gol
    }

    std::string longestMatch = "";
    size_t halfLen = len / 2;

    // Comparăm subșiruri de la 1 până la jumătate din lungimea șirului
    for (size_t i = 1; i <= halfLen; ++i) {
        std::string prefix = variable.substr(0, i);         // Prefix de lungime i
        std::string suffix = variable.substr(len - i, i);   // Sufix de lungime i

        if (prefix == suffix) { // Dacă sunt identice
            longestMatch = prefix; // Salvăm cea mai lungă potrivire
        }
    }

    return longestMatch;
}




#line 715 "ex1lab12.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "ex1lab12.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_TEXT_PRINTF = 3,            /* TOK_TEXT_PRINTF  */
  YYSYMBOL_TOK_PRINTF = 4,                 /* TOK_PRINTF  */
  YYSYMBOL_TOK_SCANF = 5,                  /* TOK_SCANF  */
  YYSYMBOL_TOK_PLUS = 6,                   /* TOK_PLUS  */
  YYSYMBOL_TOK_MINUS = 7,                  /* TOK_MINUS  */
  YYSYMBOL_TOK_MULTIPLY = 8,               /* TOK_MULTIPLY  */
  YYSYMBOL_TOK_DIVIDE = 9,                 /* TOK_DIVIDE  */
  YYSYMBOL_TOK_LEFT = 10,                  /* TOK_LEFT  */
  YYSYMBOL_TOK_RIGHT = 11,                 /* TOK_RIGHT  */
  YYSYMBOL_TOK_DECLARE = 12,               /* TOK_DECLARE  */
  YYSYMBOL_TOK_PRINT = 13,                 /* TOK_PRINT  */
  YYSYMBOL_TOK_ERROR = 14,                 /* TOK_ERROR  */
  YYSYMBOL_TOK_INT = 15,                   /* TOK_INT  */
  YYSYMBOL_TOK_FLOAT = 16,                 /* TOK_FLOAT  */
  YYSYMBOL_TOK_DOUBLE = 17,                /* TOK_DOUBLE  */
  YYSYMBOL_TOK_VOID = 18,                  /* TOK_VOID  */
  YYSYMBOL_TOK_IF = 19,                    /* TOK_IF  */
  YYSYMBOL_TOK_ELSE = 20,                  /* TOK_ELSE  */
  YYSYMBOL_TOK_WHILE = 21,                 /* TOK_WHILE  */
  YYSYMBOL_TOK_LBRACE = 22,                /* TOK_LBRACE  */
  YYSYMBOL_TOK_RBRACE = 23,                /* TOK_RBRACE  */
  YYSYMBOL_TOK_GT = 24,                    /* TOK_GT  */
  YYSYMBOL_TOK_LT = 25,                    /* TOK_LT  */
  YYSYMBOL_TOK_GE = 26,                    /* TOK_GE  */
  YYSYMBOL_TOK_LE = 27,                    /* TOK_LE  */
  YYSYMBOL_TOK_EQ = 28,                    /* TOK_EQ  */
  YYSYMBOL_TOK_NE = 29,                    /* TOK_NE  */
  YYSYMBOL_TOK_RETURN = 30,                /* TOK_RETURN  */
  YYSYMBOL_TOK_NUMBER_INT = 31,            /* TOK_NUMBER_INT  */
  YYSYMBOL_TOK_NUMBER_FLOAT = 32,          /* TOK_NUMBER_FLOAT  */
  YYSYMBOL_TOK_NUMBER_DOUBLE = 33,         /* TOK_NUMBER_DOUBLE  */
  YYSYMBOL_TOK_VARIABLE = 34,              /* TOK_VARIABLE  */
  YYSYMBOL_TOK_FUNCTION_BODY = 35,         /* TOK_FUNCTION_BODY  */
  YYSYMBOL_36_ = 36,                       /* ';'  */
  YYSYMBOL_37_ = 37,                       /* ','  */
  YYSYMBOL_38_ = 38,                       /* '&'  */
  YYSYMBOL_39_ = 39,                       /* '='  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_S = 41,                         /* S  */
  YYSYMBOL_StmtList = 42,                  /* StmtList  */
  YYSYMBOL_BlockStmt = 43,                 /* BlockStmt  */
  YYSYMBOL_44_1 = 44,                      /* $@1  */
  YYSYMBOL_FunctionDeclarationStmt = 45,   /* FunctionDeclarationStmt  */
  YYSYMBOL_VariableList = 46,              /* VariableList  */
  YYSYMBOL_AmpersandVariable = 47,         /* AmpersandVariable  */
  YYSYMBOL_ScanfStmt = 48,                 /* ScanfStmt  */
  YYSYMBOL_PrintfStmt = 49,                /* PrintfStmt  */
  YYSYMBOL_WhileStmt = 50,                 /* WhileStmt  */
  YYSYMBOL_IfStmt = 51,                    /* IfStmt  */
  YYSYMBOL_AuxIfFirst = 52,                /* AuxIfFirst  */
  YYSYMBOL_AuxIfSecond = 53,               /* AuxIfSecond  */
  YYSYMBOL_I = 54,                         /* I  */
  YYSYMBOL_ReturnStmt = 55,                /* ReturnStmt  */
  YYSYMBOL_E = 56,                         /* E  */
  YYSYMBOL_ArgumentListFunctie = 57,       /* ArgumentListFunctie  */
  YYSYMBOL_LogicalExpression = 58          /* LogicalExpression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  39
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   145

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    38,     2,
       2,     2,     2,     2,    37,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
       2,    39,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   687,   687,   693,   694,   695,   696,   697,   698,   699,
     700,   702,   708,   708,   717,   863,   883,   904,   908,   919,
     939,  1066,  1084,  1167,  1176,  1180,  1187,  1196,  1205,  1254,
    1273,  1293,  1311,  1364,  1386,  1408,  1432,  1440,  1461,  1464,
    1466,  1468,  1478,  1480,  1482,  1484,  1486,  1504,  1523,  1541,
    1569,  1624,  1679,  1683,  1687,  1691,  1697,  1703,  1709,  1717,
    1724,  1731,  1738,  1745,  1752
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOK_TEXT_PRINTF",
  "TOK_PRINTF", "TOK_SCANF", "TOK_PLUS", "TOK_MINUS", "TOK_MULTIPLY",
  "TOK_DIVIDE", "TOK_LEFT", "TOK_RIGHT", "TOK_DECLARE", "TOK_PRINT",
  "TOK_ERROR", "TOK_INT", "TOK_FLOAT", "TOK_DOUBLE", "TOK_VOID", "TOK_IF",
  "TOK_ELSE", "TOK_WHILE", "TOK_LBRACE", "TOK_RBRACE", "TOK_GT", "TOK_LT",
  "TOK_GE", "TOK_LE", "TOK_EQ", "TOK_NE", "TOK_RETURN", "TOK_NUMBER_INT",
  "TOK_NUMBER_FLOAT", "TOK_NUMBER_DOUBLE", "TOK_VARIABLE",
  "TOK_FUNCTION_BODY", "';'", "','", "'&'", "'='", "$accept", "S",
  "StmtList", "BlockStmt", "$@1", "FunctionDeclarationStmt",
  "VariableList", "AmpersandVariable", "ScanfStmt", "PrintfStmt",
  "WhileStmt", "IfStmt", "AuxIfFirst", "AuxIfSecond", "I", "ReturnStmt",
  "E", "ArgumentListFunctie", "LogicalExpression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-16)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       5,    -2,     7,     2,     4,    16,    18,    20,    31,   -16,
      22,    30,   -16,    77,   -16,     5,     5,     5,     5,     5,
       5,    34,     5,    90,    94,   -16,    43,    60,    75,    22,
      22,     5,    47,   -16,   -16,   -16,    88,     6,    22,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,     5,   -16,     0,    78,
      22,    22,    22,    59,   105,   106,    95,   108,   109,   111,
      83,    70,    22,    22,    22,    22,   -16,   100,   -16,    87,
      -5,    -5,   100,   100,   100,    22,    22,    22,    22,    22,
      22,   102,   103,   -16,    92,    93,    96,   -16,   -16,   -16,
     -16,   -16,     8,    35,    35,   -16,   -16,   -16,   -16,    97,
      12,   -16,    14,   100,   100,   100,   100,   100,   100,   -16,
       5,   -16,   -16,   -16,   -16,    79,   -16,    98,    62,    99,
       5,   110,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16,   -16,   113,   112,   107,   -16,     5,   -16,   114,   -16
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      11,     0,     0,     0,     0,     0,     0,     0,     0,    12,
       0,     0,    14,     0,     2,    11,    11,    11,    11,    11,
      11,     0,    11,     0,     0,    32,    29,    30,    31,     0,
       0,    11,     0,    43,    44,    45,    37,     0,     0,     1,
       8,     9,     7,     6,     5,     4,    11,    10,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    58,     0,     0,     0,     0,    36,    28,     3,     0,
       0,     0,    34,    35,    33,     0,     0,     0,     0,     0,
       0,     0,     0,    13,     0,     0,     0,    42,    52,    53,
      54,    50,     0,    38,    39,    40,    41,    21,    15,     0,
       0,    17,     0,    59,    60,    62,    63,    61,    64,    26,
      11,    46,    48,    47,    49,     0,    19,     0,     0,     0,
      11,     0,    55,    56,    57,    51,    22,    16,    18,    20,
      26,    23,     0,    24,     0,    27,    11,    27,     0,    25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -16,   -16,   -15,   -16,   -16,   -16,    57,    21,   -16,   -16,
     -16,   -16,    10,     1,   -16,   -16,    -4,   -16,   115
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    13,    14,    15,    31,    16,   100,   101,    17,    18,
      19,    20,   120,   136,    21,    22,    53,    92,    54
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      40,    41,    42,    43,    44,    45,    37,    47,    23,     1,
       2,    69,    62,    63,    64,    65,    56,    24,     3,   114,
       4,     5,     6,   117,     7,   119,     8,     9,    60,    98,
      29,    68,    32,    99,    67,    10,    25,    70,    26,    11,
      12,    30,    66,    64,    65,   115,    72,    73,    74,   118,
      27,   118,    28,    33,    34,    35,    36,    32,    93,    94,
      95,    96,    57,    58,    59,    62,    63,    64,    65,    38,
      46,   103,   104,   105,   106,   107,   108,    39,    33,    34,
      35,    36,    50,    75,    76,    77,    78,    79,    80,    62,
      63,    64,    65,    48,    87,   121,   127,    49,    61,    51,
      99,    88,    89,    90,    91,   130,    62,    63,    64,    65,
     122,   123,   124,   125,    52,    71,    81,    82,    83,    84,
      85,   137,    86,    97,   109,   110,   111,   112,   102,   135,
     113,   116,   134,   131,   126,   129,   133,   139,   138,   128,
     132,     0,     0,     0,     0,    55
};

static const yytype_int16 yycheck[] =
{
      15,    16,    17,    18,    19,    20,    10,    22,    10,     4,
       5,    11,     6,     7,     8,     9,    31,    10,    13,    11,
      15,    16,    17,    11,    19,    11,    21,    22,    32,    34,
      10,    46,    10,    38,    38,    30,    34,    37,    34,    34,
      35,    10,    36,     8,     9,    37,    50,    51,    52,    37,
      34,    37,    34,    31,    32,    33,    34,    10,    62,    63,
      64,    65,    15,    16,    17,     6,     7,     8,     9,    39,
      36,    75,    76,    77,    78,    79,    80,     0,    31,    32,
      33,    34,    39,    24,    25,    26,    27,    28,    29,     6,
       7,     8,     9,     3,    11,   110,    34,     3,    10,    39,
      38,    31,    32,    33,    34,   120,     6,     7,     8,     9,
      31,    32,    33,    34,    39,    37,    11,    11,    23,    11,
      11,   136,    11,    36,    22,    22,    34,    34,    71,    22,
      34,    34,    20,    23,    36,    36,    23,    23,   137,   118,
     130,    -1,    -1,    -1,    -1,    30
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,    13,    15,    16,    17,    19,    21,    22,
      30,    34,    35,    41,    42,    43,    45,    48,    49,    50,
      51,    54,    55,    10,    10,    34,    34,    34,    34,    10,
      10,    44,    10,    31,    32,    33,    34,    56,    39,     0,
      42,    42,    42,    42,    42,    42,    36,    42,     3,     3,
      39,    39,    39,    56,    58,    58,    42,    15,    16,    17,
      56,    10,     6,     7,     8,     9,    36,    56,    42,    11,
      37,    37,    56,    56,    56,    24,    25,    26,    27,    28,
      29,    11,    11,    23,    11,    11,    11,    11,    31,    32,
      33,    34,    57,    56,    56,    56,    56,    36,    34,    38,
      46,    47,    46,    56,    56,    56,    56,    56,    56,    22,
      22,    34,    34,    34,    11,    37,    34,    11,    37,    11,
      52,    42,    31,    32,    33,    34,    36,    34,    47,    36,
      42,    23,    52,    23,    20,    22,    53,    42,    53,    23
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    44,    43,    45,    46,    46,    46,    46,    47,
      48,    49,    49,    50,    51,    51,    52,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    55,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    58,
      58,    58,    58,    58,    58
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     2,     2,     2,     2,     2,     2,
       2,     0,     0,     4,     1,     1,     3,     1,     3,     2,
       7,     5,     7,     7,     9,    15,     0,     0,     3,     2,
       2,     2,     2,     4,     4,     4,     3,     1,     3,     3,
       3,     3,     3,     1,     1,     1,     4,     4,     4,     4,
       1,     3,     1,     1,     1,     3,     3,     3,     0,     3,
       3,     3,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 11: /* StmtList: %empty  */
#line 702 "ex1lab12.y"
  {
      (yyval.dval) = 0; // Valoare implicită pentru simbolul epsilon
  }
#line 1965 "ex1lab12.tab.c"
    break;

  case 12: /* $@1: %empty  */
#line 708 "ex1lab12.y"
               {
        enterScope();
    }
#line 1973 "ex1lab12.tab.c"
    break;

  case 13: /* BlockStmt: TOK_LBRACE $@1 StmtList TOK_RBRACE  */
#line 710 "ex1lab12.y"
                          {
        (yyval.dval) = (yyvsp[-1].dval);
        exitScope();
    }
#line 1982 "ex1lab12.tab.c"
    break;

  case 14: /* FunctionDeclarationStmt: TOK_FUNCTION_BODY  */
#line 718 "ex1lab12.y"
    {
        //printf("functie:\n%s\n\n\n",$1);

        std::string functionText((yyvsp[0].sir));

        // Eliminăm spațiile albe la început și la sfârșit
        functionText = trim(functionText);

        // Extragem poziția primelor delimitatoare
        size_t openParenPos = functionText.find("(");
        size_t closeParenPos = functionText.find(")");
        size_t openBracePos = functionText.find("{");
        size_t closeBracePos = functionText.rfind("}");

        // 1. Extragem tipul funcției (partea de dinainte de primul spațiu)
        std::string header = functionText.substr(0, openBracePos);
        header = trim(header);
        size_t firstSpace = header.find(" ");
        std::string tip_functie = header.substr(0, firstSpace);

        // 2. Extragem numele funcției (de la primul spațiu până la paranteza deschisă)
        std::string nume_functie = header.substr(firstSpace + 1, openParenPos - firstSpace - 1);

        // 3. Extragem lista de parametri (între parantezele rotunde)
        std::string parametrii_functie = functionText.substr(openParenPos + 1, closeParenPos - openParenPos - 1);

        // 4. Extragem corpul funcției (între acoladele { și })
        std::string corp_functie = functionText.substr(openBracePos + 1, closeBracePos - openBracePos - 1);
        corp_functie = trim(corp_functie);



        // Afișăm rezultatele pentru verificare
        // std::cout << "Tip funcție: " << tip_functie << std::endl;
        // std::cout << "Nume funcție: " << nume_functie << std::endl;
        // std::cout << "Parametrii funcție: " << parametrii_functie << std::endl;
        // std::cout << "Corp funcție: " << std::endl << corp_functie << std::endl;


        // Determinăm tipul de returnare
        VarType returnTypeEnum;
        if (tip_functie == "int") returnTypeEnum = INT_TYPE;
        else if (tip_functie == "float") returnTypeEnum = FLOAT_TYPE;
        else if (tip_functie == "double") returnTypeEnum = DOUBLE_TYPE;
        else {
            std::cerr << "Eroare: Tip necunoscut pentru funcție: " << tip_functie << std::endl;
            exit(1);
        }

        // Creăm o nouă funcție
        TFUNCTIE* functie_noua = new TFUNCTIE(strdup(nume_functie.c_str()), returnTypeEnum);

        // Parsăm parametrii
        std::istringstream paramStream(parametrii_functie);
        std::string param;
        while (std::getline(paramStream, param, ',')) {
            param = trim(param); // Eliminăm spațiile albe
            size_t spacePos = param.find_last_of(' ');
            std::string paramType = param.substr(0, spacePos);
            std::string paramName = param.substr(spacePos + 1);
            paramName =  nume_functie +paramName + nume_functie;

            VarType paramTypeEnum;
            if (paramType == "int") paramTypeEnum = INT_TYPE;
            else if (paramType == "float") paramTypeEnum = FLOAT_TYPE;
            else if (paramType == "double") paramTypeEnum = DOUBLE_TYPE;
            else {
                std::cerr << "Eroare: Tip necunoscut pentru parametru: " << paramType << std::endl;
                exit(1);
            }

            functie_noua->adauga_parametru(strdup(paramName.c_str()), paramTypeEnum);
        }


        
       // Parsăm corpul funcției
        std::istringstream bodyStream(corp_functie);
        std::string line;
        while (std::getline(bodyStream, line, ';')) { // Separați după ';'
            line = trim(line); // Eliminăm spațiile albe
            if (!line.empty()) {
                // Pentru fiecare parametru al funcției, căutăm și înlocuim în linie
                for (const auto& param : functie_noua->get_parametri()) {
                    std::string prefixedParam = param.first; // Numele stocat cu prefix și sufix
                    std::string originalParam = prefixedParam.substr(nume_functie.length(),
                                                                    prefixedParam.length() - 2 * nume_functie.length());
                    std::string wrappedParam = nume_functie + originalParam + nume_functie;

                    // Înlocuim toate aparițiile parametrului original în linie
                    size_t pos = 0;
                    while ((pos = line.find(originalParam, pos)) != std::string::npos) {
                        // Asigurăm că găsim un cuvânt întreg (nu parte din alt nume)
                        if ((pos == 0 || !isalnum(line[pos - 1])) && 
                            (pos + originalParam.size() == line.size() || !isalnum(line[pos + originalParam.size()]))) {
                            line.replace(pos, originalParam.size(), wrappedParam);
                            pos += wrappedParam.size();
                        } else {
                            pos += originalParam.size();
                        }
                    }
                }

                // Adăugăm punctul și virgula înapoi
                line += ";";

                // Adăugăm linia procesată în corpul funcției
                functie_noua->adauga_instructiune(line);
            }
        }
        // Adăugăm funcția în lista globală
        adauga_functie(functie_noua);




        //Afișăm detalii pentru verificare
        // std::cout << "Funcția " << functie_noua->get_nume() << " a fost adăugată!" << std::endl;
        // std::cout << "Tip: " << (functie_noua->get_tip() == INT_TYPE ? "int" : 
        //                         functie_noua->get_tip() == FLOAT_TYPE ? "float" : "double") << std::endl;

        // std::cout << "Parametrii:" << std::endl;
        // for (const auto& param : functie_noua->get_parametri()) {
        //     std::cout << "  " << param.first << ": " 
        //             << (param.second == INT_TYPE ? "int" : 
        //                 param.second == FLOAT_TYPE ? "float" : "double") << std::endl;
        // }

        // std::cout << "Corp funcție:" << std::endl;
        // for (const auto& instructiune : functie_noua->get_corp()) {
        //     std::cout << "  " << instructiune << std::endl;
        // }

        

    }
#line 2123 "ex1lab12.tab.c"
    break;

  case 15: /* VariableList: TOK_VARIABLE  */
#line 863 "ex1lab12.y"
                 {
        if(valoareif==-2)
        {// Extragem valoarea variabilei și tipul său
        if (ts->exists((yyvsp[0].sir))) {
            asprintf(&(yyval.sir), "%s", (yyvsp[0].sir)); // Reținem numele variabilei
            free((yyvsp[0].sir));
        } else if(tsStack.empty()==false)
        {
            if(existsInCurrentScope((yyvsp[0].sir))==1)
            {
                asprintf(&(yyval.sir), "%s", (yyvsp[0].sir)); // Reținem numele variabilei
                free((yyvsp[0].sir));
            }
        } 
        else {
            sprintf(msg, "Eroare: Variabila %s nu este declarată!", (yyvsp[0].sir));
            yyerror(msg);
            YYERROR;
        }}
    }
#line 2148 "ex1lab12.tab.c"
    break;

  case 16: /* VariableList: VariableList ',' TOK_VARIABLE  */
#line 883 "ex1lab12.y"
                                  {
            if(valoareif==-2)
        {if (ts->exists((yyvsp[0].sir))) {
            asprintf(&(yyval.sir), "%s,%s", (yyvsp[-2].sir), (yyvsp[0].sir)); // Adăugăm numele noii variabile la listă
            free((yyvsp[-2].sir));
            free((yyvsp[0].sir));
        } else if(tsStack.empty()==false)
        {
            if(existsInCurrentScope((yyvsp[0].sir))==1)
            {
                asprintf(&(yyval.sir), "%s,%s", (yyvsp[-2].sir), (yyvsp[0].sir)); // Adăugăm numele noii variabile la listă
                free((yyvsp[-2].sir));
                free((yyvsp[0].sir));
            }
        } 
        else {
            sprintf(msg, "Eroare: Variabila %s nu este declarată!", (yyvsp[0].sir));
            yyerror(msg);
            YYERROR;
        }
    }}
#line 2174 "ex1lab12.tab.c"
    break;

  case 17: /* VariableList: AmpersandVariable  */
#line 904 "ex1lab12.y"
                        {
        if(valoareif==-2)
{        (yyval.sir) = strdup((yyvsp[0].sir));} // Reținem prima variabilă
    }
#line 2183 "ex1lab12.tab.c"
    break;

  case 18: /* VariableList: VariableList ',' AmpersandVariable  */
#line 908 "ex1lab12.y"
                                         {
        if(valoareif==-2)
{        asprintf(&(yyval.sir), "%s,%s", (yyvsp[-2].sir), (yyvsp[0].sir)); // Adăugăm variabila la listă
        free((yyvsp[-2].sir));
        free((yyvsp[0].sir));}
    }
#line 2194 "ex1lab12.tab.c"
    break;

  case 19: /* AmpersandVariable: '&' TOK_VARIABLE  */
#line 919 "ex1lab12.y"
                     {
        if(valoareif==-2)
{        if (ts->exists((yyvsp[0].sir))) {
            asprintf(&(yyval.sir), "&%s", (yyvsp[0].sir));
        }  else if(tsStack.empty()==false)
        {
            if (existsInCurrentScope((yyvsp[0].sir))==1)
            {
                asprintf(&(yyval.sir), "&%s", (yyvsp[0].sir));
            }
        }
        else {
            sprintf(msg, "Eroare: Variabila %s nu este declaratăz!", (yyvsp[0].sir));
            yyerror(msg);
            YYERROR;
        }}
    }
#line 2216 "ex1lab12.tab.c"
    break;

  case 20: /* ScanfStmt: TOK_SCANF TOK_LEFT TOK_TEXT_PRINTF ',' VariableList TOK_RIGHT ';'  */
#line 940 "ex1lab12.y"
    {
        if(valoareif==-2)
        {// Obținem formatul și lista de variabile
        char *fmt = (yyvsp[-4].sir);  // Formatul de tipul "%d", "%f", "%lf" etc.
        char *vars = (yyvsp[-2].sir);  // Lista de variabile (de exemplu: &a, &b, &c)
        
        printf("fmt=%s\nvars=%s\n",fmt,vars);



        // Creăm un vector de formate și un vector de variabile
        std::vector<std::string> formats;
        std::vector<std::string> variables;

        // Parcurgem str1 și împărțim la '%'
        std::string temp;
        std::istringstream stream1(fmt);
        while (std::getline(stream1, temp, '%')) {
            temp = trim(temp); // Elimină spațiile albe din format
    if (!temp.empty()) { // Ignorăm prima parte goală
        formats.push_back(temp);
    }
        }

        // Parcurgem str2 și împărțim la ','
        std::istringstream stream2(vars);
        while (std::getline(stream2, temp, ',')) {
            if (!temp.empty()) { // Ignorăm părțile goale
                variables.push_back(temp);
            }
        }


        // Verificăm dacă numărul de formate și variabile corespunde
        if (formats.size() == variables.size()) {

            for (size_t i = 0; i < formats.size(); ++i) {
                std::string temp1 = formats[i];
                std::string temp2 = variables[i];

                // Verificăm dacă variabila începe cu '&' și o eliminăm
                if (temp2[0] == '&') {
                    temp2 = temp2.substr(1); // Eliminăm '&' din variabilă
                }

                // Verificăm tipul pentru fiecare format
                if (temp1[0] == 'd') {
                    if (ts->exists(temp2.c_str())) {
                        if (ts->getType(temp2.c_str()) != INT_TYPE) {
                            sprintf(msg, "Eroare: Variabila %s nu este de tip INT pentru %%d.", temp2.c_str());
                            yyerror(msg);
                            YYERROR;
                        }
                    } else if(test_exist_local_var(temp2.c_str())==1)
                    {
                        if (ts->getType(temp2.c_str()) != INT_TYPE) {
                            sprintf(msg, "Eroare: Variabila %s nu este de tip INT pentru %%d.", temp2.c_str());
                            yyerror(msg);
                            YYERROR;
                        }
                    }
                    else {
                        sprintf(msg, "Eroare: Variabila %s nu este declarată!", temp2.c_str());
                        yyerror(msg);
                        YYERROR;
                    }
                } 
                else if (temp1[0] == 'f') {
                    if (ts->exists(temp2.c_str())) {
                        if (ts->getType(temp2.c_str()) != FLOAT_TYPE) {
                            sprintf(msg, "Eroare: Variabila %s nu este de tip FLOAT pentru %%f.", temp2.c_str());
                            yyerror(msg);
                            YYERROR;
                        }
                    } else if(test_exist_local_var(temp2.c_str())==1)
                    {
                        if (ts->getType(temp2.c_str()) != FLOAT_TYPE) {
                            sprintf(msg, "Eroare: Variabila %s nu este de tip FLOAT pentru %%f.", temp2.c_str());
                            yyerror(msg);
                            YYERROR;
                        }
                    }
                    else {
                        sprintf(msg, "Eroare: Variabila %s nu este declarată!", temp2.c_str());
                        yyerror(msg);
                        YYERROR;
                    }
                } 
                else if (temp1[0] == 'l' && temp1[1] == 'f') {
                    if (ts->exists(temp2.c_str())) {
                        if (ts->getType(temp2.c_str()) != DOUBLE_TYPE) {
                            sprintf(msg, "Eroare: Variabila %s nu este de tip DOUBLE pentru %%lf.", temp2.c_str());
                            yyerror(msg);
                            YYERROR;
                        }
                    } else if(test_exist_local_var(temp2.c_str())==1)
                    {
                        if (ts->getType(temp2.c_str()) != DOUBLE_TYPE) {
                            sprintf(msg, "Eroare: Variabila %s nu este de tip DOUBLE pentru %%lf.", temp2.c_str());
                            yyerror(msg);
                            YYERROR;
                        }
                    }
                    else {
                        sprintf(msg, "Eroare: Variabila %s nu este declarată!", temp2.c_str());
                        yyerror(msg);
                        YYERROR;
                    }
                } 
                else {
                    sprintf(msg, "Eroare: Format necunoscut %%s pentru variabila %s.", temp2.c_str());
                    yyerror(msg);
                    YYERROR;
                }
            }
             printf("Apel corect pentru scanf cu variabile validate.\n");
            handle_scanf(formats,variables);
        } else {
            printf("apel incorect pentru scanf deoarece numarul de variabile nu sunt egale\n");
        }
    }}
#line 2342 "ex1lab12.tab.c"
    break;

  case 21: /* PrintfStmt: TOK_PRINTF TOK_LEFT TOK_TEXT_PRINTF TOK_RIGHT ';'  */
#line 1066 "ex1lab12.y"
                                                      {
        //printf("%s\n", $3); // Afișăm textul fix
        if(valoareif==-2)
        {        
            for (char* c = (yyvsp[-2].sir); *c; ++c) {
                if (*c == '\\' && *(c + 1) == 'n') {
                    printf("\n");
                    c++;  // Skip 'n'
                    continue;
                } else {
                    printf("%c",*c);
                }
            }

        free((yyvsp[-2].sir));  
        }         // Eliberăm memoria textului
    }
#line 2364 "ex1lab12.tab.c"
    break;

  case 22: /* PrintfStmt: TOK_PRINTF TOK_LEFT TOK_TEXT_PRINTF ',' VariableList TOK_RIGHT ';'  */
#line 1084 "ex1lab12.y"
                                                                       {
        if(valoareif==-2)
       {std::vector<std::string> variableNames;
       char* token = strtok((yyvsp[-2].sir), ",");
       while (token != NULL) {
           variableNames.push_back(std::string(token));
           token = strtok(NULL, ",");
       }
       free((yyvsp[-2].sir));

       std::vector<std::pair<double, VarType>> values;
       for (auto& varName : variableNames) {

           if (!ts->exists(varName.c_str()) && test_exist_local_var(varName.c_str())==0) {
               sprintf(msg, "Eroare: Variabila %s nu este declarată!", varName.c_str());
               yyerror(msg);
               YYERROR;
           }


           if(ts->exists(varName.c_str()))
           {
                VarType type = ts->getType((char*)varName.c_str());
                values.push_back({ts->getValue((char*)varName.c_str()), type});
           } else if(test_exist_local_var(varName.c_str())==1)
           {
                VarType type = GetTypeLocal(varName.c_str());
                values.push_back({getValueLocal(varName.c_str()),type});
           }

       }

       int i = 0;
       for (char* c = (yyvsp[-4].sir); *c; ++c) {
            if (*c == '\\' && *(c + 1) == 'n') {
                printf("\n");
                c++;  // Skip 'n'
                continue;
            }
           if (*c == '%') {
               if (i >= values.size()) {
                   sprintf(msg, "Eroare: Număr insuficient de variabile pentru formatul specificat!");
                   yyerror(msg);
                   YYERROR;
               }

               if (*(c + 1) == 'l' && *(c + 2) == 'f') {
                   if (values[i].second != DOUBLE_TYPE) {
                       sprintf(msg, "Eroare: Se așteaptă tip DOUBLE pentru %%lf!");
                       yyerror(msg);
                       YYERROR;
                   }
                   printf("%lf", values[i++].first);
                   c += 2;
               } 
               else if (*(c + 1) == 'f') {
                   if (values[i].second != FLOAT_TYPE) {
                       sprintf(msg, "Eroare: Se așteaptă tip FLOAT pentru %%f!");
                       yyerror(msg);
                       YYERROR;
                   }
                   printf("%f", (float)values[i++].first);
                   c++;
               }
               else if (*(c + 1) == 'd') {
                   if (values[i].second != INT_TYPE) {
                       sprintf(msg, "Eroare: Se așteaptă tip INT pentru %%d!");
                       yyerror(msg);
                       YYERROR;
                   }
                   printf("%d", (int)values[i++].first);
                   c++;
               }
           } else {
               putchar(*c);
           }
       }
       //putchar('\n');
       free((yyvsp[-4].sir));
   }}
#line 2449 "ex1lab12.tab.c"
    break;

  case 23: /* WhileStmt: TOK_WHILE TOK_LEFT LogicalExpression TOK_RIGHT TOK_LBRACE StmtList TOK_RBRACE  */
#line 1168 "ex1lab12.y"
    {
        valoareif=-2;
    }
#line 2457 "ex1lab12.tab.c"
    break;

  case 24: /* IfStmt: TOK_IF TOK_LEFT LogicalExpression TOK_RIGHT TOK_LBRACE AuxIfFirst StmtList AuxIfFirst TOK_RBRACE  */
#line 1177 "ex1lab12.y"
    {
        valoareif=-2;
    }
#line 2465 "ex1lab12.tab.c"
    break;

  case 25: /* IfStmt: TOK_IF TOK_LEFT LogicalExpression TOK_RIGHT TOK_LBRACE AuxIfFirst StmtList AuxIfFirst TOK_RBRACE TOK_ELSE TOK_LBRACE AuxIfSecond StmtList AuxIfSecond TOK_RBRACE  */
#line 1181 "ex1lab12.y"
    {
        valoareif=-2;
    }
#line 2473 "ex1lab12.tab.c"
    break;

  case 26: /* AuxIfFirst: %empty  */
#line 1187 "ex1lab12.y"
    {
        if (valoareif==1)
            valoareif=-2;
        else if(valoareif!=2)
            valoareif=0;
    }
#line 2484 "ex1lab12.tab.c"
    break;

  case 27: /* AuxIfSecond: %empty  */
#line 1196 "ex1lab12.y"
    { 
        if (valoareif==2) 
            valoareif=-2;
        else if(valoareif!=1)
            valoareif=0;
    }
#line 2495 "ex1lab12.tab.c"
    break;

  case 28: /* I: TOK_VARIABLE '=' E  */
#line 1205 "ex1lab12.y"
                       {
    if(valoareif==-2){
        if (ts != NULL) {
            if (ts->exists((yyvsp[-2].sir)) == 1) {
                VarType varType = ts->getType((yyvsp[-2].sir));
                switch (varType) {
                    case INT_TYPE:
                        if ((yyvsp[0].dval) < INT_MIN_LIMIT || (yyvsp[0].dval) > INT_MAX_LIMIT) {
                            sprintf(msg, "%d:%d Eroare semantica: Depășire a limitelor pentru tipul INT la variabila %s!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
                            yyerror(msg);
                            YYERROR;
                        }
                        ts->setValue((yyvsp[-2].sir), (int)(yyvsp[0].dval), INT_TYPE); // Conversie explicită la int
                        break;
                    case FLOAT_TYPE:
                        if ((yyvsp[0].dval) < FLOAT_MIN_LIMIT || (yyvsp[0].dval) > FLOAT_MAX_LIMIT) {
                            sprintf(msg, "%d:%d Eroare semantica: Depășire a limitelor pentru tipul FLOAT la variabila %s!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
                            yyerror(msg);
                            YYERROR;
                        }
                        ts->setValue((yyvsp[-2].sir), (float)(yyvsp[0].dval), FLOAT_TYPE); // Conversie explicită la float
                        break;
                    case DOUBLE_TYPE:
                        if ((yyvsp[0].dval) < DOUBLE_MIN_LIMIT || (yyvsp[0].dval) > DOUBLE_MAX_LIMIT) {
                            sprintf(msg, "%d:%d Eroare semantica: Depășire a limitelor pentru tipul DOUBLE la variabila %s!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
                            yyerror(msg);
                            YYERROR;
                        }
                        ts->setValue((yyvsp[-2].sir), (yyvsp[0].dval), DOUBLE_TYPE); // Fără conversie (este deja double)
                        break;
                    default:
                        sprintf(msg, "%d:%d Eroare semantica: Tip necunoscut pentru variabila %s!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
                        yyerror(msg);
                        YYERROR;
                }
            } if (existsInCurrentScope((yyvsp[-2].sir))==1)
            {
                setValue((yyvsp[-2].sir),(yyvsp[0].dval),GetTypeLocal((yyvsp[-2].sir)));
            } else {
                sprintf(msg, "%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
                yyerror(msg);
                YYERROR;
            }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
            yyerror(msg);
            YYERROR;
        }
    }}
#line 2549 "ex1lab12.tab.c"
    break;

  case 29: /* I: TOK_INT TOK_VARIABLE  */
#line 1254 "ex1lab12.y"
                         {
    if(valoareif==-2)
        {if (ts->exists((yyvsp[0].sir)) == 0) {
            if (tsStack.empty())
                {
                    ts->add((yyvsp[0].sir), INT_TYPE, 0);
                } // Adăugare variabilă de tip int cu valoare implicită 0
            else 
                {
                    addVariable((yyvsp[0].sir),INT_TYPE,0);
                    
                }
        } else 
        {
            sprintf(msg, "%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[0]).first_line, (yylsp[0]).first_column, (yyvsp[0].sir));
            yyerror(msg);
            YYERROR;
        }
    }}
#line 2573 "ex1lab12.tab.c"
    break;

  case 30: /* I: TOK_FLOAT TOK_VARIABLE  */
#line 1273 "ex1lab12.y"
                           {
    if(valoareif==-2)
        {if (ts->exists((yyvsp[0].sir)) == 0) {
            if (tsStack.empty())
                {
                    ts->add((yyvsp[0].sir), FLOAT_TYPE, 0);
                    printf("adaugare variabila %s float in variabile globale\n",(yyvsp[0].sir));
                } // Adăugare variabilă de tip float cu valoare implicită 0
            else 
                {
                    printf("adaugare variabila %s float in variabile locale\n",(yyvsp[0].sir));
                    addVariable((yyvsp[0].sir),FLOAT_TYPE,0);
                    
                }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[0]).first_line, (yylsp[0]).first_column, (yyvsp[0].sir));
            yyerror(msg);
            YYERROR;
        }
    }}
#line 2598 "ex1lab12.tab.c"
    break;

  case 31: /* I: TOK_DOUBLE TOK_VARIABLE  */
#line 1293 "ex1lab12.y"
                            {
    if(valoareif==-2)
        {if (ts->exists((yyvsp[0].sir)) == 0) {
            if (tsStack.empty())
                {
                    ts->add((yyvsp[0].sir), DOUBLE_TYPE, 0);
                } // Adăugare variabilă de tip double cu valoare implicită 0
            else 
                {
                    addVariable((yyvsp[0].sir),DOUBLE_TYPE,0);
                    
                }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[0]).first_line, (yylsp[0]).first_column, (yyvsp[0].sir));
            yyerror(msg);
            YYERROR;
        }
    }}
#line 2621 "ex1lab12.tab.c"
    break;

  case 32: /* I: TOK_PRINT TOK_VARIABLE  */
#line 1311 "ex1lab12.y"
                           {
    if(valoareif==-2)
        {if (ts != NULL) {
            if (ts->exists((yyvsp[0].sir)) == 1) {
                VarType varType = ts->getType((yyvsp[0].sir));
                switch (varType) {
                    case INT_TYPE:
                        printf("%d\n", (int)ts->getValue((yyvsp[0].sir)));
                        break;
                    case FLOAT_TYPE:
                        printf("%f\n", (float)ts->getValue((yyvsp[0].sir)));
                        break;
                    case DOUBLE_TYPE:
                        printf("%lf\n", ts->getValue((yyvsp[0].sir)));
                        break;
                    default:
                        sprintf(msg, "%d:%d Eroare semantica: Tip necunoscut pentru variabila %s!", (yylsp[-1]).first_line, (yylsp[-1]).first_column, (yyvsp[0].sir));
                        yyerror(msg);
                        YYERROR;
                }
            } else if(tsStack.empty()==false)
            {
                if(existsInCurrentScope((yyvsp[0].sir))==1)
                {
                    VarType varType = GetTypeLocal((yyvsp[0].sir));
                    switch (varType) {
                        case INT_TYPE:
                            printf("%d\n", (int)getValueLocal((yyvsp[0].sir)));
                            break;
                        case FLOAT_TYPE:
                            printf("%f\n", (float)getValueLocal((yyvsp[0].sir)));
                            break;
                        case DOUBLE_TYPE:
                            printf("%lf\n", getValueLocal((yyvsp[0].sir)));
                            break;
                        default:
                            sprintf(msg, "%d:%d Eroare semantica: Tip necunoscut pentru variabila %s!", (yylsp[-1]).first_line, (yylsp[-1]).first_column, (yyvsp[0].sir));
                            yyerror(msg);
                            YYERROR;
                    }
                }
            }
            else {
                sprintf(msg, "%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", (yylsp[-1]).first_line, (yylsp[-1]).first_column, (yyvsp[0].sir));
                yyerror(msg);
                YYERROR;
            }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", (yylsp[-1]).first_line, (yylsp[-1]).first_column, (yyvsp[0].sir));
            yyerror(msg);
            YYERROR;
        }
    }}
#line 2679 "ex1lab12.tab.c"
    break;

  case 33: /* I: TOK_DOUBLE TOK_VARIABLE '=' E  */
#line 1364 "ex1lab12.y"
                                    {
        if(valoareif==-2)
        {if (ts->exists((yyvsp[-2].sir)) == 0) {
            if ((yyvsp[0].dval) < DOUBLE_MIN_LIMIT || (yyvsp[0].dval) > DOUBLE_MAX_LIMIT) {
                sprintf(msg, "%d:%d Eroare semantica: Depășire a limitelor pentru tipul DOUBLE la variabila %s!", (yylsp[-3]).first_line, (yylsp[-3]).first_column, (yyvsp[-2].sir));
                yyerror(msg);
                YYERROR;
            }

            if(tsStack.empty())
            {
                ts->add((yyvsp[-2].sir), DOUBLE_TYPE, (yyvsp[0].dval)); // Adaugă variabila de tip double cu valoarea specificată
            } else 
            {
                addVariable((yyvsp[-2].sir),DOUBLE_TYPE,(yyvsp[0].dval));
            }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
            yyerror(msg);
            YYERROR;
        }
    }}
#line 2706 "ex1lab12.tab.c"
    break;

  case 34: /* I: TOK_INT TOK_VARIABLE '=' E  */
#line 1386 "ex1lab12.y"
                                 {
        if(valoareif==-2)
        {if (ts->exists((yyvsp[-2].sir)) == 0) {
            if ((yyvsp[0].dval) < INT_MIN_LIMIT || (yyvsp[0].dval) > INT_MAX_LIMIT) {
                sprintf(msg, "%d:%d Eroare semantica: Depășire a limitelor pentru tipul INT la variabila %s!", (yylsp[-3]).first_line, (yylsp[-3]).first_column, (yyvsp[-2].sir));
                yyerror(msg);
                YYERROR;
            }

            if(tsStack.empty())
            {
                ts->add((yyvsp[-2].sir), INT_TYPE, (yyvsp[0].dval)); // Adaugă variabila de tip INT cu valoarea specificată
            } else 
            {
                addVariable((yyvsp[-2].sir),INT_TYPE,(yyvsp[0].dval));
            }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
            yyerror(msg);
            YYERROR;
        }
    }}
#line 2733 "ex1lab12.tab.c"
    break;

  case 35: /* I: TOK_FLOAT TOK_VARIABLE '=' E  */
#line 1408 "ex1lab12.y"
                                   {
        if(valoareif==-2)
        {if (ts->exists((yyvsp[-2].sir)) == 0) {
            if ((yyvsp[0].dval) < FLOAT_MIN_LIMIT || (yyvsp[0].dval) > FLOAT_MAX_LIMIT) {
                sprintf(msg, "%d:%d Eroare semantica: Depășire a limitelor pentru tipul FLOAT la variabila %s!", (yylsp[-3]).first_line, (yylsp[-3]).first_column, (yyvsp[-2].sir));
                yyerror(msg);
                YYERROR;
            }

            if(tsStack.empty())
            {
                ts->add((yyvsp[-2].sir), FLOAT_TYPE, (yyvsp[0].dval)); // Adaugă variabila de tip FLOAT cu valoarea specificată
            } else 
            {
                addVariable((yyvsp[-2].sir),FLOAT_TYPE,(yyvsp[0].dval));
            }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[-2].sir));
            yyerror(msg);
            YYERROR;
        }
    }}
#line 2760 "ex1lab12.tab.c"
    break;

  case 36: /* ReturnStmt: TOK_RETURN E ';'  */
#line 1432 "ex1lab12.y"
                              {
    // Exemplu de variabilă din expresia evaluată
    valoare_globala_returnata_functie=(yyvsp[-1].dval);
    printf("dupa return val globala este %lf\n",valoare_globala_returnata_functie);
    }
#line 2770 "ex1lab12.tab.c"
    break;

  case 37: /* E: TOK_VARIABLE  */
#line 1440 "ex1lab12.y"
                 {
    if(valoareif==-2)
        {if (ts->exists((yyvsp[0].sir))) {
            (yyval.dval) = ts->getValue((yyvsp[0].sir)); // Obține valoarea variabilei
        } else if(tsStack.empty()==false)
        {
            if(existsInCurrentScope((yyvsp[0].sir))==1)
            {
                (yyval.dval)=getValueLocal((yyvsp[0].sir));
            } else {
                sprintf(msg, "%d:%d Eroare semantica: Variabila %s nu este declarata!", (yylsp[0]).first_line, (yylsp[0]).first_column, (yyvsp[0].sir));
                yyerror(msg);
                YYERROR;
            }
        }
        else {
            sprintf(msg, "%d:%d Eroare semantica: Variabila %s nu este declarata!", (yylsp[0]).first_line, (yylsp[0]).first_column, (yyvsp[0].sir));
            yyerror(msg);
            YYERROR;
        }
    }}
#line 2796 "ex1lab12.tab.c"
    break;

  case 38: /* E: E TOK_PLUS E  */
#line 1461 "ex1lab12.y"
                 { 
    if(valoareif==-2)
    {(yyval.dval) = (yyvsp[-2].dval) + (yyvsp[0].dval);} }
#line 2804 "ex1lab12.tab.c"
    break;

  case 39: /* E: E TOK_MINUS E  */
#line 1464 "ex1lab12.y"
                  { if(valoareif==-2)
  (yyval.dval) = (yyvsp[-2].dval) - (yyvsp[0].dval); }
#line 2811 "ex1lab12.tab.c"
    break;

  case 40: /* E: E TOK_MULTIPLY E  */
#line 1466 "ex1lab12.y"
                     { if(valoareif==-2)
  (yyval.dval) = (yyvsp[-2].dval) * (yyvsp[0].dval); }
#line 2818 "ex1lab12.tab.c"
    break;

  case 41: /* E: E TOK_DIVIDE E  */
#line 1468 "ex1lab12.y"
                   {
    if(valoareif==-2)
{        if ((yyvsp[0].dval) == 0) {
            sprintf(msg, "%d:%d Eroare semantica: Impartire la zero!", (yylsp[-2]).first_line, (yylsp[-2]).first_column);
            yyerror(msg);
            YYERROR;
        } else {
            (yyval.dval) = (yyvsp[-2].dval) / (yyvsp[0].dval);
        }}
    }
#line 2833 "ex1lab12.tab.c"
    break;

  case 42: /* E: TOK_LEFT E TOK_RIGHT  */
#line 1478 "ex1lab12.y"
                         { if(valoareif==-2)
  (yyval.dval) = (yyvsp[-1].dval); }
#line 2840 "ex1lab12.tab.c"
    break;

  case 43: /* E: TOK_NUMBER_INT  */
#line 1480 "ex1lab12.y"
                   { if(valoareif==-2)
  (yyval.dval) = (yyvsp[0].dval); }
#line 2847 "ex1lab12.tab.c"
    break;

  case 44: /* E: TOK_NUMBER_FLOAT  */
#line 1482 "ex1lab12.y"
                     { if(valoareif==-2)
  (yyval.dval) = (yyvsp[0].dval); }
#line 2854 "ex1lab12.tab.c"
    break;

  case 45: /* E: TOK_NUMBER_DOUBLE  */
#line 1484 "ex1lab12.y"
                      { if(valoareif==-2)
  (yyval.dval) = (yyvsp[0].dval); }
#line 2861 "ex1lab12.tab.c"
    break;

  case 46: /* E: TOK_LEFT TOK_INT TOK_RIGHT TOK_VARIABLE  */
#line 1486 "ex1lab12.y"
                                            {
    if(valoareif==-2)
    {if(ts->exists((yyvsp[0].sir)))
    {
        int value=(int)ts->getValue((yyvsp[0].sir));
        (yyval.dval) = value; // Rezultatul expresiei
        //printf("Casting '%s' to int: %d\n", $4, value);
    } else if(existsInCurrentScope((yyvsp[0].sir))==1)
    {
        int value = (int)getValueLocal((yyvsp[0].sir));
        (yyval.dval) = value; // Rezultatul expresiei
        //printf("Casting '%s' to int: %d\n", $4, value);
    } else {
        sprintf(msg, "%d:%d Eroare semantica: Variabila %s nu este declarata!", (yylsp[-3]).first_line, (yylsp[-3]).first_column, (yyvsp[0].sir));
        yyerror(msg);
        YYERROR;
    }  
  }}
#line 2884 "ex1lab12.tab.c"
    break;

  case 47: /* E: TOK_LEFT TOK_DOUBLE TOK_RIGHT TOK_VARIABLE  */
#line 1504 "ex1lab12.y"
                                               {
    if(valoareif==-2)
   { if(ts->exists((yyvsp[0].sir)))
    {
        double value=(double)ts->getValue((yyvsp[0].sir));
        (yyval.dval) = value; // Rezultatul expresiei
        //printf("Casting '%s' to double: %lf\n", $4, value);
    } else if(existsInCurrentScope((yyvsp[0].sir))==1)
    {
        double value = (double)getValueLocal((yyvsp[0].sir));
        (yyval.dval) = value; // Rezultatul expresiei
        //printf("Casting '%s' to double: %lf\n", $4, value);
    } else {
        sprintf(msg, "%d:%d Eroare semantica: Variabila %s nu este declarata!", (yylsp[-3]).first_line, (yylsp[-3]).first_column, (yyvsp[0].sir));
        yyerror(msg);
        YYERROR;
    }
    
  }}
#line 2908 "ex1lab12.tab.c"
    break;

  case 48: /* E: TOK_LEFT TOK_FLOAT TOK_RIGHT TOK_VARIABLE  */
#line 1523 "ex1lab12.y"
                                              {
    if(valoareif==-2){
    if(ts->exists((yyvsp[0].sir)))
    {
        float value=(float)ts->getValue((yyvsp[0].sir));
        (yyval.dval) = value; // Rezultatul expresiei
        //printf("Casting '%s' to float: %f\n", $4, value);
    } else if(existsInCurrentScope((yyvsp[0].sir))==1)
    {
        float value = (float)getValueLocal((yyvsp[0].sir));
        (yyval.dval) = value; // Rezultatul expresiei
        //printf("Casting '%s' to float: %f\n", $4, value);
    } else {
        sprintf(msg, "%d:%d Eroare semantica: Variabila %s nu este declarata!", (yylsp[-3]).first_line, (yylsp[-3]).first_column, (yyvsp[0].sir));
        yyerror(msg);
        YYERROR;
    }
  }}
#line 2931 "ex1lab12.tab.c"
    break;

  case 49: /* E: TOK_VARIABLE TOK_LEFT ArgumentListFunctie TOK_RIGHT  */
#line 1541 "ex1lab12.y"
                                                        {
    if(valoareif==-2){
        TFUNCTIE* functie = gaseste_functie((yyvsp[-3].sir));
        if (!functie) {
            sprintf(msg, "Eroare: Funcția %s nu a fost găsită!", (yyvsp[-3].sir));
            yyerror(msg);
            YYERROR;
        }

        try {
            // Apelăm funcția și obținem rezultatul
            
            
            functie->CallFunctie(parametrii);
            parametrii.clear();

            (yyval.dval)=valoare_globala_returnata_functie;
            valoare_globala_returnata_functie=0;

        } catch (const std::exception& e) {
            sprintf(msg, "Eroare la apelul funcției %s: %s", (yyvsp[-3].sir), e.what());
            yyerror(msg);
            YYERROR;
        }
    }}
#line 2961 "ex1lab12.tab.c"
    break;

  case 50: /* ArgumentListFunctie: TOK_VARIABLE  */
#line 1570 "ex1lab12.y"
    {
        if(valoareif==-2){
        if (ts->exists((yyvsp[0].sir))) {
            VarType varType = ts->getType((yyvsp[0].sir)); // Obținem tipul variabilei
            switch (varType) {
                case INT_TYPE: {
                    int for_push = (int)ts->getValue((yyvsp[0].sir)); // Creăm variabila pentru int
                    parametrii.push_back(for_push);       // Adăugăm în vector
                    break;
                }
                case FLOAT_TYPE: {
                    float for_push = (float)ts->getValue((yyvsp[0].sir)); // Creăm variabila pentru float
                    parametrii.push_back(for_push);           // Adăugăm în vector
                    break;
                }
                case DOUBLE_TYPE: {
                    double for_push = ts->getValue((yyvsp[0].sir)); // Creăm variabila pentru double
                    parametrii.push_back(for_push);     // Adăugăm în vector
                    break;
                }
                default:
                    sprintf(msg, "Eroare: Tip necunoscut pentru variabila %s!", (yyvsp[0].sir));
                    yyerror(msg);
                    YYERROR;
            }
        } else if (!tsStack.empty() && existsInCurrentScope((yyvsp[0].sir))) {
            VarType varType = GetTypeLocal((yyvsp[0].sir)); // Obținem tipul variabilei din scope-ul local
            switch (varType) {
                case INT_TYPE: {
                    int for_push = (int)getValueLocal((yyvsp[0].sir)); // Creăm variabila pentru int
                    parametrii.push_back(for_push);       // Adăugăm în vector
                    break;
                }
                case FLOAT_TYPE: {
                    float for_push = (float)getValueLocal((yyvsp[0].sir)); // Creăm variabila pentru float
                    parametrii.push_back(for_push);           // Adăugăm în vector
                    break;
                }
                case DOUBLE_TYPE: {
                    double for_push = getValueLocal((yyvsp[0].sir)); // Creăm variabila pentru double
                    parametrii.push_back(for_push);     // Adăugăm în vector
                    break;
                }
                default:
                    sprintf(msg, "Eroare: Tip necunoscut pentru variabila %s!", (yyvsp[0].sir));
                    yyerror(msg);
                    YYERROR;
            }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Variabila %s nu este declarata!", (yylsp[0]).first_line, (yylsp[0]).first_column, (yyvsp[0].sir));
            yyerror(msg);
            YYERROR;
        }
    }}
#line 3020 "ex1lab12.tab.c"
    break;

  case 51: /* ArgumentListFunctie: ArgumentListFunctie ',' TOK_VARIABLE  */
#line 1625 "ex1lab12.y"
    {
        if(valoareif==-2){
        if (ts->exists((yyvsp[0].sir))) {
            VarType varType = ts->getType((yyvsp[0].sir)); // Obținem tipul variabilei
            switch (varType) {
                case INT_TYPE: {
                    int for_push = (int)ts->getValue((yyvsp[0].sir)); // Creăm variabila pentru int
                    parametrii.push_back(for_push);       // Adăugăm în vector
                    break;
                }
                case FLOAT_TYPE: {
                    float for_push = (float)ts->getValue((yyvsp[0].sir)); // Creăm variabila pentru float
                    parametrii.push_back(for_push);           // Adăugăm în vector
                    break;
                }
                case DOUBLE_TYPE: {
                    double for_push = ts->getValue((yyvsp[0].sir)); // Creăm variabila pentru double
                    parametrii.push_back(for_push);     // Adăugăm în vector
                    break;
                }
                default:
                    sprintf(msg, "Eroare: Tip necunoscut pentru variabila %s!", (yyvsp[0].sir));
                    yyerror(msg);
                    YYERROR;
            }
        } else if (!tsStack.empty() && existsInCurrentScope((yyvsp[0].sir))) {
            VarType varType = GetTypeLocal((yyvsp[0].sir)); // Obținem tipul variabilei din scope-ul local
            switch (varType) {
                case INT_TYPE: {
                    int for_push = (int)getValueLocal((yyvsp[0].sir)); // Creăm variabila pentru int
                    parametrii.push_back(for_push);       // Adăugăm în vector
                    break;
                }
                case FLOAT_TYPE: {
                    float for_push = (float)getValueLocal((yyvsp[0].sir)); // Creăm variabila pentru float
                    parametrii.push_back(for_push);           // Adăugăm în vector
                    break;
                }
                case DOUBLE_TYPE: {
                    double for_push = getValueLocal((yyvsp[0].sir)); // Creăm variabila pentru double
                    parametrii.push_back(for_push);     // Adăugăm în vector
                    break;
                }
                default:
                    sprintf(msg, "Eroare: Tip necunoscut pentru variabila %s!", (yyvsp[0].sir));
                    yyerror(msg);
                    YYERROR;
            }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Variabila %s nu este declarata!", (yylsp[-2]).first_line, (yylsp[-2]).first_column, (yyvsp[0].sir));
            yyerror(msg);
            YYERROR;
        }
    }}
#line 3079 "ex1lab12.tab.c"
    break;

  case 52: /* ArgumentListFunctie: TOK_NUMBER_INT  */
#line 1679 "ex1lab12.y"
                     { 
        if(valoareif==-2)
{        int for_push = (yyvsp[0].dval);
        parametrii.push_back(for_push); }}
#line 3088 "ex1lab12.tab.c"
    break;

  case 53: /* ArgumentListFunctie: TOK_NUMBER_FLOAT  */
#line 1683 "ex1lab12.y"
                       {
        if(valoareif==-2)
{    float for_push = (yyvsp[0].dval);
    parametrii.push_back(for_push); }}
#line 3097 "ex1lab12.tab.c"
    break;

  case 54: /* ArgumentListFunctie: TOK_NUMBER_DOUBLE  */
#line 1687 "ex1lab12.y"
                        { 
        if(valoareif==-2)
{    double for_push = (yyvsp[0].dval);
    parametrii.push_back(for_push); }}
#line 3106 "ex1lab12.tab.c"
    break;

  case 55: /* ArgumentListFunctie: ArgumentListFunctie ',' TOK_NUMBER_INT  */
#line 1692 "ex1lab12.y"
    {
        if(valoareif==-2)
{        int for_push = (yyvsp[0].dval);
        parametrii.push_back(for_push);}
    }
#line 3116 "ex1lab12.tab.c"
    break;

  case 56: /* ArgumentListFunctie: ArgumentListFunctie ',' TOK_NUMBER_FLOAT  */
#line 1698 "ex1lab12.y"
    {
                if(valoareif==-2)
{        float for_push = (yyvsp[0].dval);
        parametrii.push_back(for_push);}
    }
#line 3126 "ex1lab12.tab.c"
    break;

  case 57: /* ArgumentListFunctie: ArgumentListFunctie ',' TOK_NUMBER_DOUBLE  */
#line 1704 "ex1lab12.y"
    {
                if(valoareif==-2)
{        double for_push = (yyvsp[0].dval);
        parametrii.push_back(for_push);}
    }
#line 3136 "ex1lab12.tab.c"
    break;

  case 58: /* ArgumentListFunctie: %empty  */
#line 1709 "ex1lab12.y"
      {

    }
#line 3144 "ex1lab12.tab.c"
    break;

  case 59: /* LogicalExpression: E TOK_GT E  */
#line 1717 "ex1lab12.y"
               { 
        (yyval.dval) = (yyvsp[-2].dval) > (yyvsp[0].dval); 
        if((yyvsp[-2].dval)>(yyvsp[0].dval))
            valoareif=1;
        else
            valoareif=2;
        }
#line 3156 "ex1lab12.tab.c"
    break;

  case 60: /* LogicalExpression: E TOK_LT E  */
#line 1724 "ex1lab12.y"
               {         
        (yyval.dval) = (yyvsp[-2].dval) > (yyvsp[0].dval); 
        if((yyvsp[-2].dval)>(yyvsp[0].dval))
            valoareif=1;
        else
            valoareif=2;
        }
#line 3168 "ex1lab12.tab.c"
    break;

  case 61: /* LogicalExpression: E TOK_EQ E  */
#line 1731 "ex1lab12.y"
               {         
        (yyval.dval) = (yyvsp[-2].dval) == (yyvsp[0].dval); 
        if((yyvsp[-2].dval)==(yyvsp[0].dval))
            valoareif=1;
        else
            valoareif=2;
        }
#line 3180 "ex1lab12.tab.c"
    break;

  case 62: /* LogicalExpression: E TOK_GE E  */
#line 1738 "ex1lab12.y"
               {        
        (yyval.dval) = (yyvsp[-2].dval) >= (yyvsp[0].dval); 
        if((yyvsp[-2].dval)>=(yyvsp[0].dval))
            valoareif=1;
        else
            valoareif=2;
        }
#line 3192 "ex1lab12.tab.c"
    break;

  case 63: /* LogicalExpression: E TOK_LE E  */
#line 1745 "ex1lab12.y"
               {         
        (yyval.dval) = (yyvsp[-2].dval) <= (yyvsp[0].dval); 
        if((yyvsp[-2].dval)<=(yyvsp[0].dval))
            valoareif=1;
        else
            valoareif=2;
        }
#line 3204 "ex1lab12.tab.c"
    break;

  case 64: /* LogicalExpression: E TOK_NE E  */
#line 1752 "ex1lab12.y"
               {         
        (yyval.dval) = (yyvsp[-2].dval) != (yyvsp[0].dval); 
        if((yyvsp[-2].dval)!=(yyvsp[0].dval))
            valoareif=1;
        else
            valoareif=2;
        }
#line 3216 "ex1lab12.tab.c"
    break;


#line 3220 "ex1lab12.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1763 "ex1lab12.y"


int main() {
    yyparse();



    // // Intercalăm analiza unui string
    // std::string intercalat = "printf(\"o iubesc pe alexia si e viata mea.\n\");";
    // switch_to_string(intercalat.c_str()); // Trecem la string
    // yyparse();
    // restore_previous_buffer(); // Revenim la fișier







    if (EsteCorecta == 1) {
        cout << "CORECT\n";
    }

    //printf("\n\n\n");
    //print_functie_by_name("suma");

    //TFUNCTIE * fct = gaseste_functie("suma");

    //std::vector<TFUNCTIE::Parametru> parametrii_corecti = { 10, 11};

    // auto test=fct->CallFunctie(parametrii_corecti);
    // std::visit([](auto&& value) {
    //     std::cout << "Rezultatul funcției este: " << value << std::endl;
    // }, test);


    ts->printVars();


    // std::string testt="andreialexiaandrei";
    // std::string rezultat=getFunctionNameFromVariable(testt);
    // printf("rezultat=%s\n",rezultat.c_str());

    return 0;
}

int yyerror(const char *msg) {
    cout << "EROARE: " << msg 
         << " la linia " << yylloc.first_line 
         << ", coloana " << yylloc.first_column << endl;
    exit(1); // Termină execuția programului
    return 1; // (Nu va fi atins, dar păstrăm pentru consistență)
}



