
#define GetCurrentDir _getcwd
#include "headers.h"
#include "Score.h"





void initialize_Instance_Amazon_New_Numpy(double* travelCost, int n_stops) {

	int i, j, e;
	N = n_stops;
	E = (N * (N - 1));
	Initialize_memory();

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			C[i][j] = travelCost[N * i + j];
		}
	}
	for (i = 0; i < N; i++)
		index_e[i][i] = NONE;
	e = 0;
	for (i = 0; i < N-1; i++) {
		for (j = 1; j < N; j++) {

			if (i == 0 && j == N - 1) {
				continue;
			}

			if (i != j) {
				//printf("%d, %d \n ", i, j);
				index_i[e] = i;
				index_j[e] = j;
				index_e[i][j] = e;
				e++;
			}
			
		}
	}
	E = e;
	//assert(e == E);

}

const char* getfield(char* line,  double *input, int pos)
{
	const char* tok;
	int i = -2;
	for (tok = strtok(line, ",");
		tok && *tok;

		tok = strtok(NULL, ",\n"))
	{
		i += 1;
		if (i < 0){
			continue;
		}
		char* ptr;
		double d = atof(tok);
		input[pos + i] = d;
		
		//printf(tok);
		/*if (!--num)
			return tok;*/
	}
	free(tok);
	/*return NULL;*/
}
int main() {

	int N_local = 21;
	N = N_local;
	double* travelCost  = malloc(sizeof(double) * (N*N)); 
	double* sequence  = malloc(sizeof(int) * (N)); 
	double* TWC_data = malloc(sizeof(double) * (N*3));

	char* FilePath = "RouteID_d405eb42-2950-49b1-b09b-0f15df295a36.csv";

	FILE* stream = fopen(FilePath, "r");
	char line[1024];
	//Get travel time
	fgets(line, 1024, stream); //skip header
	int pos = 0;
	while (fgets(line, 1024, stream))
	{
		char* tmp = strdup(line);
		getfield(tmp, travelCost, pos);
		// NOTE strtok clobbers tmp
		free(tmp);
		pos += N;

		if (pos > N * N-1) {
			break;
		}

	}
	//Get TWC Informations
	pos = 0;
	fgets(line, 1024, stream); //skip header
	while (fgets(line, 1024, stream))
	{
		char* tmp = strdup(line);
		 getfield(tmp, TWC_data, pos);
		pos += 3;
		// NOTE strtok clobbers tmp
		free(tmp);
	}
	double* E_i = malloc(sizeof(double) * N);
	double* L_i = malloc(sizeof(double) * N);
	double* w_i = malloc(sizeof(double) * N);

	for (int i = 0; i < N; i++) {
		
			E_i[i] = TWC_data[i *3]*60.0;
			L_i[i] = TWC_data[i*3 + 1]*60.0;
			w_i[i] = TWC_data[i*3 + 2];
		
	}



	printf("test");

	printf("inside ivan code");
	clock_t  start, end;
	double opt_value;
	double cputime;
	n_conn_comp = 0;
	old_objval = 0;
	count_same_node = 0;
	n_int_feas_subproblems = 0;
	n_frac_feas_subproblems = 0;
	n_feas_subproblems = 0;

	/*
	printf("travel cost is %f",travelCost[1][2]);
	printf("N is %d", n_stops);*/

	N = 10;


	initialize_Instance_Amazon_New_Numpy(travelCost, N);
	////start = clock();
	/*printf("Solving TSP with B&C algorithm: \n");*/

	double** M = create_double_matrix(N, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			M[i][j] = 20000;
		}
	}

	double lambda = 0.5;
	double delta = 0.5;


	N -= 1;


	opt_value = solve_TSP(sequence,lambda,delta,M,w_i,E_i,L_i);
	//printf("Optimal travel time is :  %f \n", opt_value);
	end = clock();
	//cputime = (double)(end - start) / (double)CLOCKS_PER_SEC;   //Compute CPU time

	free_memory();
	//free(travelCost);
	//freeDoubleMatrix(travelCost, n_stops);


}


EXPORT void solveATSPNumpy(int* sequence, double* travelCost, int n_stops) {
	printf("inside ivan code");
	clock_t  start, end;
	double opt_value;
	double cputime;
	n_conn_comp = 0;
	old_objval = 0;
	count_same_node = 0;
	n_int_feas_subproblems = 0;
	n_frac_feas_subproblems = 0;
	n_feas_subproblems = 0;

	/*
	printf("travel cost is %f",travelCost[1][2]);
	printf("N is %d", n_stops);*/
	
	////start = clock();
	/*printf("Solving TSP with B&C algorithm: \n");*/

	//opt_value = solve_TSP(sequence);
	//printf("Optimal travel time is :  %f \n", opt_value);
	end = clock();
	//cputime = (double)(end - start) / (double)CLOCKS_PER_SEC;   //Compute CPU time

	free_memory();
	//free(travelCost);
	//freeDoubleMatrix(travelCost, n_stops);
}

