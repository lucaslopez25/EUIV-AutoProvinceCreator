#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

Auto Province Creator
By Lucas Vinicius

*/

float vers = 1.4;

void Redundancia (char endereco[], char prov_numero[], char prov_nome[], char adr_arq[]) {
	strcpy(endereco, "");
	
	strcat (endereco, adr_arq);
    strcat (endereco, "\\");
    strcat (endereco, prov_numero);
    strcat (endereco, " - ");
    strcat (endereco, prov_nome);
    strcat (endereco,".txt");
}

void ProvinceCreator (char prov_numero[], char prov_nome[], char adr_arq[]) {
	FILE *arquivo;
	FILE *arquivobaseprov;
	int s1 = strlen(prov_numero); int s2 = strlen(prov_nome); int s3 = strlen(adr_arq);
	int tamanho = s1 + s2 + s3 + 10;
    char local[tamanho];
    char temporario[100], temp2[100];
    char c;
    
    Redundancia(local, prov_numero, prov_nome, adr_arq);
	puts (local);
	if ((arquivo = fopen (local , "w+")) == NULL) {
		printf ("\nERROR - PROVINCE COULD NOT BE CREATED \n");
		exit (-1);
	}

	if ((arquivobaseprov = fopen ("origem\\baseprov.txt", "r")) == NULL) { //leitura
		printf ("ERROR - ARCHIVE baseprov DOES NOT EXIST\n");
		exit (-2);
	}

	sprintf (temp2, "capital = \"%s\"\n", prov_nome);
	fputs (temp2, arquivo);

	while (fgets (temporario, 100, arquivobaseprov) != NULL) {
		fputs (temporario, arquivo);
   }

	printf("\nSucess, Province Created!\n");

	fclose (arquivo);
	fclose (arquivobaseprov);
}

void Greeting () {
	printf("Welcome to Auto Province Creator\n");
	printf("This Program is intended to automatize certain routines of the province creation process.\nCurrent version: %.4f\n", vers);
	printf("\n\n");
	printf("********************************\n");
	printf("\n\n");
}

int main () {

	FILE *arquivoprovincias;
	FILE *arquivolistprovincias;
	FILE *arquivo_localisation;
	FILE *arquivo_localisation_adj;

	char adr_arq [] = "destino";

	Greeting ();

	if ((arquivoprovincias = fopen ("origem\\newProvinces.csv", "r")) == NULL) { //leitura
		printf ("ERROR - ARCHIVE newProvinces DOES NOT EXIST\n");
		exit (-3);
	}

	if ((arquivolistprovincias = fopen ("list_of_provinces.txt", "a")) == NULL) { //apendice
		printf ("ERROR - ARCHIVE list_of_provinces NOT CREATED\n");
		exit (-4);
	}

	if ((arquivo_localisation = fopen ("localisations.txt", "a")) == NULL) { //apendice
		printf ("ERROR - ARCHIVE localisations NOT CREATED\n");
		exit (-5);
	}

	if ((arquivo_localisation_adj = fopen ("localisations_adj.txt", "a")) == NULL) { //apendice
		printf ("ERROR - ARCHIVE localisations_adj NOT CREATED\n");
		exit (-5);
	}
	
	int carac, iCont = 0, jCont;
	
	do {
		carac = fgetc (arquivoprovincias);
		if (carac == '\n') {
			iCont++;
		}
	} while (carac != EOF);
	
	rewind (arquivoprovincias);

	for (jCont = 0; jCont <= iCont; jCont++)
	{
		char prov_numero[4],prov_nome[100];
		int cr,cg,cb;
		fscanf (arquivoprovincias, "%[^;];%i;%i;%i;%[^;];x\n", prov_numero, &cr, &cg, &cb, prov_nome);
		
		if (jCont == 0) {
			printf ("Province of Start: %s\n", prov_numero);
		}

		ProvinceCreator (prov_numero, prov_nome, adr_arq);

		fprintf(arquivolistprovincias, "%s ", prov_numero);
		printf("Province %s added to list_of_provinces.txt\n", prov_numero);
		fprintf(arquivo_localisation, " PROV%s:0 \"%s\"\n", prov_numero, prov_nome);
		fprintf(arquivo_localisation_adj, " PROV_ADJ%s:0 \"%san\"\n", prov_numero, prov_nome);
		printf("Province %s added to localisations.txt and localisations_adj.txt\n", prov_numero);
		printf("\n\n");
		
		if (jCont == iCont) {
			printf ("Province of End: %s\n", prov_numero);
		}
	}

	fprintf(arquivolistprovincias, "\n");
	printf("\n\n");
	
	fclose (arquivoprovincias);
	fclose (arquivo_localisation);
	fclose (arquivo_localisation_adj);
	fclose (arquivolistprovincias);
	
	system("pause");
	return 0;
}
