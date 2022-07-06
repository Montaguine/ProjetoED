#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *registros;

#define tamNome 25
#define tamEnd 50
#define tamCid 20
#define tamPais 20
#define tamTelef 20
#define N 100

typedef struct listaRegistros ListaRegistros;

struct listaRegistros
{
	int id;
	char nome[tamNome];
	char endereco[tamEnd];
	char cidade[tamCid];
	char pais[tamPais];
	char telefone[tamTelef];
    struct listaRegistros *proximo;
    struct listaRegistros *inicio;
};

typedef ListaRegistros* Hash[N];

int hash (int id)
{
	return (id%100);
}

ListaRegistros *criaListaRegistros(ListaRegistros *l)
{
	return(NULL);
}

void setRegistros(Hash tab, int id, char nome[tamNome], char endereco[tamEnd], char cidade[tamCid], char pais[tamPais], char telefone[tamTelef])
{
	int h = hash(id);
	ListaRegistros *novo = (ListaRegistros*) malloc(sizeof(ListaRegistros));
	novo = tab[h];
	
	if (tab[h] != NULL)
	{
		while (novo->proximo != NULL)
		{
			novo=novo->proximo;
		}

		novo->proximo = (ListaRegistros*) malloc(sizeof(ListaRegistros));
		novo->proximo->id=id;
		strcpy(novo->proximo->nome,nome);
		strcpy(novo->proximo->endereco,endereco);
		strcpy(novo->proximo->cidade,cidade);
		strcpy(novo->proximo->pais,pais);
		strcpy(novo->proximo->telefone,telefone);
	}

	if (tab[h]==NULL)
	{
		tab[h] = (ListaRegistros*) malloc(sizeof(ListaRegistros));
		tab[h]->id = id;
		tab[h]->id=id;
		strcpy(tab[h]->nome,nome);
		strcpy(tab[h]->endereco,endereco);
		strcpy(tab[h]->cidade,cidade);
		strcpy(tab[h]->pais,pais);
		strcpy(tab[h]->telefone,telefone);
		tab[h]->proximo=NULL;
	}
}


void carregaRegistros(Hash tab)
{
	if((registros = fopen("Dados.csv","r")) == NULL)
	{
		printf("Erro na leitura do arquivo de registros");
	}
	else
	{
		while (!feof(registros))
		{
			if (fscanf(registros, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];", &id, nome, endereco, cidade, pais, telefone) == 6)
			{
				setRegistros(tab, id, nome, endereco, cidade, pais, telefone);
			}
		}
		fclose(registros);
	}
}

void view(Hash tab)
{
	ListaRegistros *novo = (ListaRegistros*) malloc(sizeof(ListaRegistros));
	int i=0;
	for(i = 0; i < N; i++)
	{
		novo=tab[i];
		if (novo != NULL)
		{
			while (novo->proximo != NULL)
			{
				printf("Indice: %d - Id: %d - Nome: %s - Endereco: %s - Cidade: %s - Pais: %s - Telefone: %s\n", i, novo->id, novo->nome, novo->endereco, novo->cidade, novo->pais, novo->telefone);
				novo=novo->proximo;
			}
		}
		if(novo!=NULL)
		{
			printf("Indice: %d - Id: %d - Nome: %s - Endereco: %s - Cidade: %s - Pais: %s - Telefone: %s\n", i, novo->id, novo->nome, novo->endereco, novo->cidade, novo->pais, novo->telefone);
		}
	}
}

void busca(Hash tab, int id)
{
	ListaRegistros *novo = (ListaRegistros*) malloc(sizeof(ListaRegistros));

	int contador = 0;
	int h = hash(id);
	novo=tab[h];

	if (novo != NULL)
	{
		while (novo->proximo != NULL)
		{
			contador++;
			if(novo->id==id)
			{
				break;
			}
			novo=novo->proximo;
		}
		if (novo->id==id)
		{
			printf("Indice: %d - Id: %d - Nome: %s - Endereco: %s - Cidade: %s - Pais: %s - Telefone: %s\n", h, novo->id, novo->nome, novo->endereco, novo->cidade, novo->pais, novo->telefone);
			printf("Quantidade de acessos para localizar o elemento: %d\n", contador);	
		}

		if(novo->id!=id) printf("Elemento nao localizado!\n");
	}

	else printf("Ocorreu um erro!\n");
}
