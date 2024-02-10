#include <stdlib.h>
#include <string.h>

// USAGE: char* decoded_text = hex_decode(encoded_text);
char* hex_decode(char* hex)
{
  int len = strlen(hex);
  int decoded_byte = 0;
  char* decoded_text = malloc((len/2) * sizeof(char));
  
  // ITERATE THROUGH THE ENCODED STRING IN PAIRS
  for(int i = 0; i < len; i += 2){
    // IF THE FIRST CHAR IS IN RANGE 0-9
    // GET THE DIFFERENCE BETWEEN THE CHAR AND 48 
    // (0 = 48, 9 = 57) THIS MAKE SURES THE STRING "0" EQUAL TO THE REAL ZERO)
    // MULTIPLY THE RESULT BY 16 TO GET ORIGINAL DECIMAL VALUE;
    // ADD THE DECIMAL VALUE AT THE END
    if(hex[i] > 47 && hex[i] < 58){
      decoded_byte += (hex[i] - 48) * 16;
    // IF ITS NOT IN RANGE 0-9, THEN I ASSUME IS IN RANGE a-f (ONLY ACCEPT LOWERCASE HEX ENCODED STRINGS)
    // GET THE DIFFERENCE BETWEEN THE CHAR AND 87
    // (97 = a, z = 122)  I WANT a TO BE EQUAL TO 10 (a=10,b=11,...,f=15)
    // MULTIPLY THE RESULT BY 16 TO GET ORIGINAL DECIMAL VALUE;
    // ADD THE DECIMAL VALUE AT THE END
    } else {
      decoded_byte += (hex[i] - 87) * 16;
    }

    // IF THE SECOND CHAR IS IN RANGE 0-9
    // GET THE DIFFERENCE BETWEEN THE CHAR AND 48 
    // (0 = 48, 9 = 57) THIS MAKE SURES THE STRING "0" EQUAL TO THE REAL ZERO)
    // ADD THE DECIMAL VALUE AT THE END
    if(hex[i+1] > 47 && hex[i+1] < 58){
      decoded_byte += (hex[i+1] - 48);
    // IF ITS NOT IN RANGE 0-9, THEN I ASSUME IS IN RANGE a-f (ONLY ACCEPT LOWERCASE HEX ENCODED STRINGS)
    // GET THE DIFFERENCE BETWEEN THE CHAR AND 87
    // (97 = a, z = 122)  I WANT a TO BE EQUAL TO 10 (a=10,b=11,...,f=15)
    // ADD THE DECIMAL VALUE AT THE END
   } else {
      decoded_byte += (hex[i+1] - 87);
    }

    // CONCATENATE THE FOUND ORIGINAL BYTE AND ZERO THE VARIABLE FOR THE LOOP
    strncat(decoded_text, (char*)&decoded_byte, 1);
    decoded_byte = 0;
  }
  return decoded_text;
}

// USAGE: char* encoded_text = hex_encode(plaintext);
char* hex_encode(char* pt)
{
  int len = strlen(pt);
  char encoded_byte[2];
  char* encoded_text = malloc((len * 2) * sizeof(char));

  // ITERATE THROUGH THE PLAINTEXT
  // 1 PLAINTEXT CHAR EQUALS 2 HEX ENCODED CHARS "A" = "41"
  for(int i = 0; i < len; i++){
    // DIVIDE THE DECIMAL VALUE OF CHAR BY 16 AND CHECK IF IS IN RANGE 0-9
    // GET THE RESULT OF DIVISION AND ADD 48 (DECIMAL VALUE OF "0") TO GET THE ORIGINAL NUMBER 
    // ASSIGN VALUE TO CHAR TO CONCATENATE LATER
    if(pt[i]/16 < 10){
      encoded_byte[0] = (pt[i] / 16) + 48;
    // IF NOT IN RANGE 0-9, THEN ASSUME IS IN RANGE a-f (10-15)
    // GET THE RESULT OF DIVISION AND ADD 87 (DECIMAL VALUE OF "a" - 10) TO GET THE ORIGINAL NUMBER 
    // ASSIGN VALUE TO CHAR TO CONCATENATE LATER
    } else{
      encoded_byte[0] = (pt[i] / 16) + 87;
    }

    // DIVIDE THE DECIMAL VALUE OF CHAR BY 16 AND CHECK IF MODULO IS IN RANGE 0-9
    // GET THE RESULT OF MODULO AND ADD 48 (DECIMAL VALUE OF "0") TO GET THE ORIGINAL NUMBER 
    // ASSIGN VALUE TO CHAR TO CONCATENATE LATER
    if(pt[i]%16 < 10){
      encoded_byte[1] = (pt[i] % 16) + 48;
    // IF NOT IN RANGE 0-9, THEN ASSUME IS IN RANGE a-f (10-15)
    // GET THE RESULT OF MODULO AND ADD 87 (DECIMAL VALUE OF "a" - 10) TO GET THE ORIGINAL NUMBER 
    // ASSIGN VALUE TO CHAR TO CONCATENATE LATER
    } else{
      encoded_byte[1] = (pt[i] % 16) + 87;
    }

    strncat(encoded_text, encoded_byte, 2);

  }
  return encoded_text;
}
