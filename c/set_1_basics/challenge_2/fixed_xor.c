#include "../../src/hex.h"
#include <stdio.h>
#include <string.h>

int main ()
{
  char challenge_result[] = {"746865206b696420646f6e277420706c6179"};
  char hex_1[] = {"1c0111001f010100061a024b53535009181c"};
  char hex_2[] = {"686974207468652062756c6c277320657965"};
  char hex_dec_1[19] = {};
  char hex_dec_2[19] = {};
  char xor_result[19] = {};
  char* xor;

  // DECODE GIVEN VALUES
  memcpy(hex_dec_1, hex_decode(hex_1), 18);
  memcpy(hex_dec_2, hex_decode(hex_2), 18);

  // XOR THE TWO VALUES AND STORE THE RESULT IN CHARARRAY
  for(int i = 0; i <= 18; i++) {
    xor_result[i] = hex_dec_1[i] ^ hex_dec_2[i];
  }

  // ENCODE RESULT FOR CHALLENGE VALIDATION LATER
  xor = hex_encode(xor_result);

  // PRETTY PRINTING
  printf("Decoded key: %s\n", hex_dec_2);
  printf("Decoded string: %s\n", xor_result);
  
  if(memcmp(challenge_result, xor, sizeof(challenge_result)) == 0) {
    printf("Success!!! Challenge completed.\n");
  }
  
  return 0;
}
