/* Program 3: Prace s retezci a vestavenymi funkcemi */
class Main
{
    static void run()
    {
        String str1;
        str1 = "Toto je text";
        
        ifj16.print("Pozice retezce \"text\" v retezci str2: " + str1 + 4+ "\n");
        Game.hello(str1);
        
        ifj16.print(str1);
        
    } // end of static void run()
    
    
} // end of class Main

class Game
{
    static void hello(String str1)
    {
        str1 = "ZMeneny text";
    }
}
