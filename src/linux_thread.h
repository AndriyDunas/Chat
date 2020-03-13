// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains declaration of class LinuxThread 
// having specialization to use threads in Linux.
//
#ifndef LINUX_THREAD_H_
#define LINUX_THREAD_H_

#include "general.h"

#if defined(LIN)

#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "abstract_thread.h"

// Linux thread support.
class LinuxThread : public AbstractThread {
 public:
  LinuxThread();
  LinuxThread(void*(*start_func)(void*), void *arg);
  ~LinuxThread() {};
  
  int Join(void);
  const pthread_t GetId(void) const { return t_id_; }
  const int GetResult(void) const { return result_; }

 private:
  // copy operations are private to prevent copying
  LinuxThread(const LinuxThread&);        
  LinuxThread& operator=(const LinuxThread&); 

  pthread_t t_id_;  // thread ID
  int result_;      // pthread_create return value
};

#endif  // !includes, class declaration

#endif  // !LINUX_THREAD_H_