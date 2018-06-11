#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

struct dados{
	int linha;
	int palavras;
	int caracteres;
};

int wc (FILE *, struct dados*, int);
int wcImprime (struct dados*, int);

int main (int argc, char *argv []){
	
	int totLinha = 0;
	int totPalavras = 0;
	int totCaracteres = 0;

	FILE *arq;
	int i;
	struct dados *n;

	if (argc > 1){

		n = malloc ((argc-1) * sizeof (struct dados));
		if (!n){
			printf ("Retornou %d : %s\n", errno, strerror(errno));
			return errno;
		}

		for (i = 1; i < argc; i ++){
		
			arq = fopen (argv[i], "rb");
		
			if (!arq){
				printf ("\nRetornou %d : %s\n", errno, strerror(errno));
				continue;
				//return errno;
			}

			wc (arq, n, (i-1));
			wcImprime (n, (i-1));

			if (argc > 2){
				totLinha += n[i-1].linha;
				totPalavras += n[i-1].palavras;
				totCaracteres += n[i-1].caracteres;
			}
		}
		if (argc > 2){
			printf ("\n\nTOTAL Palavras = %d  |  TOTAL Linhas = %d  |  TOTAL Caracteres = %d\n", totPalavras, totLinha, totCaracteres);
		}
	}
}

int wc (FILE *arq, struct dados *n, int indiceArq){
	
	int i;
	char letra;
	
	n[indiceArq].palavras = 0;
	n[indiceArq].linha = 0;
	n[indiceArq].caracteres = 0;
	
	for (i = 0; !feof(arq); i ++){
		letra = fgetc (arq);
		if (letra == ' '){
			n[indiceArq].palavras ++;
		}if (letra == '\n'){
			n[indiceArq].palavras ++;
			n[indiceArq].linha ++;
		}if (letra){
			n[indiceArq].caracteres ++;
		}
	} 
	n[indiceArq].palavras ++;
	n[indiceArq].linha ++;
	n[indiceArq].caracteres --;
	
	return 0;

}

int wcImprime (struct dados *n, int indiceArq){

	int i;

	printf ("\nPalavras = %d  |  Linhas = %d  |  Caracteres = %d\n", n[indiceArq].palavras, n[indiceArq].linha, n[indiceArq].caracteres);

	return 0;
}
