#ifdef __linux__
	/*
	 * The program is for windows
	 * the interface is multiportable
	*/
	FILE *parametros;
#endif

int executar()
{
	parametros = fopen(caminho,"r");
	if(parametros == NULL)
	{
		g_print("Erro criando %s\n",nome_tarefa);
		return 1;
	}
		
}

