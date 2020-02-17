int exec_cancelar()
{
	int i=0;
	printf("finalizando \n");
	while(i<qnt_acoes)
	{
		gtk_widget_destroy(acao_container[i]);
		memset(&nova_acao[i],0x0,sizeof(nova_acao[i]));
		i++;
	}
	qnt_acoes   = 0;
	qnt_remove  = 0;
	gtk_widget_set_sensitive(finaliza,FALSE);	
}
