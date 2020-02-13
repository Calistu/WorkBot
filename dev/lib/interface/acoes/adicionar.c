#define IMG_OK     "/workbot/data/interface/imgs/ok.png"
#define IMG_CANCEL "/workbot/data/interface/imgs/cancelar.png"
#ifdef WIN32


#endif
int *posicoes_acoes;
int x,y;
int qnt_acoes=0;
int qnt_remove=0;
gchar *texto_pos;
GtkWidget *janela_acoes;
GtkWidget *posicao,        *posicao_mouse_label,*posicao_mouse_button;
GtkWidget *move_label;
GtkWidget *escrever,       *escrever_entry,     *escrever_label;
GtkWidget *clicar_label;
GtkWidget *tecla,          *tecla_entry,        *tecla_label;
GtkWidget *aguardar,       *aguardar_label, *aguardar_entry;
gchar     *segundos_char,  *tecla_char;
GtkWidget *caixa_tecla;
int       segundos_int;

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

int remover_acao(GtkWidget *widget,gpointer *ponteiro)
{
	g_print("Retirado\n",ponteiro);	
	gtk_widget_destroy(GTK_WIDGET(ponteiro));
	qnt_remove++;
	if(qnt_remove==qnt_acoes)
	{
 	       gtk_widget_set_sensitive(finaliza,FALSE);	
	}
}

int fechar(GtkWidget* widget,gpointer* ponteiro)
{
	gtk_widget_set_sensitive(janela,TRUE);
	gtk_widget_destroy(GTK_WIDGET(ponteiro));
	return 0;
}

void pegar_posicao()
{
	sleep(3);
	#ifdef WIN32
	GetCursorPos(&ponteiro);
	x = ponteiro.x;
	y = ponteiro.y;
	#endif
	#ifdef __linux__
	x = 5;
	y = 5;
	#endif
   	sprintf(texto_pos,"(%i,%i)",x,y);	
	gtk_label_set_text(GTK_LABEL(move_label),texto_pos);
}

int ok_acao(GtkWidget *widget,gpointer *opcao)
{
	char *id_acao;
	char *texto;
	texto = malloc(50);
	if(qnt_acoes>30)
	{
		g_print("Limite de acoes");
		return 1;
	}
	id_acao = malloc(30);
	if(gtk_toggle_button_get_active(opcao[0]))
        {
                g_print("Acoes: selecionado mover\n");
		nova_acao[qnt_acoes].tipo = 1;
		nova_acao[qnt_acoes].mover.x = x;
		nova_acao[qnt_acoes].mover.y = y;
		sprintf(id_acao,"Mover mouse para (%i,%i)",x,y);
	}       
        else    
        if(gtk_toggle_button_get_active (opcao[1]))
        {
        	g_print("Acoes: selecionado escrever\n");
 		texto = (gchar*)gtk_entry_get_text(GTK_ENTRY(escrever_entry));
		if(strlen(texto)>30)
		{
			g_print("Erro: escrever\n");
 			gtk_entry_set_text(GTK_ENTRY(escrever_entry),"Insira até 30 caracteres");
			return 1;
		}
		if(strlen(texto)<1)
		{
			g_print("Erro: escrever\n");
			return 1;
		}
		nova_acao[qnt_acoes].tipo = 2;
		nova_acao[qnt_acoes].escrever = malloc(sizeof(texto));
		nova_acao[qnt_acoes].escrever = texto;
		sprintf(id_acao,"Escrever '%s'",texto);
        }       
        else    
        if(gtk_toggle_button_get_active (opcao[2]))
        {
                g_print("Acoes: Radio selecionado clique\n");
		sprintf(id_acao,"Clicar");
        	nova_acao[qnt_acoes].tipo = 3;

	}
        else
        if(gtk_toggle_button_get_active (opcao[3]))
        {
            g_print("Acoes: selecionado: pressiona tecla\n");
			tecla_char = malloc(30);
			nova_acao[qnt_acoes].tipo = 4;
//			nova_acao[qnt_acoes].tipo.tecla.valor =
			tecla_char = 	(gchar*)gtk_entry_get_text(GTK_ENTRY(tecla_entry));
			sprintf(id_acao,"Pressionar tecla %s",texto);
        }
        if(gtk_toggle_button_get_active (opcao[4]))
        {
            g_print("Acoes: selecionado: aguardar\n");
			segundos_char = malloc(8);
			segundos_char = (gchar*)gtk_entry_get_text(GTK_ENTRY(aguardar_entry));
			if(strlen(segundos_char)>8)
			{
				g_print("Erro: tecla\n");	
				gtk_entry_set_text(GTK_ENTRY(tecla_entry),"Insira até 1000000 segundos");
				return 1;
			}
			if(strlen(segundos_char)<1)
			{
				return 0;
			}
			segundos_int  = atoi(segundos_char); 
			sprintf(id_acao,"Aguardar  %i segundos",segundos_int);
			nova_acao[qnt_acoes].tipo             = 5;
        	nova_acao[qnt_acoes].esperar.segundos = segundos_int;
        }
	
	nova_acao[qnt_acoes].pos_act = qnt_acoes;
	acao[qnt_acoes]              = gtk_label_new(id_acao);
	remover[qnt_acoes]           = gtk_button_new_with_label("Retirar");	
    img_remover[qnt_acoes]       = gtk_image_new_from_file(IMG_REM);
	acao_container[qnt_acoes]    = gtk_box_new(1,0);
	
	gtk_button_set_image(GTK_BUTTON(remover[qnt_acoes]),img_remover[qnt_acoes]);
	gtk_box_pack_start(GTK_BOX(acao_container[qnt_acoes]),acao[qnt_acoes],0,0,5);	
	gtk_box_pack_start(GTK_BOX(acao_container[qnt_acoes]),remover[qnt_acoes],0,0,5);	
	gtk_box_pack_start(GTK_BOX(scroll_caixa),acao_container[qnt_acoes],0,0,5);
	gtk_widget_show_all(caixa_acoes);
	gtk_widget_set_sensitive(finaliza,TRUE);
	gtk_widget_set_sensitive(janela,TRUE);
	posicoes_acoes[qnt_acoes] = qnt_acoes;
	g_signal_connect(GTK_WIDGET(remover[qnt_acoes]),"clicked",G_CALLBACK(remover_acao),acao_container[qnt_acoes]);	
	qnt_acoes++;
	gtk_widget_hide(janela_acoes);	
}



int mudanca(GtkWidget*widget,gpointer *opcao)
{	
	gtk_widget_hide(posicao);
	gtk_widget_hide(escrever);
	gtk_widget_hide(clicar_label);
	gtk_widget_hide(tecla);
	gtk_widget_hide(aguardar);

	if(gtk_toggle_button_get_active (opcao[0]))
	{
		g_print("Acoes: Radio posicao: mover\n");
		gtk_widget_show_all(posicao);
	}
	else
	if(gtk_toggle_button_get_active (opcao[1]))
	{
		g_print("Acoes: Radio posicao: escrever\n");
		gtk_widget_show_all(escrever);
		gtk_widget_grab_focus(escrever_entry);
	}
	else

	if(gtk_toggle_button_get_active (opcao[2]))
	{
		g_print("Acoes: Radio posicao: clique\n");
		gtk_widget_show_all(clicar_label);

	}
	else
	if(gtk_toggle_button_get_active (opcao[3]))
	{
		g_print("Acoes: Radio posicao: pressiona tecla\n");
		gtk_widget_show_all(tecla);
		gtk_widget_grab_focus(caixa_tecla);
	}
	if(gtk_toggle_button_get_active (opcao[4]))
	{
		g_print("Acoes: Radio posicao: pressiona tecla\n");
		gtk_widget_show_all(aguardar);
		gtk_widget_grab_focus(aguardar_label);
	}


}

int adicionar_acao()
{
	void pegar_posicao();
	GtkWidget    **opcoes;
	GtkWidget **separadores;
	

	posicoes_acoes = malloc(30);
	texto_pos = malloc(30);
	gtk_widget_set_sensitive(janela,FALSE);
		
	separadores    = malloc(sizeof(GtkSeparator*)*5);
	
	
	separadores[0] = gtk_separator_new(0); 
	separadores[1] = gtk_separator_new(0); 
	separadores[2] = gtk_separator_new(0); 
	separadores[3] = gtk_separator_new(0); 
	separadores[4] = gtk_separator_new(0); 
	
	GSList    *lista_opcoes=NULL;
	GtkWidget *caixa1,*caixa2,*caixa_principal;
	GtkWidget *botao_ok,*botao_cancelar;
	GtkWidget *img_ok,*img_cancelar;
	
	janela_acoes = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    	gtk_window_set_decorated(GTK_WINDOW(janela_acoes),FALSE);
	gtk_window_set_position(GTK_WINDOW(janela_acoes),3);
	gtk_widget_set_name(janela_acoes,"janela_acoes");    
gtk_container_set_border_width(GTK_CONTAINER(janela_acoes),3);
    gtk_widget_set_size_request(janela_acoes,400,200);

	opcoes = malloc(sizeof(GtkRadioButton*)*5);

	opcoes[0] = gtk_radio_button_new_with_label(lista_opcoes,"Mover mouse");
	opcoes[1] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(opcoes[0]),"Escrever");
	opcoes[2] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(opcoes[1]),"Clicar");
	opcoes[3] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(opcoes[2]),"Pressionar uma Tecla(Sem funcionar)");
	opcoes[4] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(opcoes[3]),"Aguardar");
	
	//criar menu
	caixa_tecla = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(caixa_tecla),"1","Enter");
	
	escrever = gtk_box_new(0,0);
	escrever_label = gtk_label_new("Insira o Texto");
	escrever_entry = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(escrever),escrever_label,0,0,10);
        gtk_box_pack_start(GTK_BOX(escrever),escrever_entry,0,0,10);
	
	clicar_label = gtk_label_new("Fará um clique na posicao do mouse");
	
	posicao = gtk_box_new(0,0);
	x = 0;
	y = 0;
	sprintf(texto_pos,"(%i,%i)",x,y);
	move_label   = gtk_label_new(texto_pos);
	posicao_mouse_button = gtk_button_new_with_label("Pegar Posicao do Mouse");
        
	aguardar       = gtk_box_new(0,0);
	aguardar_label = gtk_label_new("Quanto tempo deseja aguardar?");
       	aguardar_entry = gtk_entry_new();	
        
	gtk_box_pack_start(GTK_BOX(aguardar),aguardar_label,0,0,10);
        gtk_box_pack_start(GTK_BOX(aguardar),aguardar_entry,0,0,10);

	gtk_box_pack_start(GTK_BOX(posicao),posicao_mouse_button,0,0,10);
        gtk_box_pack_start(GTK_BOX(posicao),move_label,0,0,10);

	tecla = gtk_box_new(0,0);
	tecla_label = gtk_label_new("Insira a tecla");
        gtk_box_pack_start(GTK_BOX(tecla),tecla_label,0,0,10);
        gtk_box_pack_start(GTK_BOX(tecla),caixa_tecla,0,0,10);

	caixa1 = gtk_box_new(1,0);
	caixa2 = gtk_box_new(0,0);
	caixa_principal = gtk_box_new(1,0);

	img_ok = gtk_image_new_from_file(IMG_OK);
        img_cancelar = gtk_image_new_from_file(IMG_CANCEL);
	
	botao_ok = gtk_button_new_with_label("Ok");
	botao_cancelar = gtk_button_new_with_label("Cancelar");
	gtk_button_set_image(GTK_BUTTON(botao_ok),img_ok);
	gtk_button_set_image(GTK_BUTTON(botao_cancelar),img_cancelar);

        gtk_box_pack_start(GTK_BOX(caixa1),opcoes[0],0,0,10);
        gtk_box_pack_start(GTK_BOX(caixa1),posicao,0,0,0);
        gtk_box_pack_start(GTK_BOX(caixa1),separadores[0],0,0,10);

        gtk_box_pack_start(GTK_BOX(caixa1),opcoes[1],0,0,10);
        gtk_box_pack_start(GTK_BOX(caixa1),escrever,0,0,0);
        gtk_box_pack_start(GTK_BOX(caixa1),separadores[1],0,0,10);
       
       	gtk_box_pack_start(GTK_BOX(caixa1),opcoes[2],0,0,10);
       	gtk_box_pack_start(GTK_BOX(caixa1),clicar_label,0,0,10);
        gtk_box_pack_start(GTK_BOX(caixa1),separadores[2],0,0,10);
       
       	gtk_box_pack_start(GTK_BOX(caixa1),opcoes[3],0,0,10);
        gtk_box_pack_start(GTK_BOX(caixa1),tecla,0,0,0);
        gtk_box_pack_start(GTK_BOX(caixa1),separadores[3],0,0,10);

       	gtk_box_pack_start(GTK_BOX(caixa1),opcoes[4],0,0,10);
        gtk_box_pack_start(GTK_BOX(caixa1),aguardar,0,0,0);
        gtk_box_pack_start(GTK_BOX(caixa1),separadores[4],0,0,10);
        
	gtk_box_pack_end(GTK_BOX(caixa2),botao_cancelar,0,0,5);
	gtk_box_pack_end(GTK_BOX(caixa2),botao_ok,0,0,5);

        gtk_box_pack_start(GTK_BOX(caixa_principal),caixa1,0,0,10);
        gtk_widget_set_size_request(caixa1,400,150);
        gtk_box_pack_end(GTK_BOX(caixa_principal),caixa2,0,0,0);
        gtk_widget_set_size_request(caixa2,400,50);
	
	gtk_container_add(GTK_CONTAINER(janela_acoes),caixa_principal);
	g_signal_connect(janela_acoes,"destroy",G_CALLBACK(fechar),janela_acoes);
        g_signal_connect(botao_cancelar,"clicked",G_CALLBACK(fechar),janela_acoes);
        g_signal_connect(botao_ok,"clicked",G_CALLBACK(ok_acao),opcoes);
	g_signal_connect(GTK_TOGGLE_BUTTON(opcoes[0]),"toggled",G_CALLBACK(mudanca),opcoes);
	g_signal_connect(GTK_TOGGLE_BUTTON(opcoes[1]),"toggled",G_CALLBACK(mudanca),opcoes);
	g_signal_connect(GTK_TOGGLE_BUTTON(opcoes[2]),"toggled",G_CALLBACK(mudanca),opcoes);
	g_signal_connect(GTK_TOGGLE_BUTTON(opcoes[3]),"toggled",G_CALLBACK(mudanca),opcoes);
	g_signal_connect(GTK_TOGGLE_BUTTON(opcoes[4]),"toggled",G_CALLBACK(mudanca),opcoes);
	g_signal_connect(GTK_WIDGET(posicao_mouse_button),"clicked",G_CALLBACK(pegar_posicao),NULL);
	gtk_widget_show_all(janela_acoes);
	gtk_widget_hide(escrever_label);
	gtk_widget_hide(tecla);
	gtk_widget_hide(clicar_label);
	gtk_widget_hide(escrever_entry);
	gtk_widget_hide(aguardar);
}
