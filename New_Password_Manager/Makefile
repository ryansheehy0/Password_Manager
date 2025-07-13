LIBS = -lssl -lcrypto
TARGET = password_manager
# Files
H_FILES   = $(wildcard ./*.h)
CPP_FILES = $(wildcard ./*.cpp)
O_FILES   = $(patsubst ./%.cpp, ./%.o, $(CPP_FILES))

$(TARGET): $(O_FILES)
	g++ $^ -o $@ $(LIBS)

./%.o: ./%.cpp
	g++ -c $< -o $@

clear:
	rm -f ./*.o $(TARGET)