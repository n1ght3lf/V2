
CXX = g++ #CXX - pasirenka kompiliatorių

CXXFLAGS = -std=c++14 # CXXflags - compiler flags

TARGET = V1 #TARGET - exectuable file name

SRCS = main.cpp functionality.cpp input.cpp calculations.cpp student.cpp #SRCS - source files

OBJS = $(SRCS:.cpp=.o) #Transform .cpp to .o

$(TARGET): $(OBJS) # V1: main.o functionality.o input.o calculations.o student.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) 
#g++ -std=c++14 -o V1 main.o functionality.o input.o calculations.o student.o


.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@  
#g++ -std=c++14 -c main.cpp -o main.o . $< - prereq file, $@ - target file

clean: #remove object files
	del /Q $(OBJS)

distclean: clean #remove object files and executable
	del /Q $(TARGET).exe