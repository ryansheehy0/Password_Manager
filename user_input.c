#include <stdlib.h>
#include <stdio.h>

char *get_input(){
  char *input_str = malloc(sizeof(char));
  if(input_str == NULL){
    return NULL;
  }

  int c;
  int i = 0;
  while((c = getchar()) != '\n' && c != EOF){
    input_str[i] = c;
    input_str = realloc(input_str, (i+2) * sizeof(char));
    if(input_str == NULL){
      free(input_str);
      return NULL;
    }
    i++;
  }
  input_str[i] = '\0';
  return input_str;
}

char *autocomplete_get_input(){
  return NULL;
}
