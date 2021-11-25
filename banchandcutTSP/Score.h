
#include <stdlib.h>
#define EXPORT __declspec(dllexport)
#pragma once

// EXPORT double PythonAPI(double** weightMatrix, int* actual, int* sub, int DIMENSION);
void freeDoubleMatrix(double** matrix, int DIMENSION);
void normalizeMatrix(double** weightMatrix, double** normalizedMatrix, int DIMENSION);

double calculateSD(double** data, int dimension, double mean);


double seq_dev(int* actual, int* sub, int count);

double score(int* actual, int* sub, int count, double** matrix);

double erp_per_edit(int* actual, int* sub, int len, double** matrix, double g);


struct Memos erp_per_edit_helper(int* actual, int* sub, int len_actual, int len_sub, double** matrix, double g);

double dist_erp(int p1, int p2, double** mat, int g);

static double gap_sum(int pathLength, double g);


static int findIndex(int* list, int item);
