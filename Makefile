CXX = g++
CXXFLAGS = -std=c++11 -Wall
INCLUDES = -Iinclude

SRCS = src/Admin.cpp src/StandardUser.cpp src/Action.cpp src/User.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = password_manager

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(EXEC) $(OBJS)

clean:
	rm -f $(OBJS) $(EXEC)
