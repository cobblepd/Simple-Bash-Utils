#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char pattern[4096];
  Flags flags = {0};
  ReadFlags(&argc, argv, pattern, &flags);
  Grep(argc, argv, pattern, flags);
}

void ReadFlags(int *argc, char *argv[], char pattern[], Flags *flags) {
  int currentFlag;
  while ((currentFlag = getopt_long(*argc, argv, "e:ivclnhsof", NULL, NULL)) !=
         -1) {
    switch (currentFlag) {
      case 'e':
        flags->eF = 1;
        if (!pattern[0]) {
          strcat(pattern, optarg);
        } else {
          strcat(pattern, "|");
          strcat(pattern, optarg);
        }
        break;
      case 'i':
        flags->iF = 1;
        break;
      case 'v':
        flags->vF = 1;
        break;
      case 'c':
        flags->cF = 1;
        break;
      case 'l':
        flags->lF = 1;
        break;
      case 'n':
        flags->nF = 1;
        break;
      case 'h':
        flags->hF = 1;
        break;
      case 's':
        flags->sF = 1;
        break;
      case 'o':
        flags->oF = 1;
        break;
    }
  }
  if (flags->eF && optind + 1 < *argc) {
    flags->count_files = 1;
  }
  if (optind + 2 < *argc) {
    flags->count_files = 1;
  }
  if (flags->lF) {
    flags->vF = 0;
  }
}

void Grep(int argc, char *argv[], char pattern[], Flags flags) {
  char buf[4096];
  int flag = REG_EXTENDED, len = 0, count_str = 0, result = 0, stoper = 0,
      count_str_nF = 1;
  regex_t regex;
  if (flags.iF) {
    flag = REG_ICASE;
  }
  if (flags.eF) {
    regcomp(&regex, pattern, flag);
  } else {
    regcomp(&regex, argv[optind], flag);
    optind++;
  }
  for (; optind < argc; optind++) {
    FILE *file = fopen(argv[optind], "rb");
    if (file != NULL) {
      while (fgets(buf, 4096, file) != NULL && stoper == 0) {
        count_str = PrintRegex(count_str, &result, regex, len, argv, &stoper,
                               &count_str_nF, buf, flags);
        count_str_nF++;
      }
      if (flags.cF) {
        PrintOnlyString(argv, &count_str, flags);
      }
      stoper = 0;
      count_str_nF = 1;
      fclose(file);
    }
    if (file == NULL) {
      printf("s21_grep: No such file or directory\n");
    }
  }
  regfree(&regex);
}

void PrintMatch(char *argv[], int *stopper, int *count_str_nF, char *buf,
                Flags flags) {
  if (flags.nF && *stopper == 0) {
    if (flags.count_files) {
      printf("%s:", argv[optind]);
    }
    printf("%d:%s\n", *count_str_nF, buf);
  }
  if (flags.hF && flags.cF == 0) {
    printf("%s\n", buf);
  }
  if (flags.count_files && !flags.cF && !flags.nF && !flags.hF) {
    printf("%s:", argv[optind]);
  }
  if (!flags.cF && !flags.nF && !flags.hF && flags.oF == 0) {
    printf("%s\n", buf);
  }
}
void PrintOnlyString(char *argv[], int *count_str, Flags flags) {
  if (flags.count_files && flags.hF == 0) {
    printf("%s:", argv[optind]);
  }
  printf("%d\n", *count_str);
  *count_str = 0;
}
void print_vF(char *argv[], char *buf, Flags flags) {
  if (flags.vF) {
    if (flags.count_files && flags.cF == 0) {
      printf("%s:", argv[optind]);
    }
    if (flags.cF == 0) {
      printf("%s\n", buf);
    }
  }
}

int PrintRegex(int count_str, int *result, regex_t regex, int len, char *argv[],
               int *stopper, int *count_str_nF, char *buf, Flags flags) {
  *result = regexec(&regex, buf, 0, NULL, 0);
  len = strlen(buf);
  if (buf[len - 1] == '\n') {
    buf[len - 1] = '\0';
  }
  if (*result) {
    print_vF(argv, buf, flags);
  }
  if (!(*result) && flags.vF == 0) {
    if (flags.lF) {
      printf("%s\n", argv[optind]);
      *stopper = 1;
    }
    if (*stopper == 0) {
      PrintMatch(argv, stopper, count_str_nF, buf, flags);
    }
    count_str++;
  }
  if (flags.vF && *result) {
    count_str++;
  }
  return count_str;
}
