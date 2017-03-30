#include <stdio.h>
#include <stdlib.h>
#include "proj1.h"



int main(){

	while (1){

		char comando = getchar();

		switch (comando){

		case 'a':
			/* Adiciona um banco novo */
			adiciona();
			break;

		case 'k':
			/* Despromove um banco existente */
			classifica(1, -1);
			break;

		case 'r':
			/* Promove um banco existente */
			classifica(-1, -1);
			break;

		case 'e':
			/* Adiciona um emprestimo do primeiro banco para o segundo */
			transf(1);
			break;

		case 'p':
			/* Adiciona uma amortizacao do primeiro banco para o segundo */
			transf(-1);
			break;

		case 'l':
			/* Imprime listas organizadas */
			listas();
			break;

		case 'K':
			/* Despromove o banco com mais valor emprestado a bancos maus. */
			filtra();
			break;

		case 'x':
			/* Sai do programa. */
			end();
			return EXIT_SUCCESS;

		default:
			printf("ERRO: Comando desconhecido\n");
			break;

		}
		getchar();
	}
	return EXIT_FAILURE;
}
