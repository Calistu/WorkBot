int exec_cancelar()
{
	int i;
	for(i=0;i<=qnt_acoes;i++)
	{
		if(gtk_widget_get_visible(acao_container[i])!=FALSE)
		{
			gtk_widget_destroy(acao_container[i]);
			memset(&nova_acao[i],0x0,sizeof(nova_acao[i]));
		}
	
	}
	qnt_acoes   = 0;
	qnt_remove  = 0;
	gtk_widget_set_sensitive(finaliza,FALSE);	
}
