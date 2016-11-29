/* Program 3: Prace s retezci a vestavenymi funkcemi */
class Main
{
    static void run()
    {
        int b = 3 + 5;
        int a = 3+4;
        
        ifj16.print("a = "+ a + "\n");        
        a = test(a, b);
        ifj16.print("a now equals = " + a + "\n");
    } // end of static void run()
    static int test(int a, int b)
    {
        a = 5;
        b = 6;
        return (a+b);
    }
    
    
} // end of class Main

// class Game
// {
//     static int hello(String str1, int b, String str2)
//     {
//         ifj16.print("\n\nhello()\n");
//         ifj16.print(str2);
//         ifj16.print("\n\n");
//         return 1;
//     }
    
    
// }
