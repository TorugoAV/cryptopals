typedef struct {
  char key;
  double value;
} freq;

typedef struct {
  char* ct;
  char* pt;
  double score;
  int key;
} decoded_ct;

int is_plaintext(char* buffer, int buffer_size);
double score_buffer(char* buffer, int buffer_size);
char* xor_single_byte(char* buffer, int buffer_size, int key);
void update_top_X_decoded_ct(decoded_ct* top_X_decoded_ct, int top_X, decoded_ct* decoded_ct_array, int array_size);
