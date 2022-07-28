#ifndef LOG_H
#define LOG_H

#include "globals.h"

typedef struct DataLog {

} DataLog;

// Initialize logging SD card
void initLog();

// Add to Async Storing Queue
void addLogData(DataLog* data);

// Done Async Interrupt
void finishAsync();

#endif