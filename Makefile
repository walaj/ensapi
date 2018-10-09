#CC=/usr/local/bin/g++-8
BOOST_LOCAL=/usr/local/Cellar/boost/1.67.0_1/lib
CXX=clang++
SOURCES := ensapi.cpp
# Objs are all the sources, with .cpp replaced by .o
OBJS := $(SOURCES:.cpp=.o)
CXXFLAGS=-std=c++11
LDFLAGS:=-L/usr/local/lib -L$(BOOST_LOCAL) -lstdc++ -lcpprest -lssl -lcrypto -lboost_system -lboost_thread-mt -lboost_chrono-mt 
all: ensapi

# Compile the binary 't' by calling the compiler with cflags, lflags, and any libs (if defined) and the list of objects.
ensapi: $(OBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o ensapi $(OBJS) $(LDFLAGS) $(LIBS)

# Get a .o from a .cpp by calling compiler with cflags and includes (if defined)
.cpp.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -c $<

clean:
	rm -f *.o *~
