typedef struct
{
	int tipo;
	//1 - mover mouse
	//2 - escrever
	//3 - clicar
	//4 - pressionar
	//5 - esperar
	int pos_act;
	struct
	{
		int x;
		int y;
	}mover;

	union
	{
		int valor;
	}tecla;
	
	union
	{
		int segundos;
	}esperar;	
	char *escrever;
}acoes;

typedef struct
{
	int velocidade;
	int init_segs;
	union
	{
		int flag;
		int hrs;
		int mins;
		int segs;
	}marcar;
	union
	{
		int flag;
		int qnt;
	}loop;

}params;

