/* Program 3: Prace s retezci a vestavenymi funkcemi */
class Main
{
    static int c = 4;
    static void run()
    {
        int b = 3 + 5;
        int a = 4+ Game.c;
        double dob;
        String str1 = "str1";
        String str2 = "str2";
        
        ifj16.print(a + "\n");        
        Game.play(str1, b , str2);    
        b = test(a,b);
        ifj16.print(b + "\n");
    } // end of static void run()

    

    static int test(int a, int b)
    {
        a = a + 1;
        return (a + b);
    }
    
    
} // end of class Main

class Game
{
    static int c = 2;
    static int play(String str1, int b, String str2)
    {
        ifj16.print("\n\nplay()\n");
        ifj16.print(str2);
        ifj16.print("\n\n");
        return (1 + 3);
    }
    
    
}
