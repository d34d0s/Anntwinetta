#include <anntwinetta.h>

void main() {
    ATarray* arr = atMakeArray(3, 10);
    
    atInsertArrayV(arr, 3,
        (ATvalue*[]){
            atMakeInt(12321),
            atMakeFloat(420.69),
            atMakeString("Blazing B)")
        }
    );

    printf("Value : %d\n", atQueryArrayInt(arr, 0));
    printf("Value : %0.2f\n", atQueryArrayFloat(arr, 1));
    printf("Value : %s\n", atQueryArrayString(arr, 2));
    printf("Count : %d | Re-Size : %d\n", arr->max, arr->count);

    atDestroyArray(arr);
}
