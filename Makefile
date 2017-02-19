# compiler flag
CXX = g++

# flag for compiling opitons
CXXFLAGS = -std=c++11 -I${BLAS_INC} -O2 -Wall
BLASFLAGS = -L${BLAS_LIB}
BLASLIBS = -lopenblas

all: eigenv
# target executable dependency
eigenv : eigenv.o
	${CXX} ${CXXFLAGS} -o eigenv eigenv.o ${BLASFLAGS} ${BLASLIBS}

eigenv.o : eigenv.cc
	${CXX} ${CXXFLAGS} -c -o eigenv.o eigenv.cc ${BLASFLAGS} ${BLASLIBS}

# clean all dependencies, result and the executable
clean :
	rm *.o eigenv
