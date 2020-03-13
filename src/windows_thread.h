// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains declaration of class WindowsThread 
// having specialization to use threads in Windows.
//
#ifndef WINDOWS_THREAD_H_
#define WINDOWS_THREAD_H_

#if defined(WIN)

#include <windows.h>
#include <process.h>
#include "abstract_thread.h"

// Windows thread support.
class WindowsThread : public AbstractThread {
 public:
  WindowsThread();
  ~WindowsThread();
  WindowsThread(void*(*start_func)(void*), void *arg);

  const HANDLE GetHandle() const { return t_handle_; }
  const unsigned int GetId() const { return t_id_; }

 private:
  // copy operations are private to prevent copying
  WindowsThread(const WindowsThread&);
  WindowsThread& operator=(const WindowsThread&);
  
  HANDLE t_handle_;    // thread handle
  unsigned int t_id_;  // thread ID
};

#endif  // !includes, class declaration

#endif  // !WINDOWS_THREAD_H_