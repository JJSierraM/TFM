#include <stdio.h>

typedef struct Vector3Size_t
{
    size_t x;
    size_t y;
    size_t z;
} Vector3Size_t;

inline Vector3Size_t Vector3Size_tAdd (Vector3Size_t a, Vector3Size_t b) {
    return (Vector3Size_t) {a.x+b.x, a.y+b.y, a.z+b.z};
}

inline Vector3Size_t NextCombination (Vector3Size_t *prev_combination) {
    if (prev_combination->z+1 < prev_combination->y) {
        *prev_combination = Vector3Size_tAdd(*prev_combination, (Vector3Size_t) {0, 0, 1});
    }
    else if (prev_combination->y+1 < prev_combination->x) {
        *prev_combination = Vector3Size_tAdd(*prev_combination, (Vector3Size_t) {0, 1, -prev_combination->z});
    }
    else {
        *prev_combination = Vector3Size_tAdd(*prev_combination, (Vector3Size_t) {1, 1-prev_combination->y, -prev_combination->z});
    }
    return *prev_combination;
}

int main(int argc, char* argv[]) {
    Vector3Size_t combination = (Vector3Size_t) {2, 1, 0};

    for (int i=0; i<1000000000; i++)
        NextCombination(&combination);

    printf("(%lu, %lu, %lu)\n", combination.x, combination.y, combination.z);

    return 0;
}
