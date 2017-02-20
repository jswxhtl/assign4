# compiler flag
CXX = g++

# flag for compiling opitons
CXXFLAGS = -std=c++11 -I${BLAS_INC} -O2 -Wall
BLASFLAGS = -L${BLAS_LIB}
BLASLIBS = -lopenblas

all: eigenv powermethod
# target executable dependency
eigenv : eigenv.o
	${CXX} ${CXXFLAGS} -o eigenv eigenv.o ${BLASFLAGS} ${BLASLIBS}

eigenv.o : eigenv.cc
	${CXX} ${CXXFLAGS} -c -o eigenv.o eigenv.cc ${BLASFLAGS} ${BLASLIBS}

powermethod : powermethod.o calculation.o
	${CXX} ${CXXFLAGS} -o powermethod powermethod.o calculation.o ${BLASFLAGS} ${BLASLIBS}

powermethod.o : powermethod.cc calculation.h
	${CXX} ${CXXFLAGS} -c powermethod.cc ${BLASFLAGS} ${BLASLIBS}

calculation.o : calculation.cc
	${CXX} ${CXXFLAGS} -c calculation.cc ${BLASFLAGS} ${BLASLIBS}

.PHONY: clean
# clean all dependencies, result and the executable
clean :
	rm *.o eigenv powermethod
