#include "../../src/hex.h"
#include "../../src/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// GET THE LINE SIZE OF A FILE
int get_line_size(FILE *fptr)
{
  int count = 0;
  int i = fgetc(fptr);

  // DO WHILE NOT REACHED A LINE BREAK OR THE END OF THE FILE
  while (!feof(fptr) && i != '\n') {

    // DO READ NEXT CHAR
    i = fgetc(fptr);

    // DO INCREASE THE LINE SIZE
    count++;
  }
  return count;
}

int main ()
{
  FILE *fptr = fopen("4.txt", "r");
  int line_size = get_line_size(fptr);
  char **hex_ct_array = malloc(0);
  int hex_ct_array_index = 0;
  char *hex_ct = malloc(line_size + 1);
  char *ct = malloc(line_size/2);
  char *pt;
  decoded_ct* possible_pt_array = malloc(0);
  decoded_ct* top_X_decoded_ct = malloc(0);
  int possible_pt_array_index = 0;
  int top_X = 3; 

  
  rewind(fptr);

  // DO ALLOC MEMORY TO THE TOP X ARRAY
  for (int i = 0; i < top_X; i++) {
    top_X_decoded_ct = reallocarray(top_X_decoded_ct, top_X, sizeof(decoded_ct));
  }
  
  // DO WHILE NOT REACHED THE END OF THE FILE
  while (!feof(fptr)) {
    
    // DO INCREASE THE SIZE OF HEXES
    hex_ct_array = reallocarray(hex_ct_array, hex_ct_array_index + 1, sizeof(char *));

    // DO CREATE POINTER TO STORE THE STRING
    hex_ct_array[hex_ct_array_index] = malloc(line_size + 2);

    // DO READ ONE LINE THE FILE TO PREVIOUSLY CREATED POINTER
    fgets(hex_ct_array[hex_ct_array_index], line_size + 2, fptr);

    // DO REMOVE THE NEWLINE FROM THE LINE READ
    hex_ct_array[hex_ct_array_index][strcspn(*hex_ct_array, "\n")] = 0;
    hex_ct_array_index++;
  }

  // MAGIC HAPPENS HERE
  // DO LOOP THROUGH EVERY STRING THAT WAS READ FROM THE FILE TO THE ARRAY
  for (int i = 0; i < hex_ct_array_index; i++){

    // DO COPY THE HEX DECODED VALUE TO CT, NEED TO USE MEMCPY BECAUSE OF NULLBYTE AND OTHER BAD CHARS
    memcpy(ct, hex_decode(hex_ct_array[i]), line_size/2);

    // DO LOOP THROUGH EVERY POSSIBLE KEY
    for (int key = 0; key < 256; key++) {

      // DO XOR THE CIPHERTEXT
      pt = xor_single_byte(ct, line_size/2, key);

      // DO IF THE XOR RESULT IS ALL PLAINTEXT
      if (is_plaintext(pt, line_size/2)) {

        // DO UPDATE THE UNSORTED RESULTS ARRAY
        possible_pt_array = reallocarray(possible_pt_array, possible_pt_array_index + 1, sizeof(decoded_ct));
        possible_pt_array[possible_pt_array_index].ct = hex_ct_array[i];
        possible_pt_array[possible_pt_array_index].pt = pt;
        possible_pt_array[possible_pt_array_index].score = score_buffer(pt, line_size/2);
        possible_pt_array[possible_pt_array_index].key = key;
        possible_pt_array_index++;
      }
    }
  }
  
  // DO SORT AND UPDATE FINAL ARRAY OF RESULTS
  update_top_X_decoded_ct(top_X_decoded_ct, top_X, possible_pt_array, possible_pt_array_index - 1);

  // DO PRINT THE RESULTS
  for (int i = 0; i < top_X; i++){
    printf("Original cipher text: %s\n", top_X_decoded_ct[i].ct);
    printf("Decoded string: %s\n", top_X_decoded_ct[i].pt);
    printf("Score: %f\n", top_X_decoded_ct[i].score);
    printf("XOR Key: %x (Hex)\n", top_X_decoded_ct[i].key);
    printf("-------------------------------\n");
  }

  return 0;
}
