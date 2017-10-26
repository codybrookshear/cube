#ifndef PUZZLEFILE_H
#define PUZZLEFILE_H

class PuzzleFile
{
public:
  virtual ~PuzzleFile();
  void loadFile(char *filename);
  char *getNext();
  char *getFirst();
  char *getCurrent();

private:
  char *buf;
  int fsize;
  char *line;
};

#endif // PUZZLEFILE_H
