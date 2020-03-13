// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file provides identification of platform. So, we just include
// it where we need to do some platform-depended actions.
//
#ifndef GENERAL_H_
#define GENERAL_H_

enum Platforms {
  WIN_PLATFORM = 1,
  LIN_PLATFORM = 2
};

#if defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
#define WIN WIN_PLATFORM;
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define WIN WIN_PLATFORM;
#elif defined(__NT__) || defined(__WINDOWS__) || defined(_WINDOWS)
#define WIN WIN_PLATFORM;
#elif defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
#define LIN LIN_PLATFORM;
#endif 

#endif  // !GENERAL_H_