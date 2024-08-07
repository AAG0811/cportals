#include <stdlib.h>
#include <stdio.h>

typedef struct
{
  int *array;
  size_t size;
} ArrayStruct;

void init_as(ArrayStruct *as, size_t size)
{
  as->size = size;
  as->array = malloc(size * sizeof(int));
  if (as->array == NULL)
  {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < size; i++)
  {
    as->array[i] = i * 10;
  }
}

void print_array_struct(const ArrayStruct *as)
{
  for (size_t i = 0; i < as->size; i++)
  {
    printf("array[%zu] = %d\n", i, as->array[i]);
  }
}

void free_array_struct(ArrayStruct *as)
{
  free(as->array);
  as->array = NULL;
  as->size = 0;
}
ArrayStruct vec3(int x, int y, int z)
{
  ArrayStruct as;
  init_as(&as, 3);
  as.array[0] = x;
  as.array[1] = y;
  as.array[2] = z;
  as.size = 3;
  return as;
}
// matrix struct
typedef struct
{
  float *array;
} Matrix;
// creates 3x3 matrix of floats with value being value for leading diagnoal
void mat3(Matrix *ms, float value)
{
  // malloc
  ms->array = malloc((3 * 3) * sizeof(float));
  // set values
  for (int i = 0; i < 9; i++)
  {
    if (i == 0 || i == 4 || i == 8)
    {
      ms->array[i] = value;
    }
    else
    {
      ms->array[i] = 0.0;
    }
  }
}

void printMat3(Matrix *ms)
{
  printf("%d, %d, %d,\n", ms->array[0], ms->array[3], ms->array[6]);
  printf("%d, %d, %d,\n", ms->array[1], ms->array[4], ms->array[7]);
  printf("%d, %d, %d,\n", ms->array[2], ms->array[5], ms->array[8]);
}

int main()
{
  Matrix mat;
  mat3(&mat, 1.0f);
  printMat3(&mat);
  return 0;
}