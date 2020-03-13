// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains implementation of class LinuxThread 
// having specialization to use threads in Linux.
//
#include "general.h"

#if defined(LIN)

#include "linux_thread.h"

LinuxThread::LinuxThread(void*(*start_func)(void*), void *arg) {
  // Create a new thread, run start_func in that thread, and store 
  // thread ID to t_id_
  result_ = pthread_create(&t_id_, NULL, start_func, arg);
}

int LinuxThread::Join(void) {
  // Suspend  execution of the calling thread
  // and wait for t_id_ (our) thread termination
  return pthread_join(t_id_, NULL);
}

#endif  // !class implementation