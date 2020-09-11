#include <stdio.h>
#include <stdlib.h>
#include "mat.h"

int main(int argc, char**argv)
{
	/* declaracao de variaveis */
	int dimensao, linha, coluna;
	float valor;
	
	/* declara celula nao inicializada */
	Celula* c;
	
	/* declara matriz não inicializada */
	Matriz *m1, *m2, *m3;
	
	/* abertura dos arquivos */
	FILE *arq1, *arq2;
	arq1 = fopen(argv[1], "r");
	arq2 = fopen(argv[2], "r");
	
	/* leitura da dimensao de cada matriz */
	fscanf(arq1, "%d", &dimensao);
	fscanf(arq2, "%d", &dimensao);
	
	/* criacao de cada matriz */
	m1 = cria_matriz(dimensao);
	m2 = cria_matriz(dimensao);
	
	
	/* leitura dos valores da matriz 1 */
	while (fscanf(arq1, "%d;%d;%f", &linha, &coluna, &valor) != EOF)
	{
		/* se o valor for igual a 0, remove o elemento da matriz */ 
		if (valor == 0.0)
			/* decrementa 1 do valores da linha e coluna lidos do arquivo */
			remove_celula(m1, linha-1, coluna-1);
		
		else
		{
			/* decrementa 1 do valores da linha e coluna lidos do arquivo */
			c = cria_celula(linha-1, coluna-1, valor);
			insere_celula(c, m1);
		}
	}
	
	/* leitura dos valores da matriz 2 */
	while (fscanf(arq2, "%d;%d;%f", &linha, &coluna, &valor) != EOF)
	{
		if (valor == 0.0)
			remove_celula(m2, linha-1, coluna-1);
		
		else
		{
			c = cria_celula(linha-1, coluna-1, valor);
			insere_celula(c, m2);
		}
	}
	
	/* fecha os arquivos */
	fclose(arq1);
	fclose(arq2);
	
	/* cria terceira matriz */
	m3 = cria_matriz(dimensao);
	
	/* soma as duas matrizes */
	soma(m1, m2, m3);
	
	/* imprime matriz */
	imprime_matriz(m3);
	
	return 0;
}