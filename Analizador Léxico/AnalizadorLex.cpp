#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;
/*
enum Tipo{
    TKN_UNDEFINED = -1,
    Entero = 'E',
    Variable = 'V',
    Operador = 'O'
};
*/
class Token {
    public:
        char *palabra; //almacena una copia de la palabra
        int indice;
        //Tipo tipo; //E (entero), V (variable), O (operador)
        Token ( char *str ){
            this->palabra = str;
        }
        bool isOperator(char ch);
        bool reconoceNumero(char* str);
        char* SString(char* str, int left, int right);
        bool ReconocerVariable(char* str);
        bool isDelimiter(char ch);
        void analizadorLexico(char* str);
    };

  
// Retorna true si el caracter es un operador.
bool Token::isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || 
        ch == '/' || ch == '>' || ch == '<' || 
        ch == '=' || ch == '(' || ch == ')' )
        return (true);
    return (false);
}
  


//  Retorna true si el caracter es un entero.

bool Token::reconoceNumero(char* str)
{
    int i, len = strlen(str);
  
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}
//  Extrae el substring
char* Token::SString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(
                  sizeof(char) * (right - left + 2));
  
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}
// Retorna true si el caracter es un delimitador.
bool Token::isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || 
        ch == '/' || ch == ',' || ch == ';' || ch == '>' || 
        ch == '<' || ch == '=' || ch == '(' || ch == ')' || 
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}
// Devuelve verdadero si el identificador es válido
bool Token::ReconocerVariable(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' || 
        str[0] == '6' || str[0] == '7' || str[0] == '8' || 
        str[0] == '9' || isDelimiter(str[0]) == true)
        return (false);
    return (true);
}

void Token::analizadorLexico(char* str)
{
    int left = 0, right = 0;
    int len = strlen(str);
  
    while (right <= len && left <= right) {
        if (isDelimiter(str[right]) == false)
            right++;
  
        if (isDelimiter(str[right]) == true && left == right) {
            if (isOperator(str[right]) == true)
                printf("TOKEN['%c']: pos= %d , Tipo = O\n", str[right],right);
  
            right++;
            left = right;
        } else if (isDelimiter(str[right]) == true && left != right
                   || (right == len && left != right)) {
            char* subStr = SString(str, left, right - 1);
            
            if (reconoceNumero(subStr) == true)
                printf("TOKEN['%s']: pos= %d , Tipo = E\n", subStr, right-strlen(subStr));
           
            else if (ReconocerVariable(subStr) == true
                     && isDelimiter(str[right - 1]) == false){
                         
                            printf("TOKEN['%s']: pos= %d , Tipo = V\n", subStr,right-strlen(subStr));
                     }
                
  
            else if (ReconocerVariable(subStr) == false
                     && isDelimiter(str[right - 1]) == false)
                printf("'%s' ERROR , NO VALIDO\n", subStr);
            left = right;
        }
    }
    return;
}
  
int main()
{
    char str[100] = "Hola123 = ( hola + 123 )";
    Token TK(str);
    TK.analizadorLexico(str); 
    
    return (0);
}