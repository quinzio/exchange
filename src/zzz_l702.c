/*
 ============================================================================
 Name        : zzz_l702.c
 Author      : md
 Version     :
 Copyright   : SPAL
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define NFILE 5

struct fn_s {
  char fninp[1024];
  char fnout[1024];
} fn[NFILE];

void *worker(void * fn_p);

int main(int argc, char *argv[]) {
  int i;
  struct fn_s fn[NFILE];
  pthread_t tid[NFILE];

  if (argc != 4) {
    fprintf(stderr, "Bad arguments number\n");
    exit(-1);
  }
  for (i = 0; i < NFILE; i++) {
    sprintf(fn[i].fninp, "%s%d.txt", argv[2], i);
    sprintf(fn[i].fnout, "%s%d.txt", argv[3], i);
  }

  for (i = 0; i < NFILE; i++) {
    pthread_create(tid, 0, worker, (void *)&fn[i]);
  }

  return EXIT_SUCCESS;
}

void *worker(void * fn_p) {
  int fd;
  char str1[1024];
  char *p_str1;
  int n;
  int *vett, swaph;
  int i, j;
  struct fn_s fna;

  fna = *((struct fn_s *)fn_p);
  fd = open(fna.fninp, O_RDONLY, 0);
  p_str1 = str1;
  do {
    read(fd, p_str1++, sizeof(char));
  } while (*(p_str1 - 1) != 0x0a);
  *(p_str1 - 1) = 0;
  n = atoi(str1);
  vett = (int *)malloc(n * sizeof(int));
  for (i = 0; i < n; i++) {
    p_str1 = str1;
    do {
      read(fd, p_str1++, sizeof(char));
    } while (*(p_str1 - 1) != 0x0a);
    *(p_str1 - 1) = 0;
    vett[i] = atoi(str1);
  }
  close(fd);
  // do insertion sort
  for (i = 1; i < n; i++) {
    if (vett[i - 1] > vett[i]) {
      for (j = i; j > 0; j--) {
        if (vett[j - 1] <= vett[j]) break;
        swaph = vett[j];
        vett[j] = vett[j - 1];
        vett[j - 1] = swaph;
      }
    }
  }
  sprintf(str1, "%d", n);
  fd = open(fna.fnout, O_CREAT | O_TRUNC | O_WRONLY, 0666);
  j = strlen(str1);
  p_str1 = str1;
  for (i = 0; i < j; i++) write(fd, p_str1++, sizeof(char));
  write(fd, "\x0a", sizeof(char));
  close(fd);
  free(vett);

  return 0;
}