#define VECSIZE 4096
#define NB_FOIS 200

#include <complexe.h>

typedef float vfloat[VECSIZE];
typedef double vdouble[VECSIZE];
typedef complexe_float_t vcomplex[VECSIZE];
typedef complexe_double_t vcomplexd[VECSIZE];

void vector_init(vfloat V, float x);
void vector_init_d(vdouble V, double x);
void vector_init_c(vcomplex V, complexe_float_t x);
void vector_init_z(vcomplexd V, complexe_double_t x);

void mat_init(vfloat V, float x);
void mat_init_d(vdouble V, double x);
void mat_init_c(vcomplex V, complexe_float_t x);
void mat_init_z(vcomplexd V, complexe_double_t x);

void vector_print(vfloat V);
