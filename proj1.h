#include <stdio.h>

typedef struct {

	/* Estrutura banco */

	char nome[42];
	short int classificacao,inP, outP, parceiros;
	unsigned int referencia, outV, outVM, inV, inVM;

}banco;


banco bancos[1000];  /* Vector que guarda os bancos */
int rede[1000][1000];  /* Matriz que guarda o valor dos emprestimos da rede de bancos */
short int total_bancos;  /* Inteiro que guarda o nº de bancos no sistema. Utilizado para percorrer o vector bancos ate ao ultimo inserido. */




int indice (int ref){

	/* Indice(ref) devolve o indice do banco cuja referencia e ref */
	short int i;
	for (i = 0; i < total_bancos; i++)
		if (bancos[i].referencia == ref)
			return i;
	return -1;
}


void adiciona(){

	/* Adiciona um banco novo */
	scanf("%s %hd %u", bancos[total_bancos].nome, &bancos[total_bancos].classificacao, &bancos[total_bancos].referencia);
	total_bancos++;
}


void classifica(int n, int ref){

	/* Despromove (input1 = 1) ou promove (input1 = -1) um banco existente, o segundo input recebe a referencia do 
	   banco a alterar (se for um numero negativo faz scan em vez disso)*/
	short int i;

	if (ref < 0){
		scanf("%d", &ref);
		ref = indice(ref);
	}
	if (ref == -1){
		puts("A referencia e invalida.\n Por favor introduza o comando novamente com uma referencia valida.");
		return;
	}
	if (bancos[ref].classificacao == (n < 0))
		return;
	bancos[ref].classificacao = (n < 0);
	for (i = 0; i < total_bancos; i++){
		bancos[i].inVM += (n * rede[ref][i]);
		bancos[i].outVM += (n * rede[i][ref]);
	}
}


void transf(short int n){

	/* Adiciona um emprestimo (input = 1) ou uma amortizacao (input = -1) a rede de bancos */
	int r;
	unsigned int ref1, ref2, valor;

	scanf("%u %u %u", &ref1, &ref2, &valor);
	ref1 = indice(ref1), ref2 = indice(ref2);
	if (ref1 == ref2 || ( ref1 == -1 || ref2 == -1)){
		puts("As referencias sao invalidas ou iguais.\n Por favor introduza o comando novamente com referencias validas.\n");
		return;
	}
	if (n < 0){
		int t;
		t = ref1;
		ref1 = ref2, ref2 = t;
	}
	if (n < 0)
		while (valor > rede[ref1][ref2]){
			puts("O valor da amortizacao e superior ao do emprestimo.\nPor favor introduza o comando novamente com um valor valido.\n");
			return;
		}

	r = n * valor;
	rede[ref1][ref2] += r;
	bancos[ref1].outV += r;
	bancos[ref2].inV += r;

	if (bancos[ref1].classificacao == 0)
		bancos[ref2].inVM += r;
	if (bancos[ref2].classificacao == 0)
		bancos[ref1].outVM += r;

	if (rede[ref1][ref2] == (n > 0) * valor){
		bancos[ref1].outP += n;
		bancos[ref2].inP += n;
		if (rede[ref2][ref1] == 0){
			bancos[ref1].parceiros += n;
			bancos[ref2].parceiros += n;
		}
	}
}


void listas(){

	short int tipo, i, j;

	scanf("%hd", &tipo);

	if (tipo == 0){
		/* Imprime uma lista simples com a referencia, nome e classificacao de cada banco do sistema */
		for (i = 0; i < total_bancos; i++)
			printf("%d %s %hd\n", bancos[i].referencia, bancos[i].nome, bancos[i].classificacao);
	}
	if (tipo == 1){
		/* Imprime uma lista com mais informacao sobre cada banco*/
		for (i = 0; i < total_bancos; i++)
			printf("%u %s %hd %hd %hd %u %u %u %u\n", bancos[i].referencia, bancos[i].nome, bancos[i].classificacao, bancos[i].inP,
				bancos[i].outP, bancos[i].outV, bancos[i].outVM, bancos[i].inV, bancos[i].inVM);
	}
	if (tipo == 2){
		/* Imprime uma lista que mostra quantos bancos existem com x parceiros*/
		int b[1000] = {0};

		for (i = 0; i < total_bancos; i++)
			b[bancos[i].parceiros]++;
		for (j = 0; j < total_bancos; j++)
			if (b[j] != 0)
				printf("%hd %hd\n", j, b[j]);
	}
}



void end(){

	/* Devolve o numero total de bancos e o numero de bancos bons registados*/
	short int i, j = 0;
	for (i = 0; i < total_bancos; i++)
		if (bancos[i].classificacao == 1)
			j++;
	printf("%hd %hd\n", total_bancos, j);
}


void filtra(){

	/* Procura e despromove o banco bom com maior valor emprestado a bancos maus */
	int v = 0;
	short int n = -1, i;
	for (i = 0; i < total_bancos; i++){
		if (bancos[i].classificacao == 1 && bancos[i].outVM >= v){
			v = bancos[i].outVM;
			n = i;
		}
	}
	if (v > 0){
		classifica(1, n);
		printf("*%u %s %hd %hd %hd %u %u %u %u\n", bancos[n].referencia, bancos[n].nome, bancos[n].classificacao, bancos[n].inP,
			bancos[n].outP, bancos[n].outV, bancos[n].outVM, bancos[n].inV, bancos[n].inVM);
	}
	end();
}
