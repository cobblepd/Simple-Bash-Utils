#include "s21_cat.h"

int main(int argc, char *argv[]) {
  Flags flags = ReadFlags(argc, argv);
  CatOutput(argc, argv, flags);
  return 0;
}

Flags ReadFlags(int argc, char *argv[]) {
  int currentFlag;
  int long_ingex = 0;
  struct option const longOptions[] = {{"number-nonblank", 0, NULL, 'b'},
                                       {"number", 0, NULL, 'n'},
                                       {"squeeze-blank", 0, NULL, 's'},
                                       {NULL, 0, NULL, 0}};
  Flags flags = {0, 0, 0, 0, 0, 0};
  while ((currentFlag = getopt_long(argc, argv, "bevEnstT", longOptions,
                                    &long_ingex)) != -1) {
    switch (currentFlag) {
      case 'b':
        flags.bF = 1;
        break;
      case 'e':
        flags.vF = 1;
        flags.eF = 1;
        break;
      case 'v':
        flags.vF = 1;
        break;
      case 'E':
        flags.eF = 1;
        break;
      case 'n':
        flags.nF = 1;
        break;
      case 's':
        flags.sF = 1;
        break;
      case 't':
        flags.vF = 1;
        flags.tF = 1;
        break;
      case 'T':
        flags.tF = 1;
        break;
    }
    if (flags.bF == 1) {
      flags.nF = 0;
    }
  }
  return flags;
}

int SqueezeBlank(int *buf, int *prev_ch, int *second_ch) {
  int count = 0;
  if (*buf == '\n' && *prev_ch == '\n' &&
      (*second_ch == '\n' || *second_ch == '\0')) {
    ++count;
  }
  return count;
}

void ChangeSymbol(int *buf, Flags flags) {
  if (flags.eF && *buf == '\n') {
    printf("$");
  }
  if (flags.tF && *buf == '\t') {
    printf("^");
    *buf = 'I';
  }
  if (*buf < 32 && *buf != '\n' && *buf != '\t') {
    printf("^");
    *buf += 64;
  }
  if (*buf == 127) {
    printf("^");
    *buf -= 64;
  }
  if (*buf > 127) {
    printf("M-");
    if (*buf >= 160 && *buf < 255) {
      *buf -= 128;
    } else {
      printf("^");
      *buf = *buf - 64;
    }
  }
}

void CatOutput(int argc, char *argv[], Flags flags) {
  int buf, prev_ch = -1, second_ch, count_s;
  unsigned int count_str = 1;
  for (; optind < argc; optind++) {
    FILE *file = fopen(argv[optind], "rb");
    if (file != NULL) {
      while ((buf = fgetc(file)) != EOF) {
        if (flags.sF) {
          count_s = SqueezeBlank(&buf, &prev_ch, &second_ch);
          if (count_s != 0) {
            continue;
          }
        }
        if (flags.bF && ((prev_ch == '\n' && buf != '\n') ||
                         (count_str == 1 && buf != '\n'))) {
          printf("%6d\t", count_str);
          ++count_str;
        }
        if (flags.nF && (prev_ch == '\n' || count_str == 1)) {
          printf("%6d\t", count_str);
          ++count_str;
        }
        if (flags.tF || flags.eF || flags.vF) {
          ChangeSymbol(&buf, flags);
        }
        second_ch = prev_ch;
        prev_ch = buf;
        putchar(buf);
      }
      fclose(file);
    } else {
      printf("s21_cat: No such file or directory\n");
    }
    prev_ch = -1;
  }
}
