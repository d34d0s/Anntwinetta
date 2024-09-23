#include "../../../engine/include/lotus.h"

typedef struct d_array {
    int c;
    void* arr;
} d_array;

typedef enum comps {
    transform_comp=0b0,
    material_comp=0b10,
    n_comps
} comps;

void main() {
    lotus_init();

    entity_t e = {0, 0};
    printf("entity struct size = %d\n", sizeof(e));

    set_comp(&e, transform_comp);
    set_comp(&e, material_comp);

    printf("has transform %d\n", has_comp(&e, transform_comp));

    rem_comp(&e, transform_comp);

    printf("has transform %d\n", has_comp(&e, transform_comp));

    lotus_exit();
}

