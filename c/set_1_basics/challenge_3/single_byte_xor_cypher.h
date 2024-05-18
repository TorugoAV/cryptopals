typedef struct {
  char key;
  double value;
} freq;

typedef struct {
  char* pt;
  double score;
  int key;
} decoded_ct;

int is_plaintext(char* buffer);
double score_buffer(char* buffer);
char* xor_single_byte_bruteforce(char* buffer, int buffer_size, int key);
void update_top_X_decoded_ct(decoded_ct* top_X_decoded_ct, int top_X, decoded_ct* decoded_ct_array, int array_size);
