// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains declaration of class WindowsSynchronizer 
// having specialization to synchronize threads in Windows.
//
#ifndef WINDOWS_SYNCHRONIZER_H_
#define WINDOWS_SYNCHRONIZER_H_

#include "general.h"

#if defined(WIN)

#include <windows.h>
#include "abstract_synchronizer.h"

// On Windows synchronizer are implemented using CRITICAL_SECTION objects, 
// because of critical sections are implemented in user mode, and a mutex 
// will switch context to kernel mode, that's why in most cases critical 
// section are faster than mutex. Also, in my app I don't need to synchronize 
// threads in several processes, so I don't really need to use mutex. 
class WindowsSynchronizer : public AbstractSynchronizer {
 public:
  explicit WindowsSynchronizer();
  ~WindowsSynchronizer(); 

  int Lock(void) override;
  int Unlock(void) override;

 private:
  // copy operations are private to prevent copying
  WindowsSynchronizer(const WindowsSynchronizer&);
  WindowsSynchronizer& operator=(const WindowsSynchronizer&);

  CRITICAL_SECTION cs_;  // Critical section used for mutex
};

#endif  // !includes, class declaration

#endif  // !WINDOWS_SYNCHRONIZER_H_