// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains declaration of class LinuxSynchronizer 
// having specialization to synchronize threads in Linux.
//
#ifndef LINUX_SYNCHRONIZER_H_
#define LINUX_SYNCHRONIZER_H_

#include "general.h"

#if defined(LIN)

#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "abstract_synchronizer.h"

// Linux mutex support
class LinuxSynchronizer : public AbstractSynchronizer {
 public:
  explicit LinuxSynchronizer();
  ~LinuxSynchronizer();

  int Lock(void) override;
  int Unlock(void) override;

 private:
  // copy operations are private to prevent copying
  LinuxSynchronizer(const LinuxSynchronizer&);
  LinuxSynchronizer& operator=(const LinuxSynchronizer&);

  pthread_mutex_t mutex_;  // mutex for Linux
};

#endif  // !includes, class declaration

#endif  // !LINUX_SYNCHRONIZER_H_