// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains declaration of class-wrapper File
// for storing conversation history to file.
//
#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <string.h>

class File {
 public:
  explicit File(const char *filename);
  ~File();
  void Write(const char *str);
  void Refresh(void);
  bool IsValid(void) const;

 private:
  FILE *pFile_;
  char *filename_;
};

#endif // !FILE_H_