class Main{
    static int mocnina(int exponent, int zaklad){
        int x = 0;
        int vysledok = 1;
        while(x < exponent){
            vysledok = vysledok * zaklad;
            x = x + 1;
        }
    }
}