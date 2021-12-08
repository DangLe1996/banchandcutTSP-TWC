
#include <assert.h>
#include <stdio.h>
//#include "testCases.h"
#include "Score.h"
#include <math.h>
#include <float.h>
#include <string.h>

//
//int main() {
//	//assertScore();
//	assertPythonAPI();
//	//assertScoreSameRoute();
//	//assertNormailizeMatrix();
//	//assertSwap();
//}

void freeDoubleMatrix(double** matrix, int DIMENSION) {
	for (int i = 0; i < DIMENSION; i++) {

		free(matrix[i]);
	
	}
	free(matrix);
}


 double getScore(double** weightMatrix, int* actual, int* sub, int DIMENSION) {



	double** normailizedMatrix = (double**)malloc(DIMENSION * sizeof(double*));
	for (int row = 0; row < DIMENSION; row++) {
		normailizedMatrix[row] = (double*)malloc(DIMENSION * sizeof(double));
	}

	double result = 0;
	normalizeMatrix(weightMatrix, normailizedMatrix, DIMENSION);
	result = score(actual, sub, DIMENSION, normailizedMatrix);

	/*freeDoubleMatrix(normailizedMatrix, DIMENSION);
	freeDoubleMatrix(weightMatrix, DIMENSION);
	free(actual);
	free(sub);*/
	//printf("Score is %f", result);


	return result;
}




void normalizeMatrix(double** weightMatrix, double **normalizedMatrix, int DIMENSION) {

	double avg = 0.0;
	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			avg += weightMatrix[i][j];
		}
	}
	avg = avg / pow(DIMENSION,2);
	double std_time = calculateSD(weightMatrix, DIMENSION, avg);
	double minNewTime = DBL_MAX;

	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			double oldTime =  weightMatrix[i][j];
			double newTime = (oldTime - avg) / std_time;

			if (newTime < minNewTime) {
				minNewTime = newTime;
			}
			normalizedMatrix[i][j] = newTime;
		}
	}

	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			double newTime = normalizedMatrix[i][j];
			double shiftedTime = newTime - minNewTime;
			normalizedMatrix[i][j] = shiftedTime;

		}
	}


}


double calculateSD(double **data, int dimension, double mean) {
	double sum = 0.0, SD = 0.0;

	int i,j;
	
	for (i = 0; i < dimension; i++) {
		for (j = 0; j < dimension; j++) {
			SD += pow(data[i][j] - mean, 2);
		}
	}
	return sqrt(SD / pow(dimension,2));
}



int isInvalue(int *actual, int *sub) {


	if (actual[0] != sub[0]) return 1;
	else return 0;

}

double seq_dev(int* actual, int* sub, int count) {
	int* comp_list = (int*)malloc(sizeof(int) * count);
	int* temp_sub = (int*)malloc(sizeof(int) * count);
	int* temp_act = (int*)malloc(sizeof(int) * count);

	int comp_sum = 0;

	for (int i = 0; i < count; i++) {
		temp_sub[i] = sub[i+1];
		temp_act[i] = actual[i+1];
	}
	count = count - 1;
	for (int i = 0; i < count; i++) {
		comp_list[i] = findIndex(temp_act, temp_sub[i]);
	}

	for (int i = 1; i < count; i++) {
		comp_sum += abs(comp_list[i] - comp_list[i - 1]) - 1;
	}

	int n = count;
	free(comp_list);
	free(temp_sub);
	free(temp_act);
	return (2.0 / (n * (n - 1))) * comp_sum;

}

struct Memos {
	double d;
	int count;

};


double score(int* actual, int* sub, int len, double** matrix) {


	double g = 1000.0;
	
	double seq_dev_score = seq_dev(actual, sub, len);

	//printf("SD Score is %f\n", seq_dev_score);

	double erp_per_edit_score = erp_per_edit(actual, sub, len, matrix, g);

	double result = seq_dev_score * erp_per_edit_score;

	//printf("route score: %.5f\n", result);

	return result;
}

struct Memos memos[1000][1000];

double erp_per_edit(int* actual, int* sub, int len, double** matrix, double g) {

	double d = 0; //total
	int count = 0;
	struct Memos result;

	memset(memos, -1, sizeof(memos));
	result = erp_per_edit_helper(actual, sub, len, len, matrix, g);
	if (result.count == 0) {
		return 0;

	}
	else {
		return result.d / result.count;
	}

}


struct Memos erp_per_edit_helper(int* actual, int* sub, int len_actual, int len_sub, double** matrix, double g) {

	//int* rest_Actual;
	//int* rest_Sub;

	if (memos[len_actual][len_sub ].count != -1) {
		return memos[len_actual ][len_sub ];

	}

	if (len_sub == 0 ) {
		memos[len_actual ][len_sub].count = len_actual;
		memos[len_actual ][len_sub].d = gap_sum(len_actual, g);
		
		return memos[len_actual ][len_sub];
	
	}
	else if (len_actual == 0) {
		memos[len_actual ][len_sub].count = len_actual;
		memos[len_actual ][len_sub].d = gap_sum(len_actual, g);

		return memos[len_actual][len_sub];
		
	}
	int head_actual = actual[0];
	int head_sub = sub[0];

	//if (len_actual > 1) {
	//	 rest_Actual = (int*)malloc(sizeof(int) * len_actual - 1);
	//}
	//if (len_sub) {
	//	 rest_Sub = (int*)malloc(sizeof(int) * len_sub - 1);
	//}
	int* rest_Actual = (int*)malloc(sizeof(int) * 1000);
	int* rest_Sub = (int*)malloc(sizeof(int) * 1000);

	for (int i = 1; i < len_actual; i++) {

		rest_Actual[i - 1] = actual[i];

	}
	for (int i = 1; i < len_sub; i++) {

		rest_Sub[i - 1] = sub[i];
	}

	struct Memos result = { .count = -1, .d = -1 };

	struct Memos memo1 = { .count = -1, .d = -1 };
	struct Memos memo2 = { .count = -1, .d = -1 };
	struct Memos memo3 = { .count = -1, .d = -1 };

	memo1 = erp_per_edit_helper(rest_Actual, rest_Sub, len_actual - 1, len_sub - 1, matrix, g);
	memo2 = erp_per_edit_helper(rest_Actual, sub, len_actual - 1, len_sub, matrix, g);
	memo3 = erp_per_edit_helper(actual, rest_Sub, len_actual, len_sub - 1, matrix, g);

	double option_1 = 0, option_2 = 0, option_3 = 0;
	double option_fin = 0;
	option_1 = memo1.d + dist_erp(head_actual, head_sub, matrix, g);
	option_2 = memo2.d + dist_erp(head_actual, -1, matrix, g);
	option_3 = memo3.d + dist_erp(head_sub, -1, matrix, g);

	if (option_1 < option_2 && option_1 < option_3)
	{
		result.d = option_1;
		if (head_actual == head_sub) {
			result.count = memo1.count ;
		}
		else {
			result.count = memo1.count + 1;
		}
		
	}
	else if (option_2 < option_3)
	{
		result.d = option_2;
		result.count = memo2.count + 1;
	}
	else
	{
		result.d = option_3;
		result.count = memo3.count + 1;
	}

	memos[len_actual ][len_sub ] = result;

	//if(len_actual > 1)
		free(rest_Actual);
	//if(len_sub > 1)
		free(rest_Sub);

	return result;
	
}




double dist_erp(int p1,  int p2, double** mat, int g) {
	g = 1000;
	double dist;
	if (p1 == -1 || p2 == -1) {
		dist = g;
	}
	else {
		
		dist = mat[p1][p2];
	}
	return dist;
}

static double gap_sum(int pathLength, double g) {
	return pathLength * g;
}

static int findIndex(int* list, int item) {
	int i = 0;
	while (list[i] != item) {
		i++;
	}
	return i;
}

