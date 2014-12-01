CC=g++
BIN=bin
INCLUDE=-I src/game -I src/util -I src/monte_carlo
CFLAGS=-O3 -fopenmp -c -Wall -std=c++11 $(INCLUDE)
LDFLAGS=-fopenmp -std=c++11
SOURCES=omp_util.cpp connect4.cpp test_connect4.cpp monte_carlo.cpp test_monte_carlo.cpp main.cpp
OBJECTS=$(addprefix $(BIN)/, $(SOURCES:.cpp=.o))
EXECUTABLE=$(BIN)/connect4
vpath %.cpp src/game:src/main:src/util:src/monte_carlo

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

-include $(BIN)/$(OBJECTS:.o=.d)

$(BIN)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $(BIN)/$*.o
	$(CC) -MM $(CFLAGS) $< > $(BIN)/$*.d 
	@mv -f $(BIN)/$*.d $(BIN)/$*.d.tmp
	@sed -e 's|.*:|$(BIN)/$*.o:|' < $(BIN)/$*.d.tmp > $(BIN)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(BIN)/$*.d.tmp | fmt -1 | \
	sed -e 's/^ *//' -e 's/$$/:/' >> $(BIN)/$*.d
	@rm -f $(BIN)/$*.d.tmp

clean:
	rm -f $(BIN)/*.o $(BIN)/*.d $(EXECUTABLE)
