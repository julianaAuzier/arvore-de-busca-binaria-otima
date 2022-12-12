#include <stdio.h>
#include<stdlib.h>
#define NMAX 20

typedef struct OBST{
	int KEY;
	struct OBST *left, *right;
}OBST;

int C[NMAX][NMAX]; //matriz de custo
int W[NMAX][NMAX]; //matriz de pesos
int R[NMAX][NMAX]; //matriz raiz
int q[NMAX]; //buscas sem sucesso
int p[NMAX]; //frequencias

int NUMBER_OF_KEYS; //numero de chaves na árvore
int KEYS[NMAX];
OBST *ROOT;

void COMPUTE_W_C_R(){
	int x, min;
	int i, j, k, h, m;

	//construir matriz de peso W
	for(i = 0; i <= NUMBER_OF_KEYS; i++) {
		W[i][i] = q[i];
		for(j = i + 1; j <= NUMBER_OF_KEYS; j++)
			W[i][j] = W[i][j-1] + p[j] + q[j];
	}

	//construir matriz de custo C e matriz raiz R
	for(i = 0; i <= NUMBER_OF_KEYS; i++)
		C[i][i] = W[i][i];
	for(i = 0; i <= NUMBER_OF_KEYS - 1; i++) {
		j = i + 1;
		C[i][j] = C[i][i] + C[j][j] + W[i][j];
		R[i][j] = j;
	}
	for(h = 2; h <= NUMBER_OF_KEYS; h++)
		for(i = 0; i <= NUMBER_OF_KEYS - h; i++) {
			j = i + h;
			m = R[i][j-1];
			min = C[i][m-1] + C[m][j];
			for(k = m+1; k <= R[i+1][j]; k++){
				x = C[i][k-1] + C[k][j];
				if(x < min) {
					m = k;
					min = x;
				}
			}
			C[i][j] = W[i][j] + min;
			R[i][j] = m;
		}

	//Exibir matriz de peso W
	printf("\nMatriz de peso W:\n");
	for(i = 0; i <= NUMBER_OF_KEYS; i++){
		for(j = i; j <= NUMBER_OF_KEYS; j++)
			printf("%d ", W[i][j]);
		printf("\n");
	}
	

	//Exibir matriz de custo C
	printf("\nMatriz de custo C:\n");
	for(i = 0; i <= NUMBER_OF_KEYS; i++) {
		for(j = i; j <= NUMBER_OF_KEYS; j++)
			printf("%d ", C[i][j]);
		printf("\n");
	}

	//Exibir matriz raiz  R

	printf("\nMatriz raiz R:\n");
	for(i = 0; i <= NUMBER_OF_KEYS; i++) {
		for(j = i; j <= NUMBER_OF_KEYS; j++)
			printf("%d ", R[i][j]);
		printf("\n");
	}
}

//construit arvore de busca binaria otimizada
OBST *CONSTRUCT_OBST(int i, int j){
	OBST *p;

	if(i == j)
		p = NULL;
	else{
		p = (OBST*) calloc(1, sizeof(OBST));
		p->KEY = KEYS[R[i][j]];
		p->left = CONSTRUCT_OBST(i, R[i][j] - 1); //sub-arvore da esquerda
		p->right = CONSTRUCT_OBST(R[i][j], j); //sub-arvore da direita
	}
	return p;
}

//exibir arvore de busca binaria otima
void DISPLAY(OBST *ROOT, int nivel){
	int i;
	if(ROOT != 0) {
		DISPLAY(ROOT->right, nivel+1);
		for(i = 0; i <= nivel; i++)
			printf(" ");
		printf("%d\n", ROOT->KEY);
		DISPLAY(ROOT->left, nivel + 1);
	}
}
void OPTIMAL_BINARY_SEARCH_TREE()
{
	float average_cost_per_weight;

	COMPUTE_W_C_R();
	printf("C[0] = %d W[0] = %d\n", C[0][NUMBER_OF_KEYS], W[0][NUMBER_OF_KEYS]);
	average_cost_per_weight = C[0][NUMBER_OF_KEYS]/(float)W[0][NUMBER_OF_KEYS];
	printf("A relacao custo por peso e: %f\n", average_cost_per_weight);
	ROOT = CONSTRUCT_OBST(0, NUMBER_OF_KEYS);
}
int main(){
	int i, k;

	setbuf(stdout,NULL);
	printf("Numero de chaves: ");
	scanf("%d", &NUMBER_OF_KEYS);
	for(i = 1; i <= NUMBER_OF_KEYS; i++) {
		printf("chave[%d]= ",i);
		scanf("%d", &KEYS[i]);
		printf(" probabilidade = ");
		scanf("%d",&p[i]);
	}
	for(i = 0; i <= NUMBER_OF_KEYS; i++) {
		printf("q[%d] = ", i);

		scanf("%d",&q[i]);
	}
	do {
		printf("1.Construir arvore\n2.Mostrar arvore\n3.Sair\n");
		scanf("%d", &k);
		switch(k) {
		case 1:
			OPTIMAL_BINARY_SEARCH_TREE();
			break;
		case 2:
			DISPLAY(ROOT, 0);
			break;
		case 3:
			k = -1;
			break;
		}
	} while (k != -1);
}
