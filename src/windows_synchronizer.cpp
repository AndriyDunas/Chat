// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains implementation of class WindowsSynchronizer 
// having specialization to synchronize threads in Windows.
//
#include "windows_synchronizer.h"

#if defined(WIN)

const unsigned int kSpinCount = 1024;  // spin count for critical section

// Initializes a critical section object and sets the spin count for
// the critical section. When a thread tries to acquire a critical section 
// that is locked, the thread spins: it enters a loop which iterates 
// spin count times, checking to see if the lock is released. If the lock is 
// not released before the loop finishes, the thread goes to sleep to wait 
// for the lock to be released.
WindowsSynchronizer::WindowsSynchronizer() {
  InitializeCriticalSectionAndSpinCount(&cs_, kSpinCount);
}

// Releases all resources used by an unowned critical section object.
WindowsSynchronizer::~WindowsSynchronizer() {
  DeleteCriticalSection(&cs_);
}

// Waits for ownership of the specified critical section object. 
// The function returns when the calling thread is granted ownership.
int WindowsSynchronizer::Lock(void) {
  EnterCriticalSection(&cs_);
  return 0;
}

// Releases ownership of the specified critical section object.
int WindowsSynchronizer::Unlock(void) {
  LeaveCriticalSection(&cs_);
  return 0;
}

#endif  //!class implementation