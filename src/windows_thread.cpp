// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains implementation of class WindowsThread 
// having specialization to use threads in Windows.
//
#include "general.h"

#if defined(WIN)

#include "windows_thread.h"

// Create a new thread, run start_func in that thread, and store 
// thread ID to t_id_
WindowsThread::WindowsThread(void*(*start_func)(void*), void *arg) {
  t_handle_ = reinterpret_cast<HANDLE>(_beginthreadex(0, 0, 
              (unsigned int(_stdcall*)(void*) )start_func, arg, 0, &t_id_));
}

WindowsThread::~WindowsThread() {
  CloseHandle(t_handle_);
}

#endif  // !class implementation