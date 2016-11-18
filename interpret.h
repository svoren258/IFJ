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
    INS_JMP,    //jump if true
    INS_JN,     //jump if false
    INS_CMP,    //
    INS_ASSIGN, // "=" assign value to the variable
    
}