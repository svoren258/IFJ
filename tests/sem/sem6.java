//semanticka chyba - chybny pocet parametrov
class Main{
	static void run(){
		int x = 5;
		int y = 5;
		int z = sucet(x);
	}
	static int sucet(int x, int y){
		int suma = x + y;
		return suma;
	}
}