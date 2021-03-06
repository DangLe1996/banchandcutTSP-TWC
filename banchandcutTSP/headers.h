#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <math.h>
#include <time.h>
  #include "ilcplex/cplex.h"
//#include "cplex.h"

//Export 
#define EXPORT __declspec(dllexport)

/// C PREPROCESSOR CODE ////////////////////////////////////////////////////////

// Boolean values simulated with signed integers
#define ALL		2
#define YES     1	// True
#define NO      0	// False
#define NONE   -1	// Unknown

// General precision for dealing with non integer comparisons
#define EPSILON 0.0001

// Some basic functions:
#define ABS(x) (((x) > 0 ) ? (x) : -(x))	
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) > (b)) ? (b) : (a))
#define SIZE(x) (sizeof (x) / sizeof (*(x)))
////////////////////////////////////////////////////////////////////////////////

/// Typedefs & structs /////////////////////////////////////////////////////////

typedef struct LINE {
	int		dim; //size of line
	int		start;	// first node of line
	int  	*sequence; // sequence of nodes in line
} LINES;


typedef struct CUTSET {
	int		dim; //size of cut
	int  	*S; // set of vertices in cut
} CUTSET;

struct cutinfo {
	CPXLPptr lp;
	int      numcols;
	int      num;
	double   *x;
	int      *beg;
	int      *ind;
	double   *val;
	double   *rhs;
	int      nodeid;
	double   nodeobjval;
	int      objsen;
};
typedef struct cutinfo CUTINFO, *CUTINFOptr;


typedef struct ZONEID {
	int	 dim; //number of stops in zoneid
	int  uzoneid; //unique zoneid number among all routes
	int* stops; // set of stops in zoneid
} ZONEID;

typedef struct SCUTS {
	double value;
	int cutnz;
	int *cutind;
	double *cutval;
} SCUTS;

int		N, Np, E;
double	**C;
double **T;
//double  **time;
//int     *cut_set;
int		*index_i;
int		*index_j;
int		**index_e;
double	**capacity;
SCUTS   sepcut;
CUTSET  *cutset;
int		*visited;
int		*queue;
int		*tree;
double  *alpha;
double  **currentFlow;
int		*previous;
int		n_conn_comp;
double  old_objval, pi_0;
int     count_same_node;
int     n_int_feas_subproblems;
int     n_frac_feas_subproblems;
int     n_feas_subproblems;


double	min_cap_cuts(double **);
void	connected_components(double **);
double	maxFlowAndCut(int, int, double **);
double exact_separation_SEC(int, double *);
static void free_and_null(char **);
static int CPXPUBLIC mycutcallback(CPXCENVptr, void *, int, void *, int *);
//EXPORT double solve_TSP(int* sequence);
 double solve_TSP_TWC(int* sequence, double lambda, double delta, double** M,
	double* W, double* earliest, double* latest);
FILE	*open_file(const char *filename, const char *mode);
void read_INSTANCE(const char *);
void read_INSTANCE_AMAZON(const char *);
void initialize_Instance_Amazon_New(double** travelCost, int n_stops);
char	*create_char_vector(int cells);
void	free_char_vector(char **ptr);
double	*create_double_vector(int cells);
void	free_double_vector(double **ptr);
int		*create_int_vector(int cells);
void	free_int_vector(int **ptr);
double	**create_double_matrix(int rows, int columns);
void	free_double_matrix(double ***ptr, int rows);
int		**create_int_matrix(int rows, int columns);
int ***create_int_matrix3d(int rows, int columns, int col2);
void	free_int_matrix(int ***ptr, int rows);
void i_vector(int **vector, int n, char *s);
void d_vector(double **vector, int n, char *s);
void c_vector(char **vector, int n, char *s);
void Initialize_memory(void);
void free_memory(void);
static int CPXPUBLIC mycutcallbackATSPTWC(CPXCENVptr, void *, int, void *, int *);
 /*void solveATSPNumpy(int* sequence, double* weightedCost, int n_stops, double* TWC_data
	, double* travelCost, double lambda, double delta);*/
///////////////////////////////////////////////////////////////////////////////