#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
typedef struct {
  bool eF;
  bool iF;
  bool vF;
  bool cF;
  bool lF;
  bool nF;
  bool hF;
  bool sF;
  bool fF;
  bool oF;
  bool count_files;
} Flags;

void ReadFlags(int *argc, char *argv[], char pattern[], Flags *flags);
int PrintRegex(int count_str, int *result, regex_t regex, int len, char *argv[],
               int *stopper, int *count_str_nF, char *buf, Flags flags);
void PrintMatch(char *argv[], int *stopper, int *count_str_nF, char *buf,
                Flags flags);
void PrintOnlyString(char *argv[], int *count_str, Flags flags);
void Print_vF(char *argv[], char *buf, Flags flags);
void Grep(int argc, char *argv[], char pattern[], Flags flags);
