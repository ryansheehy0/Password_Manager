LIBS = -lssl -lcrypto
TARGET = password_manager
# Folders
O_FOLDER   = Obj
H_FOLDER   = Include
CPP_FOLDER = Src
# Files
H_FILES   = $(wildcard $(H_FOLDER)/*.h)
CPP_FILES = $(wildcard $(CPP_FOLDER)/*.cpp)
O_FILES   = $(patsubst $(CPP_FOLDER)/%.cpp, $(O_FOLDER)/%.o, $(CPP_FILES))

$(TARGET): $(O_FILES)
	g++ $^ -o $@ $(LIBS)

$(O_FOLDER)/%.o: $(CPP_FOLDER)/%.cpp
	mkdir -p $(O_FOLDER)
	g++ -c $< -o $@

clear:
	rm -f $(O_FOLDER)/*.o $(TARGET)