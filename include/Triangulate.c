#include "Triangulate.h"

extern size_t nCr (size_t n, size_t r) ;

//Return 1.0 if a,b,c are in right hand pattern, -1.0 if otherwise
extern float RightHand (Vector2 a, Vector2 b, Vector2 c) ;

//Checks if point p is inside circle described by points a, b and c
extern int PointInCircle (Vector2 a, Vector2 b, Vector2 c, Vector2 p) ;

extern Vector3Size_t NextCombination (Vector3Size_t *prev_combination) ;

ArraySize_t Triangulation2D (ArrayVector2 *working_points, ArrayVector2 *testing_points, ArraySize_t *working_indices) {
    Vector3Size_t combination = (Vector3Size_t) {2, 1, 0};
    LinkedListVector3Size_t indices = LinkedListVector3Size_tNew();
    Vector2 a, b, c, d;
    size_t ok;
    for (size_t i = 0; i < nCr(working_points->size, 3); i++) {
        a = working_points->array[combination.x];
        b = working_points->array[combination.y];
        c = working_points->array[combination.z];
        ok = 1;
        //                                                            !This is only true if any of them is NaN! (Good, we have to continue if is so)
        if (Vector2CrossProduct(Vector2Sub(b,a),Vector2Sub(c,a))==0 || (a.x + b.x + c.x != a.x + b.x + c.x)) {
            combination = NextCombination(&combination);
            continue;
        }
        for (size_t j = 0; j < testing_points->size; j++) {
            d = testing_points->array[j];
            if (PointInCircle(a, b, c, d)) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            LinkedListVector3Size_tAppend(&indices, (Vector3Size_t) {working_indices->array[combination.x], working_indices->array[combination.y], working_indices->array[combination.z]});
        }
        combination = NextCombination(&combination);
    }
    return LinkedListVector3Size_tToArrayAndFree(&indices);
}

ArraySize_t Triangulation2DParallel (ArrayVector2 *working_points, ArrayVector2 *testing_points, ArraySize_t *working_indices) {
    Vector3Size_t combination = (Vector3Size_t) {2, 1, 0};
    LinkedListVector3Size_t indices = LinkedListVector3Size_tNew();
    Vector2 a, b, c, d;
    size_t ok;

    #pragma omp parallel private(a,b,c,d,ok) firstprivate(combination) shared(indices, working_points, testing_points, working_indices) 
    {
        size_t  current_item = 0, 
                my_id = omp_get_thread_num(), 
                n_proc = omp_get_num_threads();
        for (size_t i = 0; i < my_id; i++) {
            combination = NextCombination(&combination);
        }
        current_item += my_id;

        while (current_item < nCr(working_points->size, 3)) {
            a = working_points->array[combination.x];
            b = working_points->array[combination.y];
            c = working_points->array[combination.z];
            ok = 1;
            //                                                            !This is only true if any of them is NaN! (Good, we have to continue if is so)
            if (Vector2CrossProduct(Vector2Sub(b,a),Vector2Sub(c,a))==0 || (a.x + b.x + c.x != a.x + b.x + c.x)) {
                for (size_t i = 0; i < n_proc; i++) {
                    combination = NextCombination(&combination);
                }
                current_item += n_proc;
                continue;
            }
            for (size_t j = 0; j < testing_points->size; j++) {
                d = testing_points->array[j];
                if (PointInCircle(a, b, c, d)) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                #pragma omp critical
                LinkedListVector3Size_tAppend(&indices, (Vector3Size_t) {working_indices->array[combination.x], working_indices->array[combination.y], working_indices->array[combination.z]});
            }
            for (size_t i = 0; i < n_proc; i++) {
                combination = NextCombination(&combination);
            }
            current_item += n_proc;
        }
    }
    return LinkedListVector3Size_tToArrayAndFree(&indices);
}

ArraySize_t GetRimPoints (ArrayVector2 *testing_points, ArraySize_t *indices, ArraySize_t* global_to_testing_indices, ArraySize_t *testing_to_global_indices) {
    size_t n_tris = indices->size / 3;
    float *angles = (float*) calloc(testing_points->size, sizeof(float));
    int prev, next;
    Vector2 ab, ac;
    float angle;

    #pragma omp parallel for private(prev, next, ab, ac, angle)
    for (size_t i = 0; i < n_tris; i++) {
        for (size_t j = 0; j < 3; j++) {
            prev = j-1;
            prev += 3 * (prev < 0);
            next = (j+1) % 3;
            ab = Vector2Sub(testing_points->array[global_to_testing_indices->array[indices->array[3*i + prev]]], testing_points->array[global_to_testing_indices->array[indices->array[3*i + j]]]);
            ac = Vector2Sub(testing_points->array[global_to_testing_indices->array[indices->array[3*i + next]]], testing_points->array[global_to_testing_indices->array[indices->array[3*i + j]]]);
            angle = fabsf(Vector2Angle(ac) - Vector2Angle(ab));
            angle += 2*(PI-angle) * (angle > PI);
            #pragma omp atomic
            angles[global_to_testing_indices->array[indices->array[3*i + j]]] += angle;
        }
    }
    LinkedListSize_t rim_points = LinkedListSize_tNew();
    ///////////// DEBUGGING!!
    // printf("Points and their angles:\n");/////
    // #pragma omp parallel for
    for (size_t i = 0; i < testing_points->size; i++) {
        // printf("Point %3u:\t%4.3f\n",i,angles[i]);/////
        if (angles[i] < 2*PI-0.05) {
            // #pragma omp critical
            LinkedListSize_tAppend(&rim_points, testing_to_global_indices->array[i]);
        }
    }
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

void AddIndicesInSegment(LinkedListSize_t *list, ArrayVector3 *points, float low_z, float up_z) {
    #pragma omp parallel for
    for (size_t i = 0; i < points->size; i++) {
        if (points->array[i].z > low_z && points->array[i].z <= up_z) {
            #pragma omp critical
            LinkedListSize_tAppend(list, i);
        }
    }
}

void RemoveFullIndices(LinkedListSize_t *working_indices_list, ArraySize_t *rim_indices) {
    int in_rim;
    LinkedListSize_tGoFirst(working_indices_list);
    for (size_t i = 0; i < working_indices_list->size; i++) {
        in_rim = 0;
        for (size_t j = 0; j < rim_indices->size; j++) {
            if (working_indices_list->current->value == rim_indices->array[j]) {
                in_rim = 1;
                break;
            }
        }
        if (in_rim)
            LinkedListSize_tNext(working_indices_list);
        else
            LinkedListSize_tRemove(working_indices_list, working_indices_list->current); //Remove puts list pointer on next item
    }
}

ArrayVector3 IndicesListToArrayVector3 (LinkedListSize_t *list, ArrayVector3 *points) {
    ArrayVector3 output = ArrayVector3New(list->size);
    LinkedListSize_tGoFirst(list);
    for (size_t i = 0; i < list->size; i++) {
        output.array[i] = points->array[list->current->value];
        LinkedListSize_tNext(list);
    }
    return output;    
}

ArrayVector3 IndicesArrayToArrayVector3 (ArraySize_t *array, ArrayVector3 *points) {
    ArrayVector3 output = ArrayVector3New(array->size);
    for (size_t i = 0; i < array->size; i++) {
        output.array[i] = points->array[array->array[i]];
    }
    return output;    
}

void RegisterTestingIndices(LinkedListSize_t *section_indices, ArraySize_t *global_to_testing_indices, ArraySize_t *testing_to_global_indices, size_t *registered_testing_points) {
    testing_to_global_indices->size += section_indices->size;
    testing_to_global_indices->array = realloc(testing_to_global_indices->array, testing_to_global_indices->size * sizeof(size_t));
    LinkedListSize_tGoFirst(section_indices);
    for (size_t i = 0; i < section_indices->size; i++)
    {
        global_to_testing_indices->array[section_indices->current->value] = *registered_testing_points;
        testing_to_global_indices->array[*registered_testing_points] = section_indices->current->value;
        *registered_testing_points+=1;
        LinkedListSize_tNext(section_indices);
    }
}

void AppendArrayToList(LinkedListSize_t *list, ArraySize_t *array) {
    for (size_t i = 0; i < array->size; i++) {
        LinkedListSize_tAppend(list, array->array[i]);
    }
}

ArraySize_t UpperSphereTriangulate (ArrayVector3 *points, size_t n_steps, ArraySize_t *equatorial_points) {
    LinkedListSize_t section_indices_list = LinkedListSize_tNew();
    LinkedListSize_t working_indices_list = LinkedListSize_tNew();

    ArraySize_t global_to_testing_indices = ArraySize_tZeros(points->size);
    ArraySize_t testing_to_global_indices = ArraySize_tNew(0);
    ArraySize_t final_indices_array = ArraySize_tNew(0);
    ArraySize_t rim_indices_array;
    ArraySize_t working_indices_array, section_final_indices;
    ArrayVector3 working_points_3d, testing_points_3d = ArrayVector3New(0), section_points_3d;
    ArrayVector2 working_points_2d, testing_points_2d;
    size_t registered_testing_points = 0;

    for (size_t i = 0; i < n_steps; i++) {
        float low_angle, up_angle, low_z, up_z;
        // low_angle = (i)*PI/2/n_steps;
        // up_angle = (i+1)*PI/2/n_steps;
        // low_z = cosf(up_angle);
        // up_z = cosf(low_angle);

        low_z = 1.0 - 1.0/n_steps * (i+1);
        up_z = 1.0 - 1.0/n_steps * (i);

        AddIndicesInSegment(&section_indices_list, points, low_z, up_z);
        RegisterTestingIndices(&section_indices_list, &global_to_testing_indices, &testing_to_global_indices, &registered_testing_points);
        section_points_3d = IndicesListToArrayVector3(&section_indices_list, points);
        ArrayVector3AppendArrays(&testing_points_3d, &section_points_3d);
        testing_points_2d = SterographicProjectInvertedArrayVector2(&testing_points_3d);
        LinkedListSize_tAppendList(&working_indices_list, &section_indices_list);
        working_indices_array = LinkedListSize_tToArray(&working_indices_list);
        working_points_3d = IndicesListToArrayVector3(&working_indices_list, points);
        working_points_2d = SterographicProjectInvertedArrayVector2(&working_points_3d);
        section_final_indices = Triangulation2DParallel(&working_points_2d, &testing_points_2d, &working_indices_array);
        ArraySize_tAppendArrays(&final_indices_array, &section_final_indices);
        rim_indices_array = GetRimPoints(&testing_points_2d, &final_indices_array, &global_to_testing_indices, &testing_to_global_indices);
        LinkedListSize_tFree(&working_indices_list);
        working_indices_list = LinkedListSize_tFromArray(&rim_indices_array);

        //Free lists & arrays
        //These functions empty the containers, but don't free the varables themselves
        LinkedListSize_tUnlink(&section_indices_list);
        ArrayVector3Free(&section_points_3d);
        ArrayVector2Free(&testing_points_2d);
        ArraySize_tFree(&working_indices_array);
        ArrayVector3Free(&working_points_3d);
        ArrayVector2Free(&working_points_2d);
        ArraySize_tFree(&section_final_indices);

        if (i==n_steps-1) {
            equatorial_points->size = rim_indices_array.size;
            equatorial_points->array = rim_indices_array.array;
        }
        else {
            ArraySize_tFree(&rim_indices_array);
        }
    }
    return final_indices_array;
}

ArraySize_t LowerSphereTriangulate (ArrayVector3 *points, size_t n_steps, ArraySize_t *equatorial_points) {
    LinkedListSize_t section_indices_list = LinkedListSize_tNew();
    LinkedListSize_t working_indices_list = LinkedListSize_tNew();

    ArraySize_t global_to_testing_indices = ArraySize_tZeros(points->size);
    ArraySize_t testing_to_global_indices = ArraySize_tNew(0);
    ArraySize_t final_indices_array = ArraySize_tNew(0);
    ArraySize_t rim_indices_array;
    ArraySize_t working_indices_array, section_final_indices;
    ArrayVector3 working_points_3d, testing_points_3d = ArrayVector3New(0), section_points_3d;
    ArrayVector2 working_points_2d, testing_points_2d;
    size_t registered_testing_points = 0;

    for (size_t i = 0; i < n_steps; i++) {
        float low_angle, up_angle, low_z, up_z;
        low_angle = PI - (i+1)  *PI/2/n_steps;   //Now it starts at 180 deg and goes down to 90 deg
        // up_angle =  PI - (i)*PI/2/n_steps;
        // low_z = cosf(up_angle);
        // up_z = cosf(low_angle);

        low_z = -1.0 + 1.0/n_steps * (i);
        up_z =  -1.0 + 1.0/n_steps * (i+1);

        AddIndicesInSegment(&section_indices_list, points, low_z, up_z);
        if (i==n_steps-1) {
            LinkedListSize_t equatorial_points_list = LinkedListSize_tFromArray(equatorial_points);
            LinkedListSize_tAppendList(&section_indices_list, &equatorial_points_list);
        }
        RegisterTestingIndices(&section_indices_list, &global_to_testing_indices, &testing_to_global_indices, &registered_testing_points);
        section_points_3d = IndicesListToArrayVector3(&section_indices_list, points);
        ArrayVector3AppendArrays(&testing_points_3d, &section_points_3d);
        LinkedListSize_tAppendList(&working_indices_list, &section_indices_list);
        working_indices_array = LinkedListSize_tToArray(&working_indices_list);
        working_points_3d = IndicesListToArrayVector3(&working_indices_list, points);
        // if (i==n_steps-1){
        //     ArrayVector3 equatorial_points_3d = IndicesArrayToArrayVector3(equatorial_points, points);
        //     ArrayVector3AppendArrays(&testing_points_3d, &equatorial_points_3d);
        //     ArrayVector3AppendArrays(&working_points_3d, &equatorial_points_3d);
        //     ArraySize_tAppendArrays(&working_indices_array, equatorial_points);
        // }
        testing_points_2d = SterographicProjectArrayVector2(&testing_points_3d);
        working_points_2d = SterographicProjectArrayVector2(&working_points_3d);
        section_final_indices = Triangulation2DParallel(&working_points_2d, &testing_points_2d, &working_indices_array);
        ArraySize_tAppendArrays(&final_indices_array, &section_final_indices);
        rim_indices_array = GetRimPoints(&testing_points_2d, &final_indices_array, &global_to_testing_indices, &testing_to_global_indices);
        LinkedListSize_tFree(&working_indices_list);
        working_indices_list = LinkedListSize_tFromArray(&rim_indices_array);

        //Free lists & arrays
        //These functions empty the containers, but don't free the varables themselves
        LinkedListSize_tUnlink(&section_indices_list);
        ArrayVector3Free(&section_points_3d);
        ArrayVector2Free(&testing_points_2d);
        ArraySize_tFree(&working_indices_array);
        ArrayVector3Free(&working_points_3d);
        ArrayVector2Free(&working_points_2d);
        ArraySize_tFree(&section_final_indices);
        // ArraySize_tFree(&rim_indices_array);

    }
    return final_indices_array;
}

ArraySize_t SphereTriangulate (Vector3 *points, size_t n_points, size_t n_steps) {
    ArraySize_t indices, lower_indices;
    ArraySize_t equatorial_points;
    ArrayVector3 points_array = ArrayVector3New(n_points);
    for (size_t i=0; i<n_points; i++)
        points_array.array[i] = points[i];

    indices = UpperSphereTriangulate(&points_array, n_steps, &equatorial_points);
    lower_indices = LowerSphereTriangulate(&points_array, n_steps, &equatorial_points);

//
    printf("upper size:%u\n",indices.size);
    printf("lower size:%u\n",lower_indices.size);
//

    ArraySize_tAppendArrays(&indices, &lower_indices);
    ArraySize_tFree(&lower_indices);
    ArraySize_tFree(&equatorial_points);
    ArrayVector3Free(&points_array);

    return indices;
}
