#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <windows.h>
#include "../lib/stoi/stoi.h"
#include "../lib/vars.h"
#include <gtk/gtk.h>
int leitura_execucao(GtkWidget*,gpointer);	
struct tagPOINT ponteiro;
#include "../lib/interface/interface.h"
INPUT teclado;
INPUT mouse;
int main(void)
{ 
	FreeConsole();
	setlocale(LC_ALL,"Portuguese");
	nome_acao  = malloc(20);
	xchar = malloc(10);
	ychar = malloc(10);
	texto = malloc(30);
	tempo_char = malloc(10);
	exec_interface();

}


int leitura_execucao(GtkWidget *widget,gpointer ponteiro)
{
	gtk_widget_hide(janela);
	parametros = fopen((char*)ponteiro,"r");
	if(parametros==NULL)
	{
		printf("Erro ao procurar tarefa\n");
		return 1;
	}
	int mover(int,int), esperar(int), clicar(void), acao_escrever(char*),escrever_letra(char), maiuscular(char*);
	while(1)
	{
		linhas++;	
		if(fgets(nome_acao,20,parametros)==NULL)
			break;
		nome_acao[strlen(nome_acao)-1] = '\0';
		if(nome_acao[0] == '@')
		{
			printf("comentario encontrado %s\n",nome_acao+1);
		}
		if(strcmp(nome_acao,"mover")==0)
		{
			printf("mover reconhecido\n");
			fgets(xchar,10,parametros);
			xchar[strlen(xchar)-1] = '\0';
			xint = stoi(xchar);
			if(xint == -1)
			{
				printf("posicao x na nome_acao linha %i não foi reconhecida\n",linhas);
				return 1;
			}
			fgets(ychar,10,parametros);
			ychar[strlen(ychar)-1] = '\0';
			yint = stoi(ychar);
			if(yint == -1)
			{
				printf("posicao x na nome_acao linha %i não foi reconhecida\n",linhas);
				return 1;
			}
			printf("mover para %i,%i\n",xint,yint);
			mover(xint,yint);
			memset(nome_acao,0x0,strlen(nome_acao));
			memset(texto,0x0,strlen(texto));
			memset(xchar,0x0,strlen(xchar));
			memset(ychar,0x0,strlen(ychar));
		}	
		if(strcmp(nome_acao,"esperar")==0)
		{
			printf("esperar reconhecido\n");
			fgets(tempo_char,10,parametros);
			tempo_char[strlen(tempo_char)-1] = 0x0;
			tempo = stoi(tempo_char);
			if(tempo == -1)
			{
				printf("tempo na nome_acao linha %i não foi reconhecida\n",linhas);
				return 1;
			}
			printf("esperando %i segundos...\n",tempo);
			sleep(tempo);
			printf("ok!\n");
		}
		if(strcmp(nome_acao,"clicar")==0)
		{	
			printf("Clicar reconhecido\n");
			clicar();
		}
		if(strcmp(nome_acao,"escrever")==0)
		{
			printf("escrever reconhecido\n");
			fgets(texto,30,parametros);
			texto[strlen(texto)-1] = '\0';
			printf("Escrevendo %s\n",texto);
			maiuscular(texto);
			acao_escrever(texto);
			memset(nome_acao,0x0,strlen(nome_acao));
			memset(texto,0x0,strlen(texto));
		}
		if(strcmp(nome_acao,"enter")==0)
		{
			printf("enter reconhecido\n");
			escrever_letra(0xd);
		}
		//teclas FX
		if(strcmp(nome_acao,"tecla_f3")==0)
		{
			printf("Tecla F3 recebido\n");
			escrever_letra(0x72);
		}
		if(strcmp(nome_acao,"tecla_f4")==0)
		{
			printf("Tecla F4 recebido\n");
			escrever_letra(0x73);
		}
		if(strcmp(nome_acao,"tecla_f5")==0)
		{
			printf("Tecla F5 recebido\n");
			escrever_letra(0x74);
		}
		if(strcmp(nome_acao,"tecla_f6")==0)
		{
			printf("Tecla F6 recebido\n");
			escrever_letra(0x75);
		}
		if(strcmp(nome_acao,"tecla_f7")==0)
		{
			printf("Tecla F7 recebido\n");
			escrever_letra(0x76);
		}
		if(strcmp(nome_acao,"tecla_f8")==0)
		{
			printf("Tecla F8 recebido\n");
			escrever_letra(0x77);
		}
		//SETAS DO TECLADO
		if(strcmp(nome_acao,"tecla_cima")==0)
		{
			printf("Tecla para cima recebido\n");
			escrever_letra(0x26);
		}
		if(strcmp(nome_acao,"tecla_baixo")==0)
		{
			printf("Tecla para baixo recebido\n");
			escrever_letra(0x28);
		}
		if(strcmp(nome_acao,"tecla_direita")==0)
		{
			printf("Tecla para direita recebido\n");
			escrever_letra(0x27);
		}
		if(strcmp(nome_acao,"tecla_esquerda")==0)
		{
			printf("Tecla para esquerda recebido\n");
			escrever_letra(0x25);
		}
	}
	gtk_widget_show_all(janela);
	fclose(parametros);	
}

int esperar(int segundos)
{
	Sleep(segundos);
	return 0;
}

int clicar(void)
{
	GetCursorPos(&ponteiro);
	mouse.type = INPUT_MOUSE;
	mouse.mi.dx = ponteiro.x;
	mouse.mi.dy = ponteiro.y;
	mouse.mi.time = 0;
	mouse.mi.dwFlags = MOUSEEVENTF_LEFTDOWN ;
	if(SendInput(1,&mouse,sizeof(INPUT))==0)
	{
		printf("%s\n", GetLastError());
	}
	mouse.mi.dwFlags = MOUSEEVENTF_LEFTUP ;
	if(SendInput(1,&mouse,sizeof(INPUT))==0)
	{
		printf("%s\n", GetLastError());
	}	
	GetCursorPos(&ponteiro);


}
int mover(int PX,int PY)
{
	GetCursorPos(&ponteiro);
	if(ponteiro.x<PX)
	{
		while(ponteiro.x<PX)	
		{
			GetCursorPos(&ponteiro);
			SetCursorPos(ponteiro.x+1,ponteiro.y);
		}
	}
	else
	{
		while(ponteiro.x>PX)	
		{
			GetCursorPos(&ponteiro);
			SetCursorPos(ponteiro.x-1,ponteiro.y);
		}
	}
	GetCursorPos(&ponteiro);
	if(ponteiro.y<PY)
	{
		while(ponteiro.y<PY)	
		{
			GetCursorPos(&ponteiro);
			SetCursorPos(ponteiro.x,ponteiro.y+1);
		}
	}
	else
	{
		while(ponteiro.y>PY)	
		{
			GetCursorPos(&ponteiro);
			SetCursorPos(ponteiro.x,ponteiro.y-1);
		}
	}
	GetCursorPos(&ponteiro);
	if(ponteiro.x == PX && ponteiro.y == PY)
		return 0;

}
int acao_escrever(char *texto)
{
	int escrever_letra(char);
	int pos=0;
	int len = strlen(texto);
	printf("escrevendo: ");
	for(pos;pos<len;pos++)
		escrever_letra(texto[pos]);

	printf("\n");
}
int escrever_letra(char letra)
{
	printf("%c",letra);
	teclado.type       = INPUT_KEYBOARD;
	teclado.ki.wVk     = letra;
	teclado.ki.time    = 0;
       	teclado.ki.dwFlags = 0;	
	SendInput(1,&teclado,sizeof(INPUT));
	teclado.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1,&teclado,sizeof(INPUT));
	
}
int maiuscular(char *texto)
{
	int len = strlen(texto);
	int pos=0,ascii=0,maiuscula=0;
	for(pos;pos<=len;pos++)
	{
		maiuscula = 65;
		for(ascii=97;ascii<=122;ascii++)
		{
			if(texto[pos]==ascii)
			{
				texto[pos] = maiuscula;	
			}
			maiuscula++;
		}
	
	
	}

}
