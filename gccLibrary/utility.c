#include <stdio.h>
#include <stdlib.h>


// for open function
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Utility library

/* */
void setbuf (FILE *fp, char *buf);
int fflush (FILE *fp);


int getc (FILE *fp);
int fgetc (FILE *fp);
int putc (int c, FILE *fp);
int fputc (int c, FILE *fp);
char *gets (char *buf);
char *fgets (char *buf, int n, FILE *fp);
int puts (char *buf);
int fputs (char *buf, FILE *fp);


int scanf (char format);
int fscanf (FILE *fp, char format);
int printf (char format);
int fprintf (FILE *fp, char format);

// Files
FILE *fopen (char *path, char *type);
FILE *fclose (FILE *fp);

// Structures
size_t fread (void *ptr, size_t size, size_t nObj, FILE *fp);
size_t fwrite (void *ptr, size_t size,size_t nObj, FILE *fp);
size_t fread (void *ptr, size_t size, size_t nObj, FILE *fp);
size_t fwrite (void *ptr, size_t size, size_t nObj, FILE *fp);

/* 
int open(const char *path, int flags);
int open2 (const char *path, int flags, mode_t mode);
*/