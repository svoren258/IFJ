/* Program 3: Prace s retezci a vestavenymi funkcemi */
class Main
{
    static double b = 4.5;
    static void run()
    {
        String str1 = "wtf";
        String str2;
        int a = 5;
        
        ifj16.print(a+"\n");
        ifj16.print(a+"\n");
        str1 = "Text1";
        
        
        ifj16.print("Toto je este v pohode\n");
        str2 ="Text 2";
        
        

        str1 = str1 + ", toto je pokracovanie\n";

        
        ifj16.print(str1);
        ifj16.print("Pozice retezce \"text\" v retezci str2: \n");
        ifj16.print( "WUUT\n");
        //ifj16.print("a = "+a+"\n");
        //Game.hello(str1, a, str2);
        test();
    } // end of static void run()
    static int test()
    {
        int a = 3;
        ifj16.print(a);
        return 0;
    }
    
    
} // end of class Main

class Game
{
    static int hello(String str1, int b, String str2)
    {
        int c = 4;
        
        ifj16.print(str1 + b);
        // ifj16.print(str2 + b);
        // str1 = "ZMeneny text";
        // ifj16.print(str1);
        return 1;
    }
}
