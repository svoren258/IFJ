/********************************************************************/
/*Projekt:Implementace interpretu imperativního jazyka IFJ16        */
/*Jména řešitelů: Sebastián Kisela, Ondrej Svoreň, Daniel Rudík,    */
/*                  Patrik Roman, Martin Chudý                      */
/*Loginy řešitelů: xkisel02, xsvore01, xrudik00, xroman10, xchudy04 */
/********************************************************************/
enum instruction{
    INS_ADD,    // "+"
    INS_SUB,    // "-"
    INS_MUL,    // "*"
    INS_DIV,    // "/"
    INS_JCMP,    //jump if true
    INS_JNCMP,     //jump if false
    INS_JMP,    //jump
    INS_CMP,    //if the var tested has value 1 it's true
    INS_ASSIGN, // "=" assign value to the variable
    
}