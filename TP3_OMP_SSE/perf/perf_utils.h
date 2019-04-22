#define VECSIZE 4096
#define NB_FOIS 100

#include <complexe.h>

typedef float vfloat[VECSIZE] __attribute__((aligned(32)));
typedef double vdouble[VECSIZE] __attribute__((aligned(32)));
typedef complexe_float_t vcomplex[VECSIZE] __attribute__((aligned(32)));
typedef complexe_double_t vcomplexd[VECSIZE] __attribute__((aligned(32)));

void vector_init(vfloat V, float x);
void vector_init_d(vdouble V, double x);
void vector_init_c(vcomplex V, complexe_float_t x);
void vector_init_z(vcomplexd V, complexe_double_t x);

void mat_init(vfloat V, float x);
void mat_init_d(vdouble V, double x);
void mat_init_c(vcomplex V, complexe_float_t x);
void mat_init_z(vcomplexd V, complexe_double_t x);

void vector_print(vfloat V);
