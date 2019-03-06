#include <assert.h>
#include <mnblas.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
	printf("TEST DES FONCTIONS BLAS1 ASUM :\n");

	float a[5] = {1.0, 2.0, -3.0, 7.0,5.0};

	float res=mncblas_sasum (5, a, 1);

    assert(res==18.0);

	printf("OK REEL\n");

    float b[5] = {1.0, 4.0, 0.0, 3.0, -2.0};

	complexe_double_t *c;

    init_complexe_float(n, a, b, c);

	res=mncblas_scasum(5, c, 1);

	assert(res==28);

}