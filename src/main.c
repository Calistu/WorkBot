#include <main.h>

int load_main_wnd(){
  GtkBuilder *main_builder = gtk_builder_new_from_file(MAIN_WND_BUILDER);
  if(!main_builder){
    gtk_widget_show_all(gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_NONE, "Não foi possível abrir construtor"));
    return 1;
  }

  main_wnd = GTK_WIDGET(gtk_builder_get_object(main_builder,"main_wnd"));
  acoes_list_grid = GTK_WIDGET(gtk_builder_get_object(main_builder,"acoes_list_grid"));
  acao_box = malloc(sizeof(GtkWidget*)*MAX_ACOES_QNT);

  for(int cont=0;cont<MAX_ACOES_QNT;cont++){

    GtkBuilder *acao_builder = gtk_builder_new_from_file(MAIN_WND_BUILDER);
    if(!acao_builder){
      gtk_widget_show_all(gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_NONE, "Não foi possível abrir construtor"));
      return 1;
    }
    acao_box[cont] = GTK_WIDGET(gtk_builder_get_object(acao_builder,"acao_box"));
    gtk_grid_attach(GTK_GRID(acoes_list_grid),acao_box[cont],cont,0,1,1);

  }

  gtk_window_maximize(GTK_WINDOW(main_wnd));
  gtk_builder_connect_signals(main_builder,NULL);

  gtk_widget_show_all(main_wnd);
  return 0;
}

int init_main(){
  gtk_init(NULL,NULL);

  if(load_main_wnd())
    return 1;

  gtk_main();
}
