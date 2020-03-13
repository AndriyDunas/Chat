// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains implementation of class LinuxSynchronizer 
// having specialization to synchronize threads in Linux.
//
#include "linux_synchronizer.h"

#if defined(LIN)

// Initialize a mutex
LinuxSynchronizer::LinuxSynchronizer() {
  pthread_mutexattr_t attrs;
  pthread_mutexattr_init(&attrs);
  pthread_mutexattr_settype(&attrs, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&mutex_, &attrs);
}

LinuxSynchronizer::~LinuxSynchronizer() {
  pthread_mutex_destroy(&mutex_);
}

// Critical region in the code will be locked.
int LinuxSynchronizer::Lock(void) {
  int res = pthread_mutex_lock(&mutex_);
  return res;
}

// Releases the lock 
int LinuxSynchronizer::Unlock(void) {
  int res = pthread_mutex_unlock(&mutex_);
  return res;
}

#endif  // !class implementation