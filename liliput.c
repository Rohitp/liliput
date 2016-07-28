#define true 1
#define false 0

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

extern int errno;

struct row {
  int rowIndex;
  int rowSize; //Excluding null term. I think.
  int renderedSize;
  char *rowString;

}rowInstance;


//For syntaax highlighting
struct Colour {
  int r,g,b;
} colorInstance;


struct Settings {
  int cursorX;
  int cursorY;
  int rowOffset;
  int colOffset;
  int numRows;
  int screenrows;
  int screencols;
  char *filename; //Open filename
  int fileModified; //Boolean. Checks if file is modified but not saved
  struct row *row;
} settingsInstance;

void openFile(char *file) {
    FILE *fp;
    settingsInstance.fileModified = false;
    settingsInstance.filename = file;
    fp = fopen(file, "r");
    if(fp == NULL) {
      fprintf(stderr, "Err: Couldn't open file Code: <%d> \n", errno);
      exit(1);
    }

    char *line = NULL;
    size_t linecap = 0;
    ssize_t lineLength = 0;
    while(getline(&line, &linecap, fp) != -1) {
      printf("%s", line);
    }

    free(line);
    free(fp);
    settingsInstance.fileModified = true;
}

void init() {
    //initialise settings struct
    settingsInstance.cursorX = 0;
    settingsInstance.cursorY = 0;
    settingsInstance.rowOffset = 0;
    settingsInstance.colOffset = 0;
    settingsInstance.numRows = 0;
    settingsInstance.fileModified = false;
    settingsInstance.filename = NULL;
    settingsInstance.row = NULL;
}

int main(int argc, char **argv) {
    if(argc != 2) {
      //fprintf to stderr because we need to keep stdout as clean as possible
      fprintf(stderr, "Usage: liliput <filename> \n");
      exit(1);
    }
    init();
    openFile(argv[1]);
    // printf("Hello world \n");
    return 0;
}
