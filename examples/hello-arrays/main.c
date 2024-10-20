#include <anntwinetta.h>

void main() {
    ATarray* arr = atMakeArray(3, 10);
    AThashmap* hmap = atMakeHashmap(16);

    atSetHashmap(hmap, "age", atMakeInt(22));

    atInsertArrayV(arr, 4,
        (ATvalue*[]){
            atMakeInt(12321),
            atMakeFloat(420.69),
            atMakeString("Blazing B)"),
            atMakeValue(TYPE_HASHMAP, hmap)
        }
    );
    
    AThashmap* vmap = (AThashmap*)((ATvalue*)atQueryArray(arr, 3)->value);
    ATvalue* vkvp = (ATvalue*)atGetHashmap(vmap, "age");
    
    int age = *(int*)vkvp->value;
    printf("Value : %d\n", atQueryArrayInt(arr, 0));
    printf("Value : %0.2f\n", atQueryArrayFloat(arr, 1));
    printf("Value : %s\n", atQueryArrayString(arr, 2));
    printf("Count : %d | Re-Size : %d\n", arr->max, arr->count);
    printf("Age : %d\n", age);

    atDestroyArray(arr);
}
