#include "../../src/base64.h"
#include "../../src/hex.h"
#include <stdio.h>
#include <string.h>

int main() {
  char hex_encoded[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  char challenge_result[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
  char hex_decoded[49];
  char base64_encoded[65];
  strcpy(hex_decoded, hex_decode(hex_encoded));
  strcpy(base64_encoded, base64_encode(hex_decoded));
  printf("Hex encoded string: %s\n", hex_encoded);
  printf("Hex decoded string: %s\n", hex_decoded);
  printf("Base64 encoded string: %s\n", base64_encoded);
  if(strncmp(challenge_result, base64_encoded, sizeof(challenge_result)) == 0){
    printf("Success!!! Challenge completed.\n");
  }
  return 0;
}
