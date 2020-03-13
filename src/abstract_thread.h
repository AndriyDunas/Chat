// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains abstract class AbstractThread that is base class
// for derived classes having specializations for each platform. 
// Threads are used for creating and running threads. When the constructor
// is called the new thread starts running the passed method in the new thread. 
//
#ifndef ABSTRACT_THREAD_
#define ABSTRACT_THREAD_

class AbstractThread {
 public:
  virtual ~AbstractThread() {}
};

#endif // !ABSTRACT_THREAD_