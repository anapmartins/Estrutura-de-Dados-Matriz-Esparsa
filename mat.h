
#ifndef __MAT__
#define __MAT__

struct celula
{
	int linha, coluna;
	float valor;
	struct celula *proxLinha;
	struct celula *proxColuna;
};

struct matriz
{
	int dimensao;
	struct celula **cabLinha;
	struct celula **cabColuna;
};

typedef struct celula Celula;

typedef struct matriz Matriz;

Matriz* cria_matriz(int tam);

Celula* cria_celula(int lin, int col, float valor);

void insere_celula(Celula *nova_cell, Matriz *matriz);

void imprime_matriz(Matriz *matriz);

void remove_celula(Matriz *matriz, int lin, int col);

void destroi_matriz(Matriz *matriz);

void soma(Matriz *m1, Matriz *m2, Matriz *m3);

#endif
