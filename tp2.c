#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void permutation(char * tab, int * PMU, int N){
  char * tmp = (char*) malloc(sizeof(char)*N);
  for (int i = 0; i < N; ++i) {
    tmp [PMU[i]] = tab[i];
  }
  for (int i = 0; i < N; ++i) {
    tab[i] = tmp[i];
  }
  tab = tmp;
  free(tmp);
}


void Copy_File(FILE* f, FILE* fs,char *i,char *j)
{
	fclose(f);
	fclose(fs);
	f = fopen(i,"r");
	fs = fopen(j,"w+");
	if(f == NULL)
	{
		printf("Lecture Echouée");
		exit(1);
	}
	else
	{
		char c = (char)getc(f);
		while( c != EOF)
		{
			putc(c,fs);
			c=getc(f);
		}
		printf(" Lecture et Copyage\n");
	}
}

void Concatene_File(FILE* fe1, FILE* fe2,char *i,char * j)
{
	fclose(fe1);
	fclose(fe2);
	fe1 = fopen(i,"a");
	fe2 = fopen(j,"r");
	if(fe1 == NULL)
	{
		printf("Lecture Echouée");
		exit(1);
	}
	else
	{
		char c = ' ';
		putc(c,fe1);
		c = (char)getc(fe2);
		while( c != EOF)
		{
			putc(c,fe1);
			c=getc(fe2);
		}
		printf(" Lecture et Concatenage\n");
	}
	
}

void pas_voyelle(FILE* f,char* i)
{
	fclose(f);
	f = fopen(i,"r");
	if(f == NULL)
	{
		printf("Lecture Echouée");
		exit(1);
	}
	else
	{
		FILE* fichierSortie = fopen("voyelle.txt","w+");
		char c = (char)getc(f);
		while( c != EOF)
		{
			if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' ){
				c=getc(f);
			}
			else{
				putc(c,fichierSortie);
				c=getc(f);
			}
		}
		Copy_File(fichierSortie,f,"voyelle.txt",i);
		remove("voyelle.txt");
	}
}

void tab(FILE* f,char* i){
	int T[512];
	for (int i = 0; i<512; i++) T[i]=i;
	fclose(f);
	f = fopen(i,"w+");
	fwrite(T,sizeof(int),512,f);
	puts("copie du tableau effectué");
}

void code(FILE* f1, char* i, FILE* f2, char* j){
	int n = 3;
	int tab[100];
	char c = (char)getc(f2);
	int b = 0;
	while( c != EOF){
		if (c == ' ' || c == '(' || c == ')' || c == ','){
			c=getc(f2);
		}
		else{
			tab[b] = atoi(&c);
			b++;
			c=getc(f2);
		}
	}
	for (int i = 0 ; i < n ; i++){
		int a = tab[i];
		for (int j = 0 ; j< n ; j++){
			if  (a == tab[j] && j!=i){
				puts("permutation fausse");
				return;
			}
		}
	}
	FILE* fichierSortie = fopen("decalage.txt","w+");
	char* tabchar = (char*)malloc(sizeof(char)*n);
	c = getc(f1);
	int test = 1, seuil;
	while (c != EOF){
		for (int j = 0 ; j<n ; j++){
			tabchar[j] = c;
			c = getc(f1);
			if (c == EOF && j != n-1){	
				seuil = j;
				j = n;
				test = 0;
			}
		}
		if (test){	
			permutation(tabchar,tab,n);
			for (int k = 0 ; k<n ; k++)
				putc(tabchar[k],fichierSortie);
		}
		else{
			for (int i = 0 ; i <= seuil ; i++){
				c = tabchar[i];
				putc(c,fichierSortie);
			}
			c = EOF;
		}
	}
	Copy_File(fichierSortie,f1,"decalage.txt",i);
	remove("decalage.txt");
}



int main(int argc, char *argv[])
{
	char * i = argv[1];
	char * j = argv[2];

	FILE* f1 = fopen(i,"r");
	FILE* f2 = fopen(j,"r");

	// Concatene_File(f1,f2,i,j);

	// pas_voyelle(f1,i);

	// Copy_File(f1,f2,i,j);

	// tab(f1,i);

	code(f1,i,f2,j);

    fclose(f1);
	fclose(f2);


}