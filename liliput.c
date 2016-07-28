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


void saveRow(int curRow, char *line, size_t length) {
  if (curRow > settingsInstance.numRows)
    return;
  // Might have to use realloc
  settingsInstance.row = malloc(settingsInstance.row, (sizeof(rowInstance)*settingsInstance.numRows + 1));

  settingsInstance.row[curRow].

}

void openFile(char *file) {
    FILE *fp;
    settingsInstance.fileModified = false;
    settingsInstance.filename = file;
    fp = fopen(file, "r");
    if(fp == NULL) {
      fprintf(stderr, "Err: Couldn't open file Code: <%d> \n", errno);
      exit(1);
    }

    //TODO : Add else block where file is created if it doesn't exist

    char *line = NULL;
    size_t linecap = 0;
    ssize_t lineLength = 0;
    while((lineLength = getline(&line, &linecap, fp)) != -1) {

      // \n is standard new line
      // \r is newline on older mac systems
      // \r\n is new line on some windows versions. Not sure. Just following stack overflow here
      // I don't need to do this as get Line covers breaking up lines in new line chars
      // I suspect I cant use getDelim to make this check redundant. But Meh.
      if(lineLength && (line[lineLength -1] == '\n' || line[lineLength -1] == '\n' || line[lineLength -1] == '\r\n'))
        line[lineLength--] = '\0';
      saveRow(settingsInstance.numRows, line, lineLength);

    }

    free(line);
    fclose(fp);
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
