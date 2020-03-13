// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains implementation of class-wrapper File
// for storing conversation history to file.
//
#include "file.h"

File::File(const char *filename) {
  unsigned int length = strlen(filename) + 1;
  filename_ = new char[length];
  strcpy(filename_, filename);
  pFile_ = fopen(filename_, "a");
}

File::~File() {
  fclose(pFile_);
  delete[] filename_;
}

void File::Write(const char *str) {
  fputs(str, pFile_);  
  fputc('\n', pFile_); 
}

void File::Refresh(void) {
  fclose(pFile_);
  pFile_ = fopen(filename_, "a");
}

bool File::IsValid(void) const {
  if (pFile_ != nullptr) {
    return true;
  }
  return false;
}