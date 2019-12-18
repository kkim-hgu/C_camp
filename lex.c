//Isiah Slater
//This program lexicographically sorts a given text file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 32
#define MAX_LINE_LEN 256
#define TRUE 1
#define FALSE 0

//word_t stores a c-string and a number representing the quantity of that word
typedef struct word
{
  char the_word[MAX_WORD_LEN];
  int count;
} word_t;

//void sort array sorts an array of word_t variables
  //based on the ASCII value of the word stored
//int word_list_size the size of the current array
//word_t *word_list the array being sorted
void sort_array(int word_list_size, word_t *word_list);

//void read_file sorts the lines into tokens
//int *word_list_size the size of the space being occupied within the array
//FILE *f the file being read from
void read_file(int *word_list_size, word_t *word_list, FILE *f);

//void add_word reads the tokens and stores it into an array
//int *word_list_size the occupied space inside the array
//word_t *word_list the array the words are stored into
//char *token_word the token taken from the input text file
void add_word (int *word_list_size, word_t *word_list, char *token_word);

//void print_array prints the array information to the terminal
//int word_list_size the occupied size of the array
//word_t *word_list the array being printed to the terminal
void print_array(int word_list_size, word_t *word_list);
void print_result(int word_list_size, word_t *word_list);

int main(int argc, char*argv[])
{
  /* attempt to open file */
  char* filename = argv[1];
  FILE *f = fopen(filename, "r");
  if(f == NULL)
    {
      printf("Failed to open %s\n", filename);
      exit(-1);
    }
  
  /* initialize variables */
  word_t word_list[MAX_WORDS];
  int word_list_size = 0;
 
  /* break down the lines of text to tokens and write said tokens into word_list */
  read_file(&word_list_size, word_list,f);	  
  /* sort array into proper order */
  sort_array(word_list_size, word_list); 
  /* print list to the terminal*/
  //print_array(word_list_size, word_list);
  print_result(word_list_size, word_list);
}

void sort_array(int word_list_size, word_t *word_list)
{
  int loop_count;
  int array_count;
  word_t temp_word;
  for(loop_count = 0; loop_count < word_list_size; loop_count++)
    {
    for(array_count = 0; array_count < word_list_size - 1; array_count++)
    {
      if(strcmp((word_list + array_count)->the_word, (word_list + array_count + 1)->the_word) > 1)
        {
          temp_word = *(word_list + array_count);
          *(word_list + array_count) = *(word_list + array_count + 1);
          *(word_list + array_count + 1) = temp_word;
        }
    }
  }
}

void read_file(int *word_list_size, word_t *word_list, FILE *f)
{
  char *token_word;
  int array_count;
  int has_been_added = FALSE;
  char input_words[MAX_LINE_LEN];
  char *result = fgets(input_words, MAX_LINE_LEN, f);
  char delimeters[] = " \t-\n.,?\"'";
  
  while(result != NULL)
  {
    token_word = strtok(result, delimeters);
    add_word(word_list_size, word_list, token_word);

    while((token_word = strtok(NULL, delimeters)) != NULL)
    {
      add_word(word_list_size, word_list, token_word);
    }

    result = fgets(input_words, MAX_LINE_LEN, f);
  }
}

void add_word (int *word_list_size, word_t *word_list, char *token_word)
{
  int array_count;
  int has_been_added = FALSE;
 
  for(array_count = 0; array_count < *word_list_size; array_count++)
  {
    if(strcmp(token_word, (word_list + array_count)->the_word) == 0 && !has_been_added)
    {
      ((word_list + array_count)->count)++;
      has_been_added = TRUE;
    }
  }
  if(!has_been_added)
    {
      strcpy((word_list + *word_list_size)->the_word, token_word);
      (word_list + *word_list_size)->count++;
      *word_list_size += 1;
    }
  has_been_added = FALSE; 
}

void print_array(int word_list_size, word_t *word_list)
{
  int array_count;
  for(array_count = 0; array_count < word_list_size; array_count++)
    {
      printf("%s:\t%d\n", word_list[array_count].the_word, word_list[array_count].count);
    }
}

void print_result(int word_list_size, word_t *word_list)
{
  int array_count;
  int max_index, max=0;

  for (array_count = 0; array_count < word_list_size; array_count++)
  {
    if (word_list[array_count].count > max)
    {
      max = word_list[array_count].count;
      max_index = array_count;
    }
    if (word_list[array_count].count > 10)
      printf("%s:\t%d\n", word_list[array_count].the_word, word_list[array_count].count);
  }

  printf("Most used word : %s\n", word_list[max_index].the_word);
}
