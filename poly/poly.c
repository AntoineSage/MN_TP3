#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "poly.h"

#include <x86intrin.h>

p_polyf_t creer_polynome(int degre)
{
  p_polyf_t p;

  unsigned long long start, end;

  start = _rdtsc();

  p = (p_polyf_t)malloc(sizeof(polyf_t));
  p->degre = degre;

  p->coeff = (float *)malloc((degre + 1) * sizeof(float));

  end = _rdtsc();

  printf("creation polynome: %Ld cycles\n", end - start);

  return p;
}

p_polyf_t lire_polynome_float(char *nom_fichier)
{
  FILE *f;
  p_polyf_t p;
  int degre;
  int i;

  unsigned long long start, end;

  start = _rdtsc();

  f = fopen(nom_fichier, "r");
  if (f == NULL)
  {
    fprintf(f, "erreur ouverture %s \n", nom_fichier);
    exit(-1);
  }

  fscanf(f, "%d", &degre);

  p = creer_polynome(degre);

  for (i = 0; i <= degre; i++)
  {
    fscanf(f, "%f", &p->coeff[i]);
  }

  fclose(f);

  end = _rdtsc();

  printf("lire polynome:  %Ld cycles\n", end - start);

  return p;
}

void ecrire_polynome_float(p_polyf_t p)
{
  int i;

  printf("%f + %f x ", p->coeff[0], p->coeff[1]);

  for (i = 2; i <= p->degre; i++)
  {
    printf("+ %f X^%d ", p->coeff[i], i);
  }

  printf("\n");

  return;
}

int egalite_polynome(p_polyf_t p1, p_polyf_t p2)
{
  if (p1->degre != p2->degre)
    return 0;

  unsigned register int i;
  for (i = 0; i < p1->degre; i++)
  {
    if (p1->coeff[i] != p2->coeff[i])
      return 0;
  }

  return 1;
}

p_polyf_t addition_polynome(p_polyf_t p1, p_polyf_t p2)
{
  p_polyf_t grand_poly = (p1->degre > p2->degre) ? p1 : p2;
  p_polyf_t petit_poly = (grand_poly == p1) ? p2 : p1;

  p_polyf_t res = creer_polynome(grand_poly->degre);

  register unsigned int i;

  for (i = 0; i < petit_poly->degre; i++)
  {
    res->coeff[i] = petit_poly->coeff[i] + grand_poly->coeff[i];
  }

  for (i = petit_poly->degre; i < grand_poly->degre; i++)
  {
    res->coeff[i] = grand_poly->coeff[i];
  }

  return res;
}

p_polyf_t multiplication_polynome_scalaire(p_polyf_t p, float alpha)
{
  /* alpha * p1 */

  return NULL;
}

float eval_polynome(p_polyf_t p, float x)
{
  float res = 0.0;

  unsigned register int i;
  for (i = 0; i < p->degre; i++)
  {
    res += p->coeff[i] * pow(x, i);
  }
  return res;
}

p_polyf_t multiplication_polynomes(p_polyf_t p1, p_polyf_t p2)
{
  /* p1 * p2 */

  return NULL;
}

p_polyf_t puissance_polynome(p_polyf_t p, int n)
{
  p_polyf_t res = creer_polynome(p->degre * n);

  unsigned register int i;

  return NULL;
}

p_polyf_t composition_polynome(p_polyf_t p, p_polyf_t q)
{
  /*
    p O q
  */

  return NULL;
}
