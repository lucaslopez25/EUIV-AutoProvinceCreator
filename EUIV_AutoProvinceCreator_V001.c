#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

Auto Province Creator
By Lucas Vinicius

*/

float vers = 1.01;

typedef struct prv
{
	char culture[100];
	char religion[100];
	char capital[100];
	char hre[5];
	char trade_goods[100];
	int base_manpower;
	int base_tax;
	int base_production;
	int native_size;
	int native_ferocity;
	int native_hostileness;
} province;

void Redundancia (char endereco[], char prov_numero[], char prov_nome[], char adr_arq[]) {

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
    province novaProv;
    Redundancia(local, prov_numero, prov_nome, adr_arq);

	if ((arquivo = fopen (local , "w")) == NULL) {
		printf ("\nERROR - PROVINCE COULD NOT BE CREATED \n");
		exit (-1);
	}

	if ((arquivobaseprov = fopen ("origem\\baseprov.txt", "r")) == NULL) { //leitura
		printf ("ERROR - ARCHIVE baseprov DOES NOT EXIST\n");
		exit (-2);
	}

	strcpy(novaProv.capital, prov_nome);
	fscanf (arquivobaseprov, "culture = %s", novaProv.culture);
	fscanf (arquivobaseprov, "religion = %s", novaProv.religion);
	fscanf (arquivobaseprov, "hre = %s", novaProv.hre);
	fscanf (arquivobaseprov, "trade_goods = %s", novaProv.trade_goods);
	fscanf (arquivobaseprov, "base_manpower = %i", &novaProv.base_manpower);
	fscanf (arquivobaseprov, "base_tax = %i", &novaProv.base_tax);
	fscanf (arquivobaseprov, "base_production = %i", &novaProv.base_production);
	fscanf (arquivobaseprov, "native_size = %i", &novaProv.native_size);
	fscanf (arquivobaseprov, "native_ferocity = %i", &novaProv.native_ferocity);
	fscanf (arquivobaseprov, "native_hostileness = %i", &novaProv.native_hostileness);

	fprintf(arquivo, "culture = %s", novaProv.culture);
	fprintf(arquivo, "religion = %s", novaProv.religion);
	fprintf(arquivo, "capital = \"%s\"", novaProv.capital);
	fprintf(arquivo, "hre = %s", novaProv.hre);
	fprintf(arquivo, "trade_goods = %s", novaProv.trade_goods);
	fprintf(arquivo, "base_manpower = %i", novaProv.base_manpower);
	fprintf(arquivo, "base_tax = %i", novaProv.base_tax);
	fprintf(arquivo, "base_production = %i", novaProv.base_production);
	fprintf(arquivo, "native_size = %i", novaProv.native_size);
	fprintf(arquivo, "native_ferocity = %i", novaProv.native_ferocity);
	fprintf(arquivo, "native_hostileness = %i", novaProv.native_hostileness);

	printf("\nSucess, Province Created!\n");

	fclose (arquivo);
	fclose (arquivobaseprov);
}

int ProvInicioProg () {
	int i;
	printf("Please, type in the provnumber of START in the file newProvinces.csv ...:");
	scanf ("%i", &i);
	printf("\n");

	return i;
}

int ProvFimProg () {
	int i;
	printf("Please, type in the provnumber of END in the file newProvinces.csv ...:");
	scanf ("%i", &i);
	printf("\n");

	return i;
}

void Greeting () {
	printf("Welcome to Auto Province Creator\n");
	printf("This Program is intended to auto create provinces. It's version is: %f\n", vers);
	printf("\n\n");
	printf("********************************\n");
	printf("\n\n");
}

int main () {

	FILE *arquivoprovincias;

	char adr_arq [] = "destino";

	int provNum, provInicio, provFim;

	Greeting ();

	provInicio = ProvInicioProg ();
	provFim = ProvFimProg ();

	if ((arquivoprovincias = fopen ("origem\\newProvinces.csv", "r")) == NULL) { //leitura
		printf ("ERROR - ARCHIVE newProvinces DOES NOT EXIST\n");
		exit (-3);
	}

	for (provNum = provInicio; provNum <= provFim; provNum++)
	{
		char prov_numero[4],prov_nome[100];
		int cr,cg,cb;
		fscanf (arquivoprovincias, "%s;%i;%i;%i;%s;x", prov_numero, &cr, &cg, &cb, prov_nome);

		ProvinceCreator (prov_numero, prov_nome, adr_arq);
	}


	fclose (arquivoprovincias);
	return 0;
}
