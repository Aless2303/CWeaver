%{
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



%}

%union {
    char* sir;         // Pentru variabile (TOK_VARIABLE)
    int val;           // Pentru numere întregi (TOK_NUMBER_INT)
    float fval;        // Pentru numere float (TOK_NUMBER_FLOAT)
    double dval;       // Pentru numere double (TOK_NUMBER_DOUBLE)
}

%token <sir> TOK_TEXT_PRINTF
%token TOK_PRINTF TOK_SCANF
%token TOK_PLUS TOK_MINUS TOK_MULTIPLY TOK_DIVIDE TOK_LEFT TOK_RIGHT TOK_DECLARE TOK_PRINT TOK_ERROR TOK_INT TOK_FLOAT TOK_DOUBLE TOK_VOID
%token TOK_IF TOK_ELSE TOK_WHILE
%token TOK_LBRACE TOK_RBRACE //acolade
%token TOK_GT TOK_LT //> <
%token TOK_GE TOK_LE TOK_EQ TOK_NE // >= <= == !=
%token TOK_RETURN
%token <dval> TOK_NUMBER_INT    // Token pentru numere întregi
%token <dval> TOK_NUMBER_FLOAT // Token pentru numere float
%token <dval> TOK_NUMBER_DOUBLE // Token pentru numere double
%token <sir> TOK_VARIABLE      // Token pentru numele variabilelor
%token <sir> TOK_FUNCTION_BODY

%type <dval> E //am pus dval ca e cel mai precis si poate sa gestioneze si float/int
%type <dval> LogicalExpression
%type <dval> I
%type <dval> StmtList BlockStmt
%type <dval> IfStmt WhileStmt
%type <dval> PrintfStmt
%type <dval> ScanfStmt
%type <dval> ReturnStmt

%type <sir> VariableList AmpersandVariable

%type <dval> FunctionDeclarationStmt



%start S
%left TOK_PLUS TOK_MINUS
%left TOK_MULTIPLY TOK_DIVIDE

%%
S :
    StmtList
;



StmtList :
    I ';' StmtList
  | IfStmt StmtList 
  | WhileStmt StmtList
  | PrintfStmt StmtList
  | ScanfStmt StmtList
  | BlockStmt StmtList
  | FunctionDeclarationStmt StmtList
  | ReturnStmt StmtList
  | /* epsilon */
  {
      $$ = 0; // Valoare implicită pentru simbolul epsilon
  }
;

BlockStmt: 
    TOK_LBRACE {
        enterScope();
    } StmtList TOK_RBRACE {
        $$ = $3;
        exitScope();
    }
;

FunctionDeclarationStmt: 
    TOK_FUNCTION_BODY
    {
        //printf("functie:\n%s\n\n\n",$1);

        std::string functionText($1);

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
;







VariableList:
    TOK_VARIABLE {
        if(valoareif==-2)
        {// Extragem valoarea variabilei și tipul său
        if (ts->exists($1)) {
            asprintf(&$$, "%s", $1); // Reținem numele variabilei
            free($1);
        } else if(tsStack.empty()==false)
        {
            if(existsInCurrentScope($1)==1)
            {
                asprintf(&$$, "%s", $1); // Reținem numele variabilei
                free($1);
            }
        } 
        else {
            sprintf(msg, "Eroare: Variabila %s nu este declarată!", $1);
            yyerror(msg);
            YYERROR;
        }}
    }
  | VariableList ',' TOK_VARIABLE {
            if(valoareif==-2)
        {if (ts->exists($3)) {
            asprintf(&$$, "%s,%s", $1, $3); // Adăugăm numele noii variabile la listă
            free($1);
            free($3);
        } else if(tsStack.empty()==false)
        {
            if(existsInCurrentScope($3)==1)
            {
                asprintf(&$$, "%s,%s", $1, $3); // Adăugăm numele noii variabile la listă
                free($1);
                free($3);
            }
        } 
        else {
            sprintf(msg, "Eroare: Variabila %s nu este declarată!", $3);
            yyerror(msg);
            YYERROR;
        }
    }}
    | AmpersandVariable {
        if(valoareif==-2)
{        $$ = strdup($1);} // Reținem prima variabilă
    } 
    | VariableList ',' AmpersandVariable {
        if(valoareif==-2)
{        asprintf(&$$, "%s,%s", $1, $3); // Adăugăm variabila la listă
        free($1);
        free($3);}
    }
;


// Regula pentru o variabilă prefixată cu `&`
AmpersandVariable:
    '&' TOK_VARIABLE {
        if(valoareif==-2)
{        if (ts->exists($2)) {
            asprintf(&$$, "&%s", $2);
        }  else if(tsStack.empty()==false)
        {
            if (existsInCurrentScope($2)==1)
            {
                asprintf(&$$, "&%s", $2);
            }
        }
        else {
            sprintf(msg, "Eroare: Variabila %s nu este declaratăz!", $2);
            yyerror(msg);
            YYERROR;
        }}
    }
;

ScanfStmt:
    TOK_SCANF TOK_LEFT TOK_TEXT_PRINTF ',' VariableList TOK_RIGHT ';'
    {
        if(valoareif==-2)
        {// Obținem formatul și lista de variabile
        char *fmt = $3;  // Formatul de tipul "%d", "%f", "%lf" etc.
        char *vars = $5;  // Lista de variabile (de exemplu: &a, &b, &c)
        
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
;



PrintfStmt:
    TOK_PRINTF TOK_LEFT TOK_TEXT_PRINTF TOK_RIGHT ';' {
        //printf("%s\n", $3); // Afișăm textul fix
        if(valoareif==-2)
        {        
            for (char* c = $3; *c; ++c) {
                if (*c == '\\' && *(c + 1) == 'n') {
                    printf("\n");
                    c++;  // Skip 'n'
                    continue;
                } else {
                    printf("%c",*c);
                }
            }

        free($3);  
        }         // Eliberăm memoria textului
    }
    |
    TOK_PRINTF TOK_LEFT TOK_TEXT_PRINTF ',' VariableList TOK_RIGHT ';' {
        if(valoareif==-2)
       {std::vector<std::string> variableNames;
       char* token = strtok($5, ",");
       while (token != NULL) {
           variableNames.push_back(std::string(token));
           token = strtok(NULL, ",");
       }
       free($5);

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
       for (char* c = $3; *c; ++c) {
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
       free($3);
   }}
   ;

WhileStmt : 
    TOK_WHILE TOK_LEFT LogicalExpression TOK_RIGHT TOK_LBRACE StmtList TOK_RBRACE
    {
        valoareif=-2;
    }
;



IfStmt :
    TOK_IF TOK_LEFT LogicalExpression TOK_RIGHT TOK_LBRACE AuxIfFirst StmtList AuxIfFirst TOK_RBRACE
    {
        valoareif=-2;
    }
  | TOK_IF TOK_LEFT LogicalExpression TOK_RIGHT TOK_LBRACE AuxIfFirst StmtList AuxIfFirst TOK_RBRACE TOK_ELSE TOK_LBRACE AuxIfSecond StmtList AuxIfSecond TOK_RBRACE
    {
        valoareif=-2;
    }
  ;

AuxIfFirst :
    {
        if (valoareif==1)
            valoareif=-2;
        else if(valoareif!=2)
            valoareif=0;
    }
;

AuxIfSecond :
    { 
        if (valoareif==2) 
            valoareif=-2;
        else if(valoareif!=1)
            valoareif=0;
    }
;


I : TOK_VARIABLE '=' E {
    if(valoareif==-2){
        if (ts != NULL) {
            if (ts->exists($1) == 1) {
                VarType varType = ts->getType($1);
                switch (varType) {
                    case INT_TYPE:
                        if ($3 < INT_MIN_LIMIT || $3 > INT_MAX_LIMIT) {
                            sprintf(msg, "%d:%d Eroare semantica: Depășire a limitelor pentru tipul INT la variabila %s!", @1.first_line, @1.first_column, $1);
                            yyerror(msg);
                            YYERROR;
                        }
                        ts->setValue($1, (int)$3, INT_TYPE); // Conversie explicită la int
                        break;
                    case FLOAT_TYPE:
                        if ($3 < FLOAT_MIN_LIMIT || $3 > FLOAT_MAX_LIMIT) {
                            sprintf(msg, "%d:%d Eroare semantica: Depășire a limitelor pentru tipul FLOAT la variabila %s!", @1.first_line, @1.first_column, $1);
                            yyerror(msg);
                            YYERROR;
                        }
                        ts->setValue($1, (float)$3, FLOAT_TYPE); // Conversie explicită la float
                        break;
                    case DOUBLE_TYPE:
                        if ($3 < DOUBLE_MIN_LIMIT || $3 > DOUBLE_MAX_LIMIT) {
                            sprintf(msg, "%d:%d Eroare semantica: Depășire a limitelor pentru tipul DOUBLE la variabila %s!", @1.first_line, @1.first_column, $1);
                            yyerror(msg);
                            YYERROR;
                        }
                        ts->setValue($1, $3, DOUBLE_TYPE); // Fără conversie (este deja double)
                        break;
                    default:
                        sprintf(msg, "%d:%d Eroare semantica: Tip necunoscut pentru variabila %s!", @1.first_line, @1.first_column, $1);
                        yyerror(msg);
                        YYERROR;
                }
            } if (existsInCurrentScope($1)==1)
            {
                setValue($1,$3,GetTypeLocal($1));
            } else {
                sprintf(msg, "%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", @1.first_line, @1.first_column, $1);
                yyerror(msg);
                YYERROR;
            }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", @1.first_line, @1.first_column, $1);
            yyerror(msg);
            YYERROR;
        }
    }}
  | TOK_INT TOK_VARIABLE {
    if(valoareif==-2)
        {if (ts->exists($2) == 0) {
            if (tsStack.empty())
                {
                    ts->add($2, INT_TYPE, 0);
                } // Adăugare variabilă de tip int cu valoare implicită 0
            else 
                {
                    addVariable($2,INT_TYPE,0);
                    
                }
        } else 
        {
            sprintf(msg, "%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @2.first_line, @2.first_column, $2);
            yyerror(msg);
            YYERROR;
        }
    }}
  | TOK_FLOAT TOK_VARIABLE {
    if(valoareif==-2)
        {if (ts->exists($2) == 0) {
            if (tsStack.empty())
                {
                    ts->add($2, FLOAT_TYPE, 0);
                    printf("adaugare variabila %s float in variabile globale\n",$2);
                } // Adăugare variabilă de tip float cu valoare implicită 0
            else 
                {
                    printf("adaugare variabila %s float in variabile locale\n",$2);
                    addVariable($2,FLOAT_TYPE,0);
                    
                }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @2.first_line, @2.first_column, $2);
            yyerror(msg);
            YYERROR;
        }
    }}
  | TOK_DOUBLE TOK_VARIABLE {
    if(valoareif==-2)
        {if (ts->exists($2) == 0) {
            if (tsStack.empty())
                {
                    ts->add($2, DOUBLE_TYPE, 0);
                } // Adăugare variabilă de tip double cu valoare implicită 0
            else 
                {
                    addVariable($2,DOUBLE_TYPE,0);
                    
                }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @2.first_line, @2.first_column, $2);
            yyerror(msg);
            YYERROR;
        }
    }}
  | TOK_PRINT TOK_VARIABLE {
    if(valoareif==-2)
        {if (ts != NULL) {
            if (ts->exists($2) == 1) {
                VarType varType = ts->getType($2);
                switch (varType) {
                    case INT_TYPE:
                        printf("%d\n", (int)ts->getValue($2));
                        break;
                    case FLOAT_TYPE:
                        printf("%f\n", (float)ts->getValue($2));
                        break;
                    case DOUBLE_TYPE:
                        printf("%lf\n", ts->getValue($2));
                        break;
                    default:
                        sprintf(msg, "%d:%d Eroare semantica: Tip necunoscut pentru variabila %s!", @1.first_line, @1.first_column, $2);
                        yyerror(msg);
                        YYERROR;
                }
            } else if(tsStack.empty()==false)
            {
                if(existsInCurrentScope($2)==1)
                {
                    VarType varType = GetTypeLocal($2);
                    switch (varType) {
                        case INT_TYPE:
                            printf("%d\n", (int)getValueLocal($2));
                            break;
                        case FLOAT_TYPE:
                            printf("%f\n", (float)getValueLocal($2));
                            break;
                        case DOUBLE_TYPE:
                            printf("%lf\n", getValueLocal($2));
                            break;
                        default:
                            sprintf(msg, "%d:%d Eroare semantica: Tip necunoscut pentru variabila %s!", @1.first_line, @1.first_column, $2);
                            yyerror(msg);
                            YYERROR;
                    }
                }
            }
            else {
                sprintf(msg, "%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", @1.first_line, @1.first_column, $2);
                yyerror(msg);
                YYERROR;
            }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", @1.first_line, @1.first_column, $2);
            yyerror(msg);
            YYERROR;
        }
    }}
    | TOK_DOUBLE TOK_VARIABLE '=' E {
        if(valoareif==-2)
        {if (ts->exists($2) == 0) {
            if ($4 < DOUBLE_MIN_LIMIT || $4 > DOUBLE_MAX_LIMIT) {
                sprintf(msg, "%d:%d Eroare semantica: Depășire a limitelor pentru tipul DOUBLE la variabila %s!", @1.first_line, @1.first_column, $2);
                yyerror(msg);
                YYERROR;
            }

            if(tsStack.empty())
            {
                ts->add($2, DOUBLE_TYPE, $4); // Adaugă variabila de tip double cu valoarea specificată
            } else 
            {
                addVariable($2,DOUBLE_TYPE,$4);
            }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @2.first_line, @2.first_column, $2);
            yyerror(msg);
            YYERROR;
        }
    }}
    | TOK_INT TOK_VARIABLE '=' E {
        if(valoareif==-2)
        {if (ts->exists($2) == 0) {
            if ($4 < INT_MIN_LIMIT || $4 > INT_MAX_LIMIT) {
                sprintf(msg, "%d:%d Eroare semantica: Depășire a limitelor pentru tipul INT la variabila %s!", @1.first_line, @1.first_column, $2);
                yyerror(msg);
                YYERROR;
            }

            if(tsStack.empty())
            {
                ts->add($2, INT_TYPE, $4); // Adaugă variabila de tip INT cu valoarea specificată
            } else 
            {
                addVariable($2,INT_TYPE,$4);
            }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @2.first_line, @2.first_column, $2);
            yyerror(msg);
            YYERROR;
        }
    }}
    | TOK_FLOAT TOK_VARIABLE '=' E {
        if(valoareif==-2)
        {if (ts->exists($2) == 0) {
            if ($4 < FLOAT_MIN_LIMIT || $4 > FLOAT_MAX_LIMIT) {
                sprintf(msg, "%d:%d Eroare semantica: Depășire a limitelor pentru tipul FLOAT la variabila %s!", @1.first_line, @1.first_column, $2);
                yyerror(msg);
                YYERROR;
            }

            if(tsStack.empty())
            {
                ts->add($2, FLOAT_TYPE, $4); // Adaugă variabila de tip FLOAT cu valoarea specificată
            } else 
            {
                addVariable($2,FLOAT_TYPE,$4);
            }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @2.first_line, @2.first_column, $2);
            yyerror(msg);
            YYERROR;
        }
    }}
;

ReturnStmt : TOK_RETURN E ';' {
    // Exemplu de variabilă din expresia evaluată
    valoare_globala_returnata_functie=$2;
    printf("dupa return val globala este %lf\n",valoare_globala_returnata_functie);
    }
;


E : TOK_VARIABLE {
    if(valoareif==-2)
        {if (ts->exists($1)) {
            $$ = ts->getValue($1); // Obține valoarea variabilei
        } else if(tsStack.empty()==false)
        {
            if(existsInCurrentScope($1)==1)
            {
                $$=getValueLocal($1);
            } else {
                sprintf(msg, "%d:%d Eroare semantica: Variabila %s nu este declarata!", @1.first_line, @1.first_column, $1);
                yyerror(msg);
                YYERROR;
            }
        }
        else {
            sprintf(msg, "%d:%d Eroare semantica: Variabila %s nu este declarata!", @1.first_line, @1.first_column, $1);
            yyerror(msg);
            YYERROR;
        }
    }}
  | E TOK_PLUS E { 
    if(valoareif==-2)
    {$$ = $1 + $3;} }
  | E TOK_MINUS E { if(valoareif==-2)
  $$ = $1 - $3; }
  | E TOK_MULTIPLY E { if(valoareif==-2)
  $$ = $1 * $3; }
  | E TOK_DIVIDE E {
    if(valoareif==-2)
{        if ($3 == 0) {
            sprintf(msg, "%d:%d Eroare semantica: Impartire la zero!", @1.first_line, @1.first_column);
            yyerror(msg);
            YYERROR;
        } else {
            $$ = $1 / $3;
        }}
    }
  | TOK_LEFT E TOK_RIGHT { if(valoareif==-2)
  $$ = $2; }
  | TOK_NUMBER_INT { if(valoareif==-2)
  $$ = $1; }
  | TOK_NUMBER_FLOAT { if(valoareif==-2)
  $$ = $1; }
  | TOK_NUMBER_DOUBLE { if(valoareif==-2)
  $$ = $1; }
  | TOK_LEFT TOK_INT TOK_RIGHT TOK_VARIABLE {
    if(valoareif==-2)
    {if(ts->exists($4))
    {
        int value=(int)ts->getValue($4);
        $$ = value; // Rezultatul expresiei
        //printf("Casting '%s' to int: %d\n", $4, value);
    } else if(existsInCurrentScope($4)==1)
    {
        int value = (int)getValueLocal($4);
        $$ = value; // Rezultatul expresiei
        //printf("Casting '%s' to int: %d\n", $4, value);
    } else {
        sprintf(msg, "%d:%d Eroare semantica: Variabila %s nu este declarata!", @1.first_line, @1.first_column, $4);
        yyerror(msg);
        YYERROR;
    }  
  }}
  | TOK_LEFT TOK_DOUBLE TOK_RIGHT TOK_VARIABLE {
    if(valoareif==-2)
   { if(ts->exists($4))
    {
        double value=(double)ts->getValue($4);
        $$ = value; // Rezultatul expresiei
        //printf("Casting '%s' to double: %lf\n", $4, value);
    } else if(existsInCurrentScope($4)==1)
    {
        double value = (double)getValueLocal($4);
        $$ = value; // Rezultatul expresiei
        //printf("Casting '%s' to double: %lf\n", $4, value);
    } else {
        sprintf(msg, "%d:%d Eroare semantica: Variabila %s nu este declarata!", @1.first_line, @1.first_column, $4);
        yyerror(msg);
        YYERROR;
    }
    
  }}
  | TOK_LEFT TOK_FLOAT TOK_RIGHT TOK_VARIABLE {
    if(valoareif==-2){
    if(ts->exists($4))
    {
        float value=(float)ts->getValue($4);
        $$ = value; // Rezultatul expresiei
        //printf("Casting '%s' to float: %f\n", $4, value);
    } else if(existsInCurrentScope($4)==1)
    {
        float value = (float)getValueLocal($4);
        $$ = value; // Rezultatul expresiei
        //printf("Casting '%s' to float: %f\n", $4, value);
    } else {
        sprintf(msg, "%d:%d Eroare semantica: Variabila %s nu este declarata!", @1.first_line, @1.first_column, $4);
        yyerror(msg);
        YYERROR;
    }
  }}
  | TOK_VARIABLE TOK_LEFT ArgumentListFunctie TOK_RIGHT {
    if(valoareif==-2){
        TFUNCTIE* functie = gaseste_functie($1);
        if (!functie) {
            sprintf(msg, "Eroare: Funcția %s nu a fost găsită!", $1);
            yyerror(msg);
            YYERROR;
        }

        try {
            // Apelăm funcția și obținem rezultatul
            
            
            functie->CallFunctie(parametrii);
            parametrii.clear();

            $$=valoare_globala_returnata_functie;
            valoare_globala_returnata_functie=0;

        } catch (const std::exception& e) {
            sprintf(msg, "Eroare la apelul funcției %s: %s", $1, e.what());
            yyerror(msg);
            YYERROR;
        }
    }}
;

ArgumentListFunctie:
    TOK_VARIABLE
    {
        if(valoareif==-2){
        if (ts->exists($1)) {
            VarType varType = ts->getType($1); // Obținem tipul variabilei
            switch (varType) {
                case INT_TYPE: {
                    int for_push = (int)ts->getValue($1); // Creăm variabila pentru int
                    parametrii.push_back(for_push);       // Adăugăm în vector
                    break;
                }
                case FLOAT_TYPE: {
                    float for_push = (float)ts->getValue($1); // Creăm variabila pentru float
                    parametrii.push_back(for_push);           // Adăugăm în vector
                    break;
                }
                case DOUBLE_TYPE: {
                    double for_push = ts->getValue($1); // Creăm variabila pentru double
                    parametrii.push_back(for_push);     // Adăugăm în vector
                    break;
                }
                default:
                    sprintf(msg, "Eroare: Tip necunoscut pentru variabila %s!", $1);
                    yyerror(msg);
                    YYERROR;
            }
        } else if (!tsStack.empty() && existsInCurrentScope($1)) {
            VarType varType = GetTypeLocal($1); // Obținem tipul variabilei din scope-ul local
            switch (varType) {
                case INT_TYPE: {
                    int for_push = (int)getValueLocal($1); // Creăm variabila pentru int
                    parametrii.push_back(for_push);       // Adăugăm în vector
                    break;
                }
                case FLOAT_TYPE: {
                    float for_push = (float)getValueLocal($1); // Creăm variabila pentru float
                    parametrii.push_back(for_push);           // Adăugăm în vector
                    break;
                }
                case DOUBLE_TYPE: {
                    double for_push = getValueLocal($1); // Creăm variabila pentru double
                    parametrii.push_back(for_push);     // Adăugăm în vector
                    break;
                }
                default:
                    sprintf(msg, "Eroare: Tip necunoscut pentru variabila %s!", $1);
                    yyerror(msg);
                    YYERROR;
            }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Variabila %s nu este declarata!", @1.first_line, @1.first_column, $1);
            yyerror(msg);
            YYERROR;
        }
    }}
    | ArgumentListFunctie ',' TOK_VARIABLE
    {
        if(valoareif==-2){
        if (ts->exists($3)) {
            VarType varType = ts->getType($3); // Obținem tipul variabilei
            switch (varType) {
                case INT_TYPE: {
                    int for_push = (int)ts->getValue($3); // Creăm variabila pentru int
                    parametrii.push_back(for_push);       // Adăugăm în vector
                    break;
                }
                case FLOAT_TYPE: {
                    float for_push = (float)ts->getValue($3); // Creăm variabila pentru float
                    parametrii.push_back(for_push);           // Adăugăm în vector
                    break;
                }
                case DOUBLE_TYPE: {
                    double for_push = ts->getValue($3); // Creăm variabila pentru double
                    parametrii.push_back(for_push);     // Adăugăm în vector
                    break;
                }
                default:
                    sprintf(msg, "Eroare: Tip necunoscut pentru variabila %s!", $3);
                    yyerror(msg);
                    YYERROR;
            }
        } else if (!tsStack.empty() && existsInCurrentScope($3)) {
            VarType varType = GetTypeLocal($3); // Obținem tipul variabilei din scope-ul local
            switch (varType) {
                case INT_TYPE: {
                    int for_push = (int)getValueLocal($3); // Creăm variabila pentru int
                    parametrii.push_back(for_push);       // Adăugăm în vector
                    break;
                }
                case FLOAT_TYPE: {
                    float for_push = (float)getValueLocal($3); // Creăm variabila pentru float
                    parametrii.push_back(for_push);           // Adăugăm în vector
                    break;
                }
                case DOUBLE_TYPE: {
                    double for_push = getValueLocal($3); // Creăm variabila pentru double
                    parametrii.push_back(for_push);     // Adăugăm în vector
                    break;
                }
                default:
                    sprintf(msg, "Eroare: Tip necunoscut pentru variabila %s!", $3);
                    yyerror(msg);
                    YYERROR;
            }
        } else {
            sprintf(msg, "%d:%d Eroare semantica: Variabila %s nu este declarata!", @1.first_line, @1.first_column, $3);
            yyerror(msg);
            YYERROR;
        }
    }}
    | TOK_NUMBER_INT { 
        if(valoareif==-2)
{        int for_push = $1;
        parametrii.push_back(for_push); }}
    | TOK_NUMBER_FLOAT {
        if(valoareif==-2)
{    float for_push = $1;
    parametrii.push_back(for_push); }}
    | TOK_NUMBER_DOUBLE { 
        if(valoareif==-2)
{    double for_push = $1;
    parametrii.push_back(for_push); }}
    | ArgumentListFunctie ',' TOK_NUMBER_INT
    {
        if(valoareif==-2)
{        int for_push = $3;
        parametrii.push_back(for_push);}
    }
    | ArgumentListFunctie ',' TOK_NUMBER_FLOAT
    {
                if(valoareif==-2)
{        float for_push = $3;
        parametrii.push_back(for_push);}
    }
    | ArgumentListFunctie ',' TOK_NUMBER_DOUBLE
    {
                if(valoareif==-2)
{        double for_push = $3;
        parametrii.push_back(for_push);}
    }
    | {

    }
;



LogicalExpression :
    E TOK_GT E { 
        $$ = $1 > $3; 
        if($1>$3)
            valoareif=1;
        else
            valoareif=2;
        }
  | E TOK_LT E {         
        $$ = $1 > $3; 
        if($1>$3)
            valoareif=1;
        else
            valoareif=2;
        }
  | E TOK_EQ E {         
        $$ = $1 == $3; 
        if($1==$3)
            valoareif=1;
        else
            valoareif=2;
        }
  | E TOK_GE E {        
        $$ = $1 >= $3; 
        if($1>=$3)
            valoareif=1;
        else
            valoareif=2;
        }
  | E TOK_LE E {         
        $$ = $1 <= $3; 
        if($1<=$3)
            valoareif=1;
        else
            valoareif=2;
        }
  | E TOK_NE E {         
        $$ = $1 != $3; 
        if($1!=$3)
            valoareif=1;
        else
            valoareif=2;
        }
  ;



%%

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



