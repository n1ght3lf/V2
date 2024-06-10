
CXX = g++ #CXX - pasirenka kompiliatorių

CXXFLAGS = -std=c++14 -O2 # CXXflags - compiler flags

TARGET = main #TARGET - exectuable file name

SRCS = main.cpp functionality.cpp input.cpp calculations.cpp student.cpp #SRCS - source files

OBJS = $(SRCS:.cpp=.o) #Transform .cpp to .o

GTEST = /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a

# Test files
TEST_SRCS = student_test.cpp
# V1: student_test.cpp

# Test objects
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
# V1: student_test.o

# test file name
TEST_TARGET = student_test
# V1: main.o functionality.o input.o calculations.o student.o

$(TARGET): $(OBJS) # V1: main.o functionality.o input.o calculations.o student.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) 
#g++ -std=c++14 -o V1 main.o functionality.o input.o calculations.o student.o

# Rule to build the test executable
$(TEST_TARGET): student.o $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) student.o $(TEST_OBJS) $(GTEST)
# g++ -std=c++14 -o student_test student.o student_test.o /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a


.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@  
#g++ -std=c++14 -c main.cpp -o main.o . $< - prereq file, $@ - target file

clean: #remove object files
	rm -f $(OBJS) $(TEST_OBJS)


distclean: clean #remove object files and executable
	rm -f $(TARGET) $(TEST_TARGET)