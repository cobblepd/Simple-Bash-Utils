#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
  bool bF;
  bool eF;
  bool vF;
  bool nF;
  bool sF;
  bool tF;
} Flags;

Flags ReadFlags(int argc, char *argv[]);
int SqueezeBlank(int *buf, int *prev_ch, int *second_ch);
void ChangeSymbol(int *buf, Flags flags);
void CatOutput(int argc, char *argv[], Flags flags);