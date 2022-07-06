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

void *setRegistros(Hash tab, int id, char nome[tamNome], char endereco[tamEnd], char cidade[tamCid], char pais[tamPais], char telefone[tamTelef])
{
	printf("id: %d chegou em setRegistros\n", id);
	int h = hash(id);
	if (tab[h] != NULL)
	{
		printf("id: %d vai em tab[%d] e a tab nao eh NULL\n", id, hash(id));
		if (tab[h]->inicio->proximo != NULL)
		{
			printf("procurando proximo NULL na lista da tab[%d]\n", h);
			tab[h]=tab[h]->inicio->proximo;
			printf("tab[%d]->proximo->id=%d\n", h, tab[h]->proximo->id);
		}

		tab[h]->proximo = (ListaRegistros*) malloc(sizeof(ListaRegistros));
		tab[h]->proximo->id=id;
		printf("tab[%d]->id:%d->proximo->id:%d\n", h, tab[h]->id, tab[h]->proximo->id);
		strcpy(tab[h]->proximo->nome,nome);
		strcpy(tab[h]->proximo->endereco,endereco);
		strcpy(tab[h]->proximo->cidade,cidade);
		strcpy(tab[h]->proximo->pais,pais);
		strcpy(tab[h]->proximo->telefone,telefone);
		tab[h]->proximo->proximo = (ListaRegistros*) malloc(sizeof(ListaRegistros));
		printf("tab[%d] id: %d encadeado na lista com sucesso\n", h, tab[h]->proximo->id);
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
		tab[h]->inicio=tab[h];
		tab[h]->proximo=NULL;
		printf("tab[%d] id: %d inserido como indice no array\n", h, tab[h]->id);
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
	int i=0;
	for(i = 0; i < N; i++)
	{
		if (tab[i] != NULL)
		{
			while (tab[i]->proximo != NULL)
			{
				printf("Indice: %d - Id: %d - Nome: %s - Endereco: %s - Cidade: %s - Pais: %s - Telefone: %s\n", i, tab[i]->id, tab[i]->nome, tab[i]->endereco, tab[i]->cidade, tab[i]->pais, tab[i]->telefone);				
				tab[i]=tab[i]->proximo;
			}
		}
		if(tab[i]!=NULL)
		{
			printf("Indice: %d - Id: %d - Nome: %s - Endereco: %s - Cidade: %s - Pais: %s - Telefone: %s\n", i, tab[i]->id, tab[i]->nome, tab[i]->endereco, tab[i]->cidade, tab[i]->pais, tab[i]->telefone);
		}	
	}
}

void busca(Hash tab, int id)
{
	int contador = 1;
	int h = hash(id);
	if(tab[h]->id != id)
	{
		printf("tab[%d]->id=%d nao eh igual o id informado: %d\n", h, tab[h]->id, id);
		while(tab[h]->id != id)
		{
			tab[h]=tab[h]->proximo;
			contador++;
			printf("proxima posicao = tab[%d]->id %d\n", h, tab[h]->id);
			if(tab[h]->proximo == NULL && tab[h]->id != id)
			{
				printf("Elemento nao localizado\n");
				printf("Quantidade de acessos: %d\n", contador);	
				break;
			}
		}
		if(tab[h]->id==id)
		{
			printf("Indice: %d - Id: %d - Nome: %s - Endereco: %s - Cidade: %s - Pais: %s - Telefone: %s\n", h, tab[h]->id, tab[h]->nome, tab[h]->endereco, tab[h]->cidade, tab[h]->pais, tab[h]->telefone);
			printf("Quantidade de acessos: %d\n", contador);
		}
	}
}
