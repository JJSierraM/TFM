#include "Triangulate.h"

extern size_t nCr (size_t n, size_t r) ;

//Return 1.0 if a,b,c are in right hand pattern, -1.0 if otherwise
extern float RightHand (Vector2 a, Vector2 b, Vector2 c) ;

//Checks if point p is inside circle described by points a, b and c
extern int PointInCircle (Vector2 a, Vector2 b, Vector2 c, Vector2 p) ;

extern Vector3Size_t NextCombination (Vector3Size_t *prev_combination) ;

ArraySize_t Triangulation2D (Vector2 *points, size_t n_points) {
    Vector3Size_t combination = (Vector3Size_t) {2, 1, 0};
    LinkedListVector3Size_t indices = LinkedListVector3Size_tNew();
    Vector2 a, b, c, d;
    size_t ok;
    for (size_t i = 0; i < nCr(n_points, 3); i++) {
        a = points[combination.x];
        b = points[combination.y];
        c = points[combination.z];
        ok = 1;
        //                                                            !This is only true if any of them is NaN! (Good, we have to continue if is so)
        if (Vector2CrossProduct(Vector2Sub(b,a),Vector2Sub(c,a))==0 || (a.x + b.x + c.x != a.x + b.x + c.x)) {
            combination = NextCombination(&combination);
            continue;
        }
        for (size_t j = 0; j < n_points; j++) {
            if (j==combination.x || j==combination.y || j==combination.z)
                continue;
            d = points[j];
            if (PointInCircle(a, b, c, d)) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            LinkedListVector3Size_tAppend(&indices, combination);
        }
        combination = NextCombination(&combination);
    }
    return LinkedListVector3Size_tToArrayAndFree(&indices);
}

ArraySize_t Triangulation2DParallel (Vector2 *points, size_t n_points) {
    Vector3Size_t combination = (Vector3Size_t) {1, 0, 0}, my_combination;
    LinkedListVector3Size_t indices = LinkedListVector3Size_tNew();
    Vector2 a, b, c, d;
    size_t ok, i;

    #pragma omp parallel
    #pragma omp taskloop private(i,a,b,c,d,ok,my_combination) shared(combination, indices) 
    for (i = 0; i < nCr(n_points, 3); i++) {
        #pragma omp critical
        my_combination = NextCombination(&combination);
        a = points[my_combination.x];
        b = points[my_combination.y];
        c = points[my_combination.z];
        ok = 1;
        //                                                            !This is only true if any of them is NaN! (Good, we have to continue if is so)
        if (!(Vector2CrossProduct(Vector2Sub(b,a),Vector2Sub(c,a))==0 || (a.x + b.x + c.x != a.x + b.x + c.x))) {
            for (size_t j = 0; j < n_points; j++) {
                if (j==my_combination.x || j==my_combination.y || j==my_combination.z)
                    continue;
                d = points[j];
                if (PointInCircle(a, b, c, d)) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                #pragma omp critical
                LinkedListVector3Size_tAppend(&indices, my_combination);
            }
        }
    }
    return LinkedListVector3Size_tToArrayAndFree(&indices);
}

ArraySize_t GetRimPoints (Vector2 *points, size_t n_points, ArraySize_t *indices) {
    size_t n_tris = indices->size / 3;
    float *angles = (float*) calloc(n_points, sizeof(float));
    // size_t *HITS = (size_t*) calloc(n_points, sizeof(size_t)); //DEBUGGING
    int prev, next;
    Vector2 ab, ac;
    float angle;

    for (size_t i = 0; i < n_tris; i++) {
        for (size_t j = 0; j < 3; j++) {
            prev = j-1;
            prev += 3 * (prev < 0);
            next = (j+1) % 3;
            ab = Vector2Sub(points[indices->array[3*i + prev]], points[indices->array[3*i + j]]);
            ac = Vector2Sub(points[indices->array[3*i + next]], points[indices->array[3*i + j]]);
            angle = fabsf(Vector2Angle(ac) - Vector2Angle(ab));
            angle += 2*(PI-angle) * (angle > PI);
            angles[indices->array[3*i + j]] += angle;
            // HITS[indices->array[3*i + j]] ++;
        }
    }
    LinkedListSize_t rim_points = LinkedListSize_tNew();
    ///////////// DEBUGGING!!
    // printf("Points and their angles:\n");/////
    for (size_t i = 0; i < n_points; i++) {
        // printf("Point %3u: %4.3f\n",i,angles[i]);/////
        if (angles[i] < 2*PI-0.05) {
            LinkedListSize_tAppend(&rim_points, i);
        }
    }
    // printf("Points and their triangles:\n");/////
    // for (size_t i = 0; i < n_points; i++) {/////
        // printf("Point %3u: %3u\n",i,HITS[i]);/////
    // }
    /////////////
    free(angles);
    return LinkedListSize_tToArrayAndFree(&rim_points);
}

ArraySize_t convert_indices(ArraySize_t *indices, ArraySize_t *conversion) {
    LinkedListSize_t converted = LinkedListSize_tNew();
    for (size_t i = 0; i < indices->size; i++) {
        LinkedListSize_tAppend(&converted, conversion->array[indices->array[i]]);
    }
    return LinkedListSize_tToArrayAndFree(&converted);
}

ArraySize_t SphereTriangulate (Vector3 *points, size_t n_points) {
    Vector2 *points_stero = SterographicProjectArray(points, n_points);
    ArraySize_t indices = Triangulation2DParallel(points_stero, n_points);
    
    ArraySize_t final_points_indices = GetRimPoints(points_stero, n_points, &indices);
    if (final_points_indices.size > 0) {
        Vector3 *final_points = malloc(final_points_indices.size * sizeof(Vector3));
        for (size_t i = 0; i < final_points_indices.size; i++) {
            final_points[i] = points[final_points_indices.array[i]];
        }
        Vector2 *final_points_stero = SterographicProjectInvertedArray(final_points, final_points_indices.size);
        ArraySize_t final_indices_pre = Triangulation2DParallel(final_points_stero, final_points_indices.size);
        ArraySize_t final_indices = convert_indices(&final_indices_pre, &final_points_indices);
        indices = ArraySize_tAppendArrays(&indices, &final_indices);
        free(final_points);
        free(final_points_stero);
        ArraySize_tFree(&final_indices_pre);
        ArraySize_tFree(&final_indices);
    }
    free(points_stero);
    ArraySize_tFree(&final_points_indices);
    return indices;
}
