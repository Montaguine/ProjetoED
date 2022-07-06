#include "funcoes.h"
#include "registros.h"

int main(int argc, char *argv[]) 
{
	Hash dados;
	int i;
	for(i = 0; i < N; i++)
  	dados[i] = NULL;

	carregaRegistros(dados);

	do
	{
		system("pause");
		system("cls");
		fMenu();
		if(menu==1)
		{
			view(dados);
		}
		if(menu==2)
		{
			busca(dados, dadosBusca());
		}
	}while (menu!=0);
	
	return 0;
}
