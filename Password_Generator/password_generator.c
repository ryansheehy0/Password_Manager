#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../user_input.h"

// Functions
long get_pass_len();
bool ask_char_type(char *ask_message);
void append_to_pass_chars(char *chars_array, int chars_array_len, char *pass_chars, int *pass_chars_len);

int main(void){
	// Get length of the password
  long pass_len = get_pass_len();
	// Get if the password can have special characters or not
  bool spec = ask_char_type("special characters");
	// Get if the password can have uppercase chars or not
  bool upper = ask_char_type("uppercase characters");
	// Get if the password can have lowercase chars or not
  bool nums = ask_char_type("numbers");
	// Get if the password can have spaces or not
  bool spaces = ask_char_type("spaces");

  // Arrays of password characters
  char lower_chars[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  int letters_len = sizeof(lower_chars) / sizeof(char);
  char upper_chars[letters_len];
  for(int i = 0; i < letters_len; i++){
    upper_chars[i] = toupper(lower_chars[i]);
  }
	char num_chars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  int nums_len = 10;
	char spec_chars[] = {'~', '`', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '+', '=', '{', '}', '[', ']', '|', '\\', ':', ';', '\'', '"', '<', '>', ',', '.', '?', '/'};
  int spec_chars_len = sizeof(spec_chars) / sizeof(char);
	// Generate password
    int pass_chars_len = letters_len;
    char *pass_chars = malloc(pass_chars_len);
    // Set password characters to lowercase letters
    for(int i = 0; i < pass_chars_len; i++){
      pass_chars[i] = lower_chars[i];
    }
		// Get an array of each type of characters that can be in the password
    if(spec){
      append_to_pass_chars(spec_chars, spec_chars_len, pass_chars, &pass_chars_len);
    }
    if(upper){
      append_to_pass_chars(upper_chars, letters_len, pass_chars, &pass_chars_len);
    }
    if(nums){
      append_to_pass_chars(num_chars, nums_len, pass_chars, &pass_chars_len);
    }
    if(spaces){
      char space[1] = {' '};
      append_to_pass_chars(space, 1, pass_chars, &pass_chars_len);
    }
		// Keep choosing a random character from that array until you have the password length
    srand(time(NULL));
    char generated_pass[pass_len];
    for(int i = 0; i < pass_len; i++){
      // Get random number from 0 to pass_chars_len - 1
      int rand_num = rand() % pass_chars_len;
      // Get a random number from pass_chars and set it equal to the next generated_pass character
      generated_pass[i] = pass_chars[rand_num];
    }
		// Print out the generated password
    printf("%s\n", generated_pass);
}


long get_password_length(){
  printf("Enter length of password: ");
  char *length_str = get_input();
  char *endptr;
  long length = strtol(length_str, &endptr, 10);
  while(*endptr != '\0' || length < 1){
    if(*endptr != '\0'){
      printf("Invalid character found: %c\n", *endptr);
    }else if( length < 1 ){
      printf("Password has to be greater than 0.\n");
    }
    printf("Enter length of password: ");
    length_str = get_input();
    length = strtol(length_str, &endptr, 10);
  }
  free(length_str);
  return length;
}

bool ask_char_type(char *ask_message){
  char char_type;
  bool is_first = true;
  do{
    if(!is_first){
      printf("Must be 'y' or 'n'.\n");
    }
    printf("Can the password have %s?(y/n): ", ask_message);
    scanf(" %c", &char_type);
    is_first = false;
  }while(char_type != 'y' && char_type != 'Y' && char_type != 'n' && char_type != 'N');
  if(char_type == 'y' || char_type == 'Y'){
    return true;
  }
  return false; 
}

void append_to_pass_chars(char *chars_array, int chars_array_len, char *pass_chars, int *pass_chars_len){
  // get the previous pass_chars_len
  int prev_pass_chars_len = *pass_chars_len;
  // Resize pass_chars so it can fit the chars_array
  *pass_chars_len += chars_array_len;
  pass_chars = realloc(pass_chars, *pass_chars_len);
  // Append the chars_array to the pass_chars
  for (int i = 0; i < chars_array_len; i++) {
    pass_chars[i + prev_pass_chars_len - 1] = chars_array[i];
  }
}
