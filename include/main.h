#include <gtk/gtk.h>

int init_main();
#define MAIN_WND_BUILDER "glade/main.glade"
#define MAX_ACOES_QNT 20
static GtkWidget *main_wnd, *acoes_list_grid;
static GtkWidget **acao_box;
