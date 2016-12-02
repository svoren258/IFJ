/* Program 3: Prace s retezci a vestavenymi funkcemi */
class Main
{
    static int b = 2;
    static void run()
    {
        int a = 3 + Game.b;
        ifj16.print("a = " +a+"\n");
        
        test(a);
    
    } // end of static void run()

    static void test(int a)
    {
        ifj16.print("test + "a+"\n");
        
        if(a > 0)
        {
            test(a - 1);
        }
        else
        {
            return;
        }
    }
} // end of class Main

class Game
{
    static int c = 1;
    static int b = 2;
    static int a = 3;
    static void play()
    {
        
    }
}

