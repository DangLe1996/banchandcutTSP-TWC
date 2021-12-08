LIB = /encs/pkg/cplex-20.1.0/root/cplex
CXX=gcc -O2 -std=c11
CXX2=gcc -O2 -fPIC -std=c11
CPLXST=-DIL_STD  -L$(LIB)/lib/x86-64_linux/static_pic -lcplex -lm -lpthread -ldl
LIB2=-I$(LIB)/include/ilcplex
OBJ= main.o read_data.o solve_Clustered_ATSP_TWC_model.o  Score.o solve_MIP_TSP_model.o

ATSP1: $(OBJ)
	$(CXX) -shared -I$(LIB)/include/ilcplex $(OBJ) -o ATSP-TWC.so $(CPLXST)

main.o : main.c headers.h
	$(CXX2) -c main.c $< $(LIB2)
read_data.o : read_data.c headers.h
	$(CXX2) -c read_data.c $< $(LIB2)
	
solve_MIP_TSP_model.o : solve_MIP_TSP_model.c headers.h
	$(CXX2) -c solve_MIP_TSP_model.c $< $(LIB2)

solve_Clustered_ATSP_TWC_model.o : solve_Clustered_ATSP_TWC_model.c headers.h
	$(CXX2) -c solve_Clustered_ATSP_TWC_model.c $< $(LIB2)

Score.o : Score.c headers.h Score.h
	$(CXX2) -c Score.c $< $(LIB2)

clean :
	rm ATSP-TWC.so $(OBJ)

