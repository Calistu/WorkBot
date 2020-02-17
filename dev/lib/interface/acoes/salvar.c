#define CAMINHO "/workbot/data/tarefas/"
GtkWidget *nome_entry;
gchar *nome_tarefa;
gchar *caminho;
int fechar_janela(GtkWidget *widget,gpointer ponteiro)
{
	gtk_widget_destroy(GTK_WIDGET(ponteiro));
	gtk_widget_set_sensitive(janela,TRUE);
}

int criar_tarefa()
{
	caminho = malloc(60);
	nome_tarefa = malloc(50);
	nome_tarefa = (gchar*)gtk_entry_get_text(GTK_ENTRY(nome_entry));
	sprintf(caminho,"%s%s",CAMINHO,nome_tarefa);
	if(strlen(nome_tarefa)>50)
	{	
		GtkWidget *popup;
		GtkWidget *mensagem;
		GtkWidget *caixa;
		popup = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_position(GTK_WINDOW(popup),3);
		mensagem  = gtk_label_new("Erro! nome muito grande");
		caixa = gtk_box_new(1,0);	
		nome_entry = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(caixa),mensagem,0,0,0);	
		gtk_container_add(GTK_CONTAINER(popup),caixa);	
		g_signal_connect(popup,"destroy",G_CALLBACK(gtk_widget_destroy),NULL);
		gtk_widget_show_all(popup);	
	}
	FILE *arquivo;
    arquivo = fopen(caminho,"w");
	int pos = 0;
        while(pos<qnt_acoes)
        {
                if(gtk_widget_get_visible(acao_container[pos])!=FALSE)
 		{
			g_print("Adicionando campo %i\n",pos);
			if(nova_acao[pos].tipo==1)
			{
				fprintf(arquivo,"mover\n");
				fprintf(arquivo,"%i\n",nova_acao[pos].mover.x);
				fprintf(arquivo,"%i\n",nova_acao[pos].mover.y);
			}
			if(nova_acao[pos].tipo==2)
			{
				fprintf(arquivo,"escrever\n");
				fprintf(arquivo,"%s\n",nova_acao[pos].escrever);
			}
			if(nova_acao[pos].tipo==3)
			{
				fprintf(arquivo,"clicar\n");
			}
			if(nova_acao[pos].tipo==4);
			{
				switch(nova_acao[pos].tecla.valor)
				{
					case 1:
						fprintf(arquivo,"enter\n");
						break;
					case 2:
						fprintf(arquivo,"tecla_cima");
						break;
					case 3:
						fprintf(arquivo,"tecla_baixo");
						break;					
					case 4:
						fprintf(arquivo,"tecla_direita");
						break;
					case 5:
						fprintf(arquivo,"tecla_esquerda");
						break;
					case 6:
						fprintf(arquivo,"");
						break;
					case 7:
						fprintf(arquivo,"");
						break;
					case 8:
						fprintf(arquivo,"");
						break;
					
				}
			}
			if(nova_acao[pos].tipo==5)
			{
				fprintf(arquivo,"esperar\n");
				fprintf(arquivo,"%i\n",nova_acao[pos].esperar.segundos);
			
			}
		}
		else
		{
			g_print("o campo %i havia sido deletado\n",pos);
		}
		pos++;

        }
	exec_cancelar();
	fclose(arquivo);
}

int exec_salvar()
{
	int exec_listas();
	GtkWidget *janela_nome;
	GtkWidget *nome_label;
	GtkWidget *container;
	janela_nome = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(janela_nome),3);
	nome_label  = gtk_label_new("Insira o nome da Tarefa");
	nome_entry  = gtk_entry_new();
	container = gtk_box_new(1,0);	
	gtk_box_pack_start(GTK_BOX(container),nome_label,0,0,0);	
	gtk_box_pack_start(GTK_BOX(container),nome_entry,0,0,0);	
	gtk_container_add(GTK_CONTAINER(janela_nome),container);	
	g_signal_connect(janela_nome,"destroy",G_CALLBACK(fechar_janela),janela_nome);
	g_signal_connect(nome_entry,"activate",G_CALLBACK(criar_tarefa),NULL);
	g_signal_connect(nome_entry,"activate",G_CALLBACK(exec_listas),NULL);
	g_signal_connect(nome_entry,"activate",G_CALLBACK(fechar_janela),janela_nome);
	gtk_widget_set_sensitive(janela,FALSE);
	gtk_widget_show_all(janela_nome);
}
