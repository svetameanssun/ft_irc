#pragma once
#include <csignal>

extern volatile std::sig_atomic_t gSignalStatus;

void signalHandler(int sig);
