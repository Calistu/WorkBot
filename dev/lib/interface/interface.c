#include <gtk/gtk.h>
GtkWidget *janela;
#include "etc/css.c"

#define IMG_INIT   "/workbot/data/interface/imgs/iniciar.png"
#define IMG_PAUSE  "/workbot/data/interface/imgs/pause.png"
#define IMG_FECHA  "/workbot/data/interface/imgs/fecha.png"
#define IMG_MAIS   "/workbot/data/interface/imgs/mais.png"
#define PRINC_CSS  "/workbot/data/interface/princ.css"
#define IMG_SAVE   "/workbot/data/interface/imgs/salvar.png"
#define IMG_CANC   "/workbot/data/interface/imgs/cancelar.png"
#define IMG_REM   "/workbot/data/interface/imgs/remover.png"

char *caminho_arq;

GtkWidget *caixa_acoes,  *caixa_parametros,*caixa_lista;
GtkWidget *loop,                    *checkbox_loop;
GtkWidget *velocidade,              *velocidade_entry,            *velocidade_label;
GtkWidget *iniciar_apos,            *iniciar_apos_label,          *iniciar_apos_spin;
GtkWidget *marcar_inicio,           *marcar_inicio_checkbox,      *marcar_horario,
	  *marcar_inicio_hora,      *marcar_inicio_minutos,       *marcar_inicio_segundos,
	  *marcar_inicio_hora_label,*marcar_inicio_minutos_label, *marcar_inicio_segundos_label;
GtkWidget *botao_fecha;
GtkWidget *botao_mais_acoes;
GtkWidget *img_iniciar,             *img_fecha,       *img_mais;
GtkWidget *frame_acoes,             *frame_parametros,*frame_lista;
#include "acoes/dados.c"
acoes     nova_acao[30];

GtkWidget **acao;
GtkWidget **remover;
GtkWidget **acao_container;
GtkWidget **img_remover;

GtkWidget *scroll_acoes;
GtkWidget *scroll_caixa;

GtkWidget *finaliza;
GtkWidget *salvar_acoes,    *cancelar_acoes;
GtkWidget *salvar_acoes_img,*cancelar_acoes_img;

GtkWidget *tarefas_listadas;
GtkWidget *espaco_rolamento_lista;

#include "acoes/adicionar.c"
#include "acoes/salvar.c"
#include "acoes/executar.c"
#include "acoes/cancelar.c"
#include "acoes/listar.c"

int main()
{
	int exec_interface();
	exec_interface();
}

int exec_interface()
{
	gtk_init(NULL,NULL);
	abrir_css(PRINC_CSS);
	GtkWidget *barra;
	GtkWidget *caixa_principal,*caixas;
	GtkWidget *separador1,*separador2,*separador3,*separador_barra;
	GtkWidget *separador_param1,*separador_param2,*separador_param3;
	
	acao           = malloc(sizeof(GtkLabel*)*30);       
	remover        = malloc(sizeof(GtkButton*)*30);       
	img_remover    = malloc(sizeof(GtkImage*)*30);       
	acao_container = malloc(sizeof(GtkBox*)*30);       

	finaliza           = gtk_box_new(1,0);
	salvar_acoes       = gtk_button_new_with_label("Salvar");
	salvar_acoes_img   = gtk_image_new_from_file(IMG_SAVE);
	cancelar_acoes     = gtk_button_new_with_label("Cancelar");
	cancelar_acoes_img = gtk_image_new_from_file(IMG_CANC);
	gtk_box_pack_start(GTK_BOX(finaliza),salvar_acoes,0,0,0);
	gtk_box_pack_start(GTK_BOX(finaliza),cancelar_acoes,0,0,0);
		
	scroll_caixa = gtk_box_new(0,0);
	scroll_acoes = gtk_scrolled_window_new(NULL,NULL);
	
	loop             = gtk_box_new(1,0);  
	checkbox_loop    = gtk_check_button_new_with_label("Fazer Loop?");
	gtk_box_pack_start(GTK_BOX(loop),checkbox_loop,0,0,0);

	velocidade_label = gtk_label_new("Qual velocidade da execucao?");
	velocidade_entry = gtk_spin_button_new_with_range(1,5,1);
       	velocidade       = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(velocidade),velocidade_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(velocidade),velocidade_entry,0,0,0);
	
	iniciar_apos       = gtk_box_new(1,0);
	iniciar_apos_spin  = gtk_spin_button_new_with_range(1,1000,1);
	iniciar_apos_label = gtk_label_new("Iniciar após quantos segundos?");
	gtk_box_pack_start(GTK_BOX(iniciar_apos),iniciar_apos_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(iniciar_apos),iniciar_apos_spin,0,0,0);

	marcar_inicio          = gtk_box_new(1,0); 
	marcar_horario         = gtk_box_new(1,0);
	marcar_inicio_hora     = gtk_spin_button_new_with_range(0,23,1);
	marcar_inicio_minutos  = gtk_spin_button_new_with_range(0,59,1);
	marcar_inicio_segundos = gtk_spin_button_new_with_range(0,59,1);
	marcar_inicio_hora_label     = gtk_label_new("Horas:");
	marcar_inicio_minutos_label  = gtk_label_new("Minutos:");
	marcar_inicio_segundos_label = gtk_label_new("Segundos:");
	marcar_inicio_checkbox    = gtk_check_button_new_with_label("Marcar para iniciar?");
	
	tarefas_listadas = gtk_box_new(0,0);
	espaco_rolamento_lista = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(espaco_rolamento_lista),tarefas_listadas);

	gtk_box_pack_start(GTK_BOX(marcar_inicio),marcar_inicio_checkbox,0,0,0);
	gtk_box_pack_start(GTK_BOX(marcar_horario),marcar_inicio_hora_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(marcar_horario),marcar_inicio_hora,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(marcar_horario),marcar_inicio_minutos_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(marcar_horario),marcar_inicio_minutos,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(marcar_horario),marcar_inicio_segundos_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(marcar_horario),marcar_inicio_segundos,0,0,0);

	gtk_box_pack_start(GTK_BOX(marcar_inicio),marcar_horario,0,0,0);

	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_title(GTK_WINDOW(janela),"WorkBot");
	gtk_container_set_border_width(GTK_CONTAINER(janela),10);
	gtk_window_set_decorated(GTK_WINDOW(janela),TRUE);

	gtk_widget_set_size_request(janela,1280,640);

	frame_acoes      = gtk_frame_new("Ações");
	frame_parametros = gtk_frame_new("Parametros");
	frame_lista      = gtk_frame_new("Salvos");

	img_fecha   = gtk_image_new_from_file(IMG_FECHA);
	img_mais    = gtk_image_new_from_file(IMG_MAIS);
	
	caixa_principal = gtk_box_new(0,0);
	caixas          = gtk_box_new(1,0);
	barra           = gtk_box_new(1,0);
	
	caixa_acoes      = gtk_box_new(0,0);
	caixa_parametros = gtk_box_new(0,0);
	caixa_lista = gtk_box_new(0,0);
	
	separador1       = gtk_separator_new(0);
	separador2       = gtk_separator_new(0);
	separador3       = gtk_separator_new(0);
	separador_barra  = gtk_separator_new(1);
	
	separador_param1       = gtk_separator_new(1);
	separador_param2       = gtk_separator_new(1);
	separador_param3       = gtk_separator_new(1);
	
	botao_mais_acoes = gtk_button_new_with_label("Ação");
	gtk_widget_set_name(botao_mais_acoes,"botao_acoes");
	gtk_widget_set_size_request(botao_mais_acoes,80,20);

	botao_fecha = gtk_button_new_with_label("Sair");
	gtk_widget_set_name(botao_mais_acoes,"botao_fecha");
	gtk_widget_set_size_request(botao_fecha,80,20);

	gtk_button_set_image(GTK_BUTTON(botao_fecha),img_fecha);
	gtk_button_set_image(GTK_BUTTON(botao_mais_acoes),img_mais);
	gtk_button_set_image(GTK_BUTTON(salvar_acoes),salvar_acoes_img);
	gtk_button_set_image(GTK_BUTTON(cancelar_acoes),cancelar_acoes_img);
	
	gtk_box_pack_start(GTK_BOX(caixas),frame_acoes,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixas),separador1,0,0,0);

	gtk_box_pack_start(GTK_BOX(caixas),frame_parametros,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixas),separador2,0,0,0);

	gtk_box_pack_start(GTK_BOX(caixas),frame_lista,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixas),separador3,0,0,0);

	gtk_box_pack_start(GTK_BOX(caixa_principal),caixas,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_principal),separador_barra,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_principal),barra,0,0,0);
	gtk_box_pack_end(GTK_BOX(barra),botao_fecha,0,0,20);
	
	gtk_widget_set_size_request(frame_acoes,1200,200);
	gtk_widget_set_size_request(frame_parametros,1200,200);
	gtk_widget_set_size_request(frame_lista,1200,200);	
	
	gtk_widget_set_size_request(barra,80,640);

	gtk_container_add(GTK_CONTAINER(frame_acoes),caixa_acoes);
	gtk_box_pack_start(GTK_BOX(caixa_acoes),botao_mais_acoes,0,0,10);
	gtk_widget_set_name(botao_mais_acoes,"botao_mais");
	gtk_box_pack_start(GTK_BOX(caixa_acoes),scroll_acoes,0,0,10);
	
	//scroll acoes - scrolled_window
//	gtk_container_add(GTK_CONTAINER(scroll_acoes),scroll_caixa);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll_acoes),scroll_caixa);
	
	gtk_widget_set_size_request(scroll_caixa,1000,200);	
	gtk_widget_set_size_request(scroll_acoes,1000,200);	

	gtk_box_pack_end(GTK_BOX(caixa_acoes),finaliza,0,0,5);
	gtk_widget_set_sensitive(finaliza,FALSE);

	gtk_container_add(GTK_CONTAINER(frame_parametros),caixa_parametros);

	gtk_box_pack_start(GTK_BOX(caixa_parametros),loop,0,0,40);
	gtk_box_pack_start(GTK_BOX(caixa_parametros),separador_param1,0,0,10);

	gtk_box_pack_start(GTK_BOX(caixa_parametros),velocidade,0,0,40);
	gtk_box_pack_start(GTK_BOX(caixa_parametros),separador_param2,0,0,10);

	gtk_box_pack_start(GTK_BOX(caixa_parametros),iniciar_apos,0,0,40);
	gtk_box_pack_start(GTK_BOX(caixa_parametros),separador_param3,0,0,10);

	gtk_box_pack_start(GTK_BOX(caixa_parametros),marcar_inicio,0,0,40);
	
	gtk_widget_set_size_request(frame_lista,1000,200);	
	gtk_container_add(GTK_CONTAINER(frame_lista),espaco_rolamento_lista);	
	exec_listas();
	gtk_container_add(GTK_CONTAINER(janela),caixa_principal);
	g_signal_connect(janela,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect(botao_fecha,"clicked",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect(botao_mais_acoes,"clicked",G_CALLBACK(adicionar_acao),NULL);
	g_signal_connect(cancelar_acoes,"clicked",G_CALLBACK(exec_cancelar),NULL);
	g_signal_connect(salvar_acoes,"clicked",G_CALLBACK(exec_salvar),NULL);
	gtk_widget_show_all(janela);
	gtk_main();
}



