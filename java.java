/* Program 3: Prace s retezci a vestavenymi funkcemi */
class Main
{
    static void run()
    {
        int b = 0;
        String str1 = "Text 1";
        String str2 = "Text 2";
        ifj16.print("Toto je este v pohode\n");

        str2 ="Text 2";


        str1 = str1 + ", toto je pokracovanie\n";




        
        ifj16.print(str1);
        ifj16.print(str1);
        ifj16.print("Pozice retezce \"text\" v retezci str2: \n");
        ifj16.print( "WUUT\n");

        //ifj16.print("a = "+a+"\n");

        // ifj16.print("a = "+a+"\n");


        Game.hello(str1, a, str2);
        test();

        Game.hello(str1, b, str2);
        test(4, 3);
        int a = 4;
        ifj16.print("\nb = "+ a + a + "\n");
        ifj16.print(3);
        ifj16.print("\n");
        ifj16.print("\n");

    } // end of static void run()
    static int test(int a, int b)
    {

        int a = 3;

        ifj16.print(a+"\n");

        ifj16.print("test() + " a +" \n");

        return 0;

        ifj16.print(2);
        return 1;

    }
    
    
} // end of class Main

class Game
{
    static int hello(String str1, int b, String str2)
    {

        int c = 4;

        ifj16.print(str1 + b + "\n");
        ifj16.print(str2 + " " + b + "\n");
        // str1 = "Zmeneny text";
        //ifj16.print(str1);

        
        ifj16.print("hello() " + str1 + " " + b + " \n");
        // ifj16.print(str2 + b);
        // str1 = "ZMeneny text";
        // ifj16.print(str1);


        
        ifj16.print(1);

        return 1;
    }
    
    
}
