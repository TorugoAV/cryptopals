#include <stdlib.h>
#include <string.h>

// USAGE: char* decoded_text = base64_decode(encoded_text);
char* base64_decode(char* ct) 
{
  int padding;
  int mask[] = {16711680, 65280, 255}; // MASK EQUIVALLENT TO 111111110000000000000000 000000001111111100000000 000000000000000011111111
  int ct_length = strlen(ct);
  int rounds = ct_length / 4;
  char Base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  char decoded_byte;
  char* decoded_text = malloc((rounds * 3) * sizeof(char));
  
  // CHECK AND SET PADDING TO NULLBYTE
  if(ct[ct_length - 1] == '='){
    padding = 1;
    ct[ct_length - 1] = '\0';
    if(ct[ct_length - 2] == '='){
      padding = 2;
      ct[ct_length - 2] = '\0';
    }
  }

  // GET 4 BYTES AND THEIR INDEX AT BASE64 DICT; CONCATENATE THE 4 INDEX NUMBERS SHIFTING BYTES (4 BASE64 BYTES = 3 UTF ENCODED BYTES)
  for(int i = 0; i < rounds; i++){
    int concatenated_ciphertext = ((int)(strchr(Base64, ct[i*4]) - Base64) << 18) + ((int)(strchr(Base64, ct[i*4+1]) - Base64) << 12) + ((int)(strchr(Base64, ct[i*4+2]) - Base64) << 6) + ((int)(strchr(Base64, ct[i*4+3]) - Base64));
    // FOR A GIVEN CONCATENATION, DO A LOGICAL AND WITH A FIXED MASK, SHIFT BYTES RIGHT TO GET ORIGINAL PLAINTEXT
    for(int j = 0; j < 3; j++) {
      decoded_byte = (concatenated_ciphertext & mask[j]) >> 8 * (j - 2) * -1;
      strncat(decoded_text, &decoded_byte, 1);
    }
  }
  
  // IF PADDED, LAST BYTES MIGHT BE WRONG, DO MANUAL CLEANING
  if(padding > 0 ){
    decoded_text[rounds*3-1] = '\0';
    if(padding > 1){
      decoded_text[rounds*3-2] = '\0';
    }
  }
  return decoded_text;
}

// USAGE: char* encoded_text = base64_encode(plaintext);
char* base64_encode(char* pt) 
{
  int mask[] = {16515072, 258048, 4032, 63}; // Mask equivallent to 111111000000000000000000 000000111111000000000000 000000000000111111000000 000000000000000000111111
  int pt_length = strlen(pt);
  int rounds = pt_length / 3;
  int padding = pt_length % 3;
  char Base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  char encoded_byte;
  char* encoded_text = malloc((rounds * 4 + padding) * sizeof(char));
  
  // CONCATENATE 3 BYTES INTO 1 INT 10001000 10101010 11110000 SHIFTING BYTES
  for(int i = 0; i < rounds; i++) {
    int concatenated_plaintext = (pt[i*3] << 16) + (pt[i*3+1] << 8) + pt[i*3+2];
  // DO A LOGICAL AND AGAINST THE MASK, SHIFT THE BYTES AND DO LOOKUP INTO BASE64 ALPHABET TO GET CORRECT CHAR
    for(int j = 0; j < 4; j++){
      encoded_byte =  Base64[(concatenated_plaintext & mask[j]) >> 6 * (j - 3) * -1];
      strncat(encoded_text, &encoded_byte, 1);
    }
  }
  
  // IF THE STRING NEEDS PADDING, CHECK WETHER IS 1 '=' OR 2 '=' AND DO THE SAME PROCESS AS BEFORE  
  if(padding == 1){
    int concatenated_plaintext = (pt[pt_length -1] << 16);
    for(int j = 0; j < 2; j++){
      encoded_byte =  Base64[(concatenated_plaintext & mask[j]) >> 6 * (j - 3) * -1];
      strncat(encoded_text, &encoded_byte, 1);
    }
    strcat(encoded_text, "==");
  }

  if(padding == 2){
    int concatenated_plaintext = (pt[pt_length - 2] << 16) + (pt[pt_length - 1] << 8);
    for(int j = 0; j < 3; j++){
      encoded_byte =  Base64[(concatenated_plaintext & mask[j]) >> 6 * (j - 3) * -1];
      strncat(encoded_text, &encoded_byte, 1);
    }
    strcat(encoded_text, "=");
  }
  return encoded_text;
}
