#include <dirent.h>
DIR *dir_tarefas;
char **caminho_tarefa;
int posmem=0;

GtkWidget *popup;
int popup_aberto=0;



int apaga_tarefa(GtkWidget *widget,gpointer *ponteiro)
{
	int err=0;
	int exec_listas();
	printf("removendo %s\n",(char*)ponteiro);
	err = remove((char*)ponteiro);
	if(err!=0)
	{
		g_print("Erro removendo %s\n",(char*)ponteiro);	
	}
	exec_listas();
}


int exec_listas()
{
	struct dirent *leitor;
	GtkWidget **nome_tarefa;
	GtkWidget **botao_executa;
	GtkWidget **botao_exclui;
	GtkWidget **tarefa_listada;
	GtkWidget *mensagem;
	GtkWidget *caixa;
        popup = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_widget_set_name(popup,"limite");
	gtk_window_set_position(GTK_WINDOW(popup),3);
	mensagem  = gtk_label_new("Limite de 9 Tarefas,\nexclua algumas\npara poder criar outras");
	caixa = gtk_box_new(1,0);
	nome_entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(caixa),mensagem,0,0,0);
	gtk_container_add(GTK_CONTAINER(popup),caixa);
	g_signal_connect(popup,"destroy",G_CALLBACK(gtk_widget_destroy),NULL);
	gtk_widget_set_size_request(popup,100,100);

	nome_tarefa    = malloc(sizeof(GtkLabel*)*30);
	tarefa_listada = malloc(sizeof(GtkBox*)*30);
	botao_executa  = malloc(sizeof(GtkButton*)*30); 	
	botao_exclui   = malloc(sizeof(GtkButton*)*30); 	

	dir_tarefas = opendir(CAMINHO);
	
	if(dir_tarefas == NULL)
	{
		g_print("Erro ao tentar listar as tarefas\n");
		return 1;
	}		
	gtk_widget_destroy(tarefas_listadas);
        tarefas_listadas = gtk_box_new(0,0);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(espaco_rolamento_lista),tarefas_listadas);
	posmem=0;
	while(leitor = readdir(dir_tarefas))
	{
		if(strcmp(leitor->d_name,".")!=0&&strcmp(leitor->d_name,"..")!=0)
		{
			caminho_tarefa = malloc(600);
			caminho_tarefa[posmem] = malloc(60);
			if((strlen(CAMINHO)+strlen(leitor->d_name))>60)
			{
				g_print("Limite de caracteres!\n");
				break;
			}
			sprintf(caminho_tarefa[posmem],"%s%s",CAMINHO,leitor->d_name);
			printf("nome tarefa: %s\n",leitor->d_name);		
			nome_tarefa[posmem]    = gtk_label_new(leitor->d_name);
			botao_executa[posmem]  = gtk_button_new_with_label("Executar");
			botao_exclui[posmem]  = gtk_button_new_with_label("Excluir");
			tarefa_listada[posmem] = gtk_box_new(1,0);

			gtk_widget_set_name(tarefa_listada[posmem],"tarefa_listada");	
			
			gtk_box_pack_start(GTK_BOX(tarefa_listada[posmem]),nome_tarefa[posmem],0,0,10);
			gtk_box_pack_end(GTK_BOX(tarefa_listada[posmem]),botao_exclui[posmem],0,0,5);
			gtk_box_pack_end(GTK_BOX(tarefa_listada[posmem]),botao_executa[posmem],0,0,5);
			gtk_box_pack_start(GTK_BOX(tarefas_listadas),tarefa_listada[posmem],0,0,10);	
			g_signal_connect(botao_exclui[posmem],"clicked",G_CALLBACK(apaga_tarefa),caminho_tarefa[posmem]);
			g_signal_connect(botao_exclui[posmem],"clicked",G_CALLBACK(fechar_janela),caminho_tarefa[posmem]);
			#ifdef WIN32
			g_signal_connect(botao_executa[posmem],"clicked",G_CALLBACK(leitura_execucao),caminho_tarefa[posmem]);
			#endif
			g_signal_connect(botao_exclui[posmem],"clicked",G_CALLBACK(fechar_janela),popup);
			gtk_widget_show_all(espaco_rolamento_lista);	
			posmem++;
		}
	}

}
