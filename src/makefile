CXX = g++

CXXFLAGS = -c

LIBS = -lSDL2

SRCS = raycaster.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = raycaster

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

