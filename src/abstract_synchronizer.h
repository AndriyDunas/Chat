// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains abstract class AbstractSynchronizer with virtual methods
// that are overrided in derived classes having specializations for each platform. 
// Synchronizers are used for serializing access to non-reentrant sections of code.
//
#ifndef ABSTRACT_SYNCHRONIZER_
#define ABSTRACT_SYNCHRONIZER_

class AbstractSynchronizer {
 public:
  virtual ~AbstractSynchronizer() {}
  
  virtual int Lock(void) = 0;
  virtual int Unlock(void) = 0;
};

#endif // !ABSTRACT_SYNCHRONIZER_