#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
	// sudo apt install libreadline-dev

char* getinput();
char* remove_trailing_whitespace(const char *string);

int32_t main(void){
	// Input file
		rl_bind_key('\t', rl_complete);
		char *input_file_name = readline("Enter your input file: ");
		char *temp_string = remove_trailing_whitespace(input_file_name);
		strcpy(input_file_name, temp_string);
		free(temp_string);
		FILE *input_file = fopen(input_file_name, "r");
		while (input_file == NULL) {
			printf("Failed to open/find %s\n", input_file_name);
			input_file_name = readline("Enter your input file: ");
			input_file = fopen(input_file_name, "r");
		}
		rl_unbind_key('\t');
	// Encrypt or decrypt
		printf("Enter 'e' to encrypt or 'd' to decrypt: ");
		char *encrypt_or_decrypt = getinput(); 
		while( encrypt_or_decrypt[0] != 'e' && encrypt_or_decrypt[0] != 'd' ){
			printf("Enter 'e' to encrypt or 'd' to decrypt: ");
			encrypt_or_decrypt = getinput(); 
		}
	// Password
		char *password;
		password = getpass("Enter password: ");
		int64_t password_size = strlen(password);

	int64_t output_data_size = 1;
	char* output_data = malloc(output_data_size);
	output_data[0] = '\n';
	int64_t password_index = 0;
	char password_char = 0;
	char output_char = 0;
	for( char input_char = fgetc(input_file); input_char != EOF; input_char = fgetc(input_file) ){
		//allocate another character
			output_data_size+=1;
			output_data = realloc(output_data, output_data_size );
		//if input char is a tab or a new line then write to output data and continue
			if(input_char == '\t' || input_char == '\n'){
				output_data[output_data_size - 1] = input_char;
				continue;
			}
		//get next password character
			char password_char = password[password_index];
			password_index = (password_index + 1) % password_size;
		//subtract 32 from input char and password char
			input_char-=32;
			password_char-=32;
		//if encrypt ten add number and then mod (127-32)
			if(*encrypt_or_decrypt == 'e'){
				output_char = input_char + password_char;
				output_char = output_char % (127 - 32);
			}
		//if decrypt then subtract numbers and add then mod
			if(*encrypt_or_decrypt == 'd'){
				output_char = input_char - password_char;
				output_char = output_char + (127 - 32);
				output_char = output_char % (127 - 32);
			}
		//add 32
			output_char+=32;
		//write to output data
			output_data[output_data_size - 1] = output_char;
	}

	printf("%s", output_data);
	
	// Clean up
		fclose(input_file);

	return 0;
}

char* getinput(){
	// Need to free once done
	char *input_line = NULL; //char[]
	size_t size = 0;
	size_t return_value = getline(&input_line, &size, stdin);
	if( return_value == -1){
		return NULL; // Error getting line so return null
	}
	// Remove the last new line
	char *last_char = &(input_line)[return_value - 1];
	if( *last_char == '\n' ){
		*last_char = '\0';
	}

	return input_line;
}

char* remove_trailing_whitespace(const char *string){
	// Need to free returned string
	// get string size
		int64_t string_size = 0;
		for(; string[string_size] != '\0'; string_size++);
	// make return string
		char *return_string = malloc(string_size);
		strcpy(return_string, string);
		for(int64_t i = string_size - 1; i >= 0; i--){
			if(return_string[i] == ' ' || return_string[i] == '\t'){
				return_string[i] = '\0';
			}else if(return_string[i] == '\n'){
				continue;
			}else{
				return return_string;
			}
		}
		return return_string;
}
