#include "signals.hpp"

volatile std::sig_atomic_t gSignalStatus = 0;

void signalHandler(int sig){
    gSignalStatus = sig;
}
