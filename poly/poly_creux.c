#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "poly_creux.h"

#include <x86intrin.h>

p_polycreux_t creer_polynome()
{
  p_polycreux_t p;

  //unsigned long long start, end;

  //start = _rdtsc();

  p = (p_polycreux_t)malloc(sizeof(polycreux_t));
	p->nelem=0;
	//DEFINITION MEMOIRE DU POLYNOME A TRAVAILLER

  //end = _rdtsc();

  //printf("creation polynome: %Ld cycles\n", end - start);

  return p;
}


void ajouter_paire(p_polycreux_t p, int degre, int coeff){
	
	paire duo;
	int i=0;
	int j;
	duo.degre=degre;
	duo.coeff=coeff;
	//Placement de la paire de sorte que le tableau de paire soit trié par degré croissant
	while (p->tab_paires[i].degre<degre){
		i++;
	}
	//decalage des paires pour inserer la nouvelle paire
	for (j=p->nelem-1;j>=i;j--){
		p->tab_paires[j+1]=p->tab_paires[j];
	}
	//Insertion de la nouvelle paire
	p->tab_paires[i]=duo;
	p->nelem++;

}

p_polycreux_t lire_polynome_float(char *nom_fichier)
{
  FILE *f;
  p_polycreux_t p;
  int degre;
  int i;
	float coeff;

  unsigned long long start, end;

  start = _rdtsc();

  f = fopen(nom_fichier, "r");
  if (f == NULL)
  {
    fprintf(f, "erreur ouverture %s \n", nom_fichier);
    exit(-1);
  }

  fscanf(f, "%d", &degre);
  p = creer_polynome();
  for (i = 0; i <= degre; i++)
  {
    fscanf(f, "%f",&coeff);
		if (coeff!=0.0){
			ajouter_paire(p, i, coeff);
		}
  }

  fclose(f);

  end = _rdtsc();

  printf("lire polynome:  %Ld cycles\n", end - start);

  return p;
}

void ecrire_polynome_float(p_polycreux_t p)
{
  int i;

	if (p->tab_paires[0].degre==0){
		  printf("%f",p->tab_paires[0].coeff);
	}
	else if (p->tab_paires[0].degre==1){
		  printf("%f X",p->tab_paires[0].coeff);
	}
	if (p->tab_paires[1].degre==1){
		  printf("+ %f X",p->tab_paires[1].coeff);
	}
  for (i = 2; i <= p->nelem; i++)
  {
    printf("+ %f X^%d ",p->tab_paires[1].coeff, p->tab_paires[1].degre);
  }

  printf("\n");

  return;
}


