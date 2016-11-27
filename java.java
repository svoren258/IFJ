/* Program 3: Prace s retezci a vestavenymi funkcemi */
class Main
{
    static double b = 4.5;
    static void run()
    {
        String str1 = "wtf";
        double a = 5 + b;
        
        Game.hello(str1, b);
        str1 = "Toto je text";
        ifj16.print(a+"\n");
        
        
        str1 = str1 + ", toto jep okracovanie\n";
        
        ifj16.print(str1);
        ifj16.print("Pozice retezce \"text\" v retezci str2: "+ 4+   "\n");
        
        
        
        
    } // end of static void run()
    
    
} // end of class Main

class Game
{
    static void hello(String str1, int b)
    {
        int c = b;
        str1 = "ZMeneny text";
        ifj16.print(str1);
    }
}
