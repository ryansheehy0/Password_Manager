LIBS = -lssl -lcrypto
TARGET = password_manager
OBJ_FILES = ascii_keyboard_char.o generate_password.o password_manager.o password.o passwords.o

$(TARGET): $(OBJ_FILES)
	g++ $^ -o $(TARGET) $(LIBS)

%.o: %.cpp %.h
	g++ -c $< -o $@

clear:
	rm -f $(OBJ_FILES) $(TARGET)