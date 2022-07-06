#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int menu;
int id;
char nome[25];
char endereco[50];
char cidade[20];
char pais[20];
char telefone[20];

int fMenu()
{
	printf("-----------------------------------"
"Sistema de implementacao Double hash e lista"

"-----------------------------------------\n"

"\n\n-----[1] Listar todos os registros"
"\n"
"-----[2] Pesquisar registro"
"\n"
"-----[0] Sair\n"
"\n"
"-----------------------------------------------"
"-----------------------------------------------"
"--------------------------\n");
	scanf("%d", &menu);
	return menu;
}


int dadosBusca()
{
	int i;
	printf("Informe o ID do registro:");
	scanf("%d", &i);
	return i;
}


