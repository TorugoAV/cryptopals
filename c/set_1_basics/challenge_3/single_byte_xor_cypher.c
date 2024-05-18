#include "../../src/hex.h"
#include "single_byte_xor_cypher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DO CHECK IF A BUFFER IS PLAINTEXT
int is_plaintext(char* buffer)
{
  for (int i = 0; i < sizeof(buffer); i++){
    if ( buffer[i] < 32 || buffer[i] > 126){
      return 0;
    }
  }
  return 1;
}

// DO SCORE A BUFFER BASED ON ENGLISH FREQUENCY ANALISYS
double score_buffer(char* buffer)
{
  freq char_freq[] = {{' ', 18.74}, {'E', 9.60}, {'T', 7.02}, {'A', 6.21}, {'O', 5.84}, {'I', 5.22}, {'N', 5.21}, {'H', 4.87}, {'S', 4.77}, {'R', 4.43}, {'D', 3.52}, {'L', 3.20}, {'U', 2.25}, {'M', 1.94}, {'C', 1.88}, {'W', 1.82}, {'G', 1.66}, {'F', 1.62}, {'Y', 1.56}, {'P', 1.31}, {',', 1.24}, {'.', 1.21}, {'B', 1.19}, {'K', 0.74}, {'V', 0.71}, {'"', 0.67}, {'\'', 0.44}, {'-', 0.26}, {'?', 0.12}, {'X', 0.12}, {'J', 0.12}, {';', 0.08}, {'!', 0.08}, {'Q', 0.07}, {'Z', 0.07}, {':', 0.03}, {'1', 0.02}, {'0', 0.01}, {')', 0.01}, {'*', 0.01}, {'(', 0.01}, {'2', 0.01}, {'`', 0.01}, {'3', 0.01}, {'9', 0.01}, {'5', 0.01}, {'4', 0.01}};
  double score = 0;

  // DO LOOP THROUGH THE BUFFER
  for (int i = 0; i < sizeof(buffer); i++){

      // DO LOOP THROUGH THE FREQUENCY ARRAY
      for (int j = 0; j < sizeof(char_freq)/sizeof(*char_freq); j++){

        // IF FOUND BUFFER KEY IN ARRAY, SCORE GOES UP
        if ( buffer[i] == char_freq[j].key){
          score += char_freq[j].value;
          break;
      }
    }
  }
  return score;
}

// TAKES A BUFFER, THE BUFFER SIZE AND A KEY (1 byte)
// DO A SINGLE KEY XOR OPERATION AND RETURN A VALUE
char* xor_single_byte_bruteforce(char* buffer, int buffer_size, int key)
{
  // DO CREATE A EMPTY BUFFER
  char* decoded_buffer = calloc(buffer_size, sizeof(char));

  // DO LOOP THROUGH THE BUFFER AND XOR
  for (int i = 0; i < buffer_size; i++){
    decoded_buffer[i] = buffer[i] ^ key;
  }
  
  return decoded_buffer;
}

void update_top_X_decoded_ct(decoded_ct* top_X_decoded_ct, int top_X, decoded_ct* decoded_ct_array, int array_size)
{
  // DO LOOP THROUGH THE UNSORTED ARRAY
  for (int i = 0; i < array_size; i++){

    // GET THE TOP X
    for (int j = 0; j < top_X; j++){

      // IF THE SCORE IS HIGHER THAN ANY POSITION AND IT'S NOT THE LAST ITERATION, 1. DO COPY THE VALUE FROM TOP X TO NEXT POSITION; 2. DO REPLACE WITH NEW HIGHSCORE
	    if (decoded_ct_array[i].score > top_X_decoded_ct[j].score && j != top_X -1){
        
          // 1. DO COPY PREVIOUS HIGHSCORE TO THE NEXT POSITION
          top_X_decoded_ct[j+1].pt = top_X_decoded_ct[j].pt;
          top_X_decoded_ct[j+1].score = top_X_decoded_ct[j].score;
          top_X_decoded_ct[j+1].key = top_X_decoded_ct[j].key;
          
          // 2. DO REPLACE THE CURRENT POSITION WITH NEW HIGHSCORE
          top_X_decoded_ct[j].pt = decoded_ct_array[i].pt;
          top_X_decoded_ct[j].score = decoded_ct_array[i].score;
          top_X_decoded_ct[j].key = decoded_ct_array[i].key;

          // IF HIGHSCORE IS FOUND STOP SEARCHING THE TOP X ARRAY
          break;
        
      // IF THE SCORE OF THE LAST POSITION IS HIGHER, REPLACE WITH NEW HIGHSCORE
  	  } else if (decoded_ct_array[i].score > top_X_decoded_ct[j].score) {
          top_X_decoded_ct[j].pt = decoded_ct_array[i].pt;
	        top_X_decoded_ct[j].score = decoded_ct_array[i].score;
          top_X_decoded_ct[j].key = decoded_ct_array[i].key;
        }
    }
  }
}

int main ()
{
  char ct[] = {"1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"};
  char* pt;
  char dec_ct[sizeof(ct)/2] = {};
  decoded_ct* top_X_decoded_ct = malloc(0);
  decoded_ct* possible_pt_array = malloc(0);
  int possible_pt_array_index = 0;
  int top_X = 3; 
  
  // UPDATE THE SIZE OF THE TOP X RESULTS ARRAY
  for (int i = 0; i < top_X; i++) {
    top_X_decoded_ct = reallocarray(top_X_decoded_ct, top_X, sizeof(decoded_ct));
  }
  
  // GET HEX DECODED VALUE OF CT
  memcpy(dec_ct, hex_decode(ct), sizeof(dec_ct));

  // DO LOOP THROUGH EVERY POSSIBLE XOR KEY 1...255
  for (int i = 0; i<256; i++){
    // GET THE VALUE OF CT XOR KEY
    pt = xor_single_byte_bruteforce(dec_ct, sizeof(dec_ct), i);

    // UPDATE ARRAY IF THE XOR RESULT IS PLAINTEXT
    if(is_plaintext(pt)){
      possible_pt_array = reallocarray(possible_pt_array, possible_pt_array_index + 1, 24);
      possible_pt_array[possible_pt_array_index].pt = pt;
      possible_pt_array[possible_pt_array_index].score = score_buffer(pt);
      possible_pt_array[possible_pt_array_index].key = i;
      possible_pt_array_index++;
    }
  }
   
  // GET THE SORTED TOP X RESULTS
  update_top_X_decoded_ct(top_X_decoded_ct, top_X, possible_pt_array, possible_pt_array_index - 1);

  // DO PRINT THE RESULT ON SCREEN
  for (int i = 0; i < top_X; i++){
    printf("Decoded string: %s\n", top_X_decoded_ct[i].pt);
    printf("Score: %f\n", top_X_decoded_ct[i].score);
    printf("XOR Key: %x (Hex)\n", top_X_decoded_ct[i].key);
    printf("-------------------------------\n");
  }

  return 0;
}
