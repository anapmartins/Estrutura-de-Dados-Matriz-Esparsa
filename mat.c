#include <stdio.h>
#include <stdlib.h>
#include "mat.h"


Matriz* cria_matriz(int tam)
{
	Matriz* matriz = (Matriz*) malloc(sizeof(Matriz));
	matriz->dimensao = tam;
	matriz->cabLinha = (Celula**) malloc(tam * sizeof(Celula*));
	matriz->cabColuna = (Celula**) malloc(tam * sizeof(Celula*));
	
	/* atribui NULL para todas as posicoes dos vetores */
	int i;
	for (i=0; i<tam; i++)
	{
		matriz->cabLinha[i] = NULL;
		matriz->cabColuna[i] = NULL;
	}
	
	return matriz;
}


Celula* cria_celula(int lin, int col, float valor)
{
	Celula* nova_cell = (Celula*) malloc(sizeof(Celula));
	nova_cell->valor = valor;
	nova_cell->coluna = col;
	nova_cell->linha = lin;
	nova_cell->proxLinha = NULL;
	nova_cell->proxColuna = NULL;
	
	return nova_cell;
}


void insere_celula(Celula* nova_cell, Matriz* matriz)
{
	/* insere uma celula em uma linha da matriz */
	/* verifica se a linha esta vazia */
	if (matriz->cabLinha[nova_cell->linha] == NULL)
		matriz->cabLinha[nova_cell->linha] = nova_cell;
	
	
	else
	{
		/* se a linha nao estiver vazia, o ponteiro percorre o vetor de colunas ate NULL */
		Celula* pl = matriz->cabLinha[nova_cell->linha];
		while (pl->proxColuna != NULL)
			pl = pl->proxColuna;
		pl->proxColuna = nova_cell;
	}
		
	/* insere uma celula em uma coluna da matriz */
	/* verifica se a coluna esta vazia */
	if (matriz->cabColuna[nova_cell->coluna] == NULL)
		matriz->cabColuna[nova_cell->coluna] = nova_cell;
		
	
	else
	{
		/* se a coluna nao estiver vazia, o ponteiro percorre o vetor de linhas ate achar NULL */
		Celula* pc = matriz->cabColuna[nova_cell->coluna];
		while (pc->proxLinha != NULL)
			pc = pc->proxLinha;
		pc->proxLinha = nova_cell;
	}
}


void imprime_matriz(Matriz* matriz)
{
	printf("%d\n", matriz->dimensao);
	
	int i;
	Celula* ap;
	
	for (i=0; i<matriz->dimensao; i++)
	{
		if (matriz->cabLinha[i] != NULL)
		{
			ap = matriz->cabLinha[i];
			while(ap != NULL) 
			{
				/* acrescenta 1 na linha e coluna para ficar de acordo com o exemplo */
				printf("%d;%d;%.2f \n", ap->linha+1, ap->coluna+1, ap->valor);
				ap = ap->proxColuna;
			}
		}		
	}
}


void remove_celula(Matriz* matriz, int lin, int col)
{
	/* ajusta ponteiros da celula da linha */
	Celula* pl = matriz->cabLinha[lin];
	Celula* antL = NULL;
	
	while (pl->coluna != col)
	{
		antL = pl;
		pl = pl->proxColuna;
	}
	
	if (antL == NULL)
		matriz->cabLinha[lin] = pl->proxColuna;
	else
		antL->proxColuna = pl->proxColuna;
	
	
	/* ajusta ponteiros da celula da coluna */
	Celula* pc = matriz->cabColuna[col];
	Celula* antC = NULL;
	while (pl->linha != lin)
	{
		antC = pc;
		pc = pc->proxLinha;
	}
	
	if (antC == NULL)
		matriz->cabColuna[col] = pc->proxLinha;
	else
		antC->proxLinha = pc->proxLinha;
	
	free(pl);

}


void destroi_matriz(Matriz* matriz)
{
	int i;
	Celula* p;
	
	for (i=0; i<matriz->dimensao; i++)
	{
		p = matriz->cabLinha[i];
		while(p != NULL)
		{
			Celula* t = p->proxColuna;  	/* guarda referencia para proxima celula */
			free(p);						
			p = t; 							
		}		
	}
	
	free(matriz->cabLinha);
	free(matriz->cabColuna);
}


void soma(Matriz* m1, Matriz* m2, Matriz* m3)
{
	int i;
	float soma;
	Celula *p1, *p2, *c;
	
	for (i=0; i<m1->dimensao; i++)
	{
		p1 = m1->cabLinha[i];
		p2 = m2->cabLinha[i];
		
		/* se a linha i de m1 for zero, o resultado eh prenchido com os valores da linha i de m2 */
		if (p1 == NULL && p2 != NULL)
		{
			while (p2 != NULL)
			{
				c = cria_celula(p2->linha, p2->coluna,p2->valor);
				insere_celula(c, m3);
				p2 = p2->proxColuna;
			}
		}

		else if (p2 == NULL && p1 != NULL)
		{
			while (p1 != NULL)
			{
				c = cria_celula(p1->linha, p1->coluna,p1->valor);
				insere_celula(c, m3);
				p1 = p1->proxColuna;
			}
		}
		

		else while(p1 != NULL && p2 != NULL)
		{
			/* se uma coluna estiver preenchida em apenas uma das matrizes, o valor eh copiado para o resultado */
			if (p1->coluna < p2->coluna)
			{
				c = cria_celula(p1->linha, p1->coluna,p1->valor);
				insere_celula(c, m3);
				p1 = p1->proxColuna;
			}

			else if (p2->coluna < p1->coluna)
			{
				c = cria_celula(p2->linha, p2->coluna,p2->valor);
				insere_celula(c, m3);
				p2 = p2->proxColuna;
			}

			/* se uma coluna estiver preenchida nas duas matrizes, os valores sao somados */
			else if (p2->coluna == p1->coluna)
			{
				soma = p2->valor + p1->valor;
				c = cria_celula(p2->linha, p2->coluna, soma);
				insere_celula(c, m3);
				p1 = p1->proxColuna;
				p2 = p2->proxColuna;
			}	
			
		}
		
		/* quando uma das linhas acaba, copia o valor da outra para o resultado */
		while (p2 == NULL && p1 != NULL)
			{
				c = cria_celula(p1->linha, p1->coluna, p1->valor);
				insere_celula(c, m3);
				p1 = p1->proxColuna;
			}
			
		while (p1 == NULL && p2 != NULL)
			{
				c = cria_celula(p2->linha, p2->coluna, p2->valor);
				insere_celula(c, m3);
				p2 = p2->proxColuna;
			}			
	}
}

