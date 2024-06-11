
CXX = g++ #CXX - pasirenka kompiliatorių

CXXFLAGS = -std=c++14 -O2 # CXXflags - compiler flags

TARGET = main #TARGET - exectuable file name

SRCS = main.cpp functionality.cpp input.cpp calculations.cpp student.cpp #SRCS - source files

OBJS = $(SRCS:.cpp=.o) #Transform .cpp to .o

# Test files
TEST_SRCS = test.cpp
# V1: test.cpp

# Test objects
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
# V1: test.o

# test file name
TEST_TARGET = test
# V1: main.o functionality.o input.o calculations.o student.o




$(TARGET): $(OBJS) # V1: main.o functionality.o input.o calculations.o student.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) 
#g++ -std=c++14 -o V1 main.o functionality.o input.o calculations.o student.o

# Rule to build the test executable
$(TEST_TARGET): student.o $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) student.o $(TEST_OBJS)
# g++ -std=c++14 -o test student.o test.o


.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@  
#g++ -std=c++14 -c main.cpp -o main.o . $< - prereq file, $@ - target file

clean: #remove object files
	rm -f $(OBJS) $(TEST_OBJS)


distclean: clean #remove object files and executable
	rm -f $(TARGET) $(TEST_TARGET)

	setup.sh:
    @echo "#!/bin/bash" > setup.sh
    @echo "echo 'Setting up the environment...'" >> setup.sh
    @echo "sudo apt-get update" >> setup.sh
    @echo "sudo apt-get install g++" >> setup.sh
    @echo "echo 'Environment setup complete.'" >> setup.sh
    @chmod +x setup.sh