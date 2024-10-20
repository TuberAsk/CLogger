#ifndef LOGGER_H
#define LOGGER_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<fcntl.h>

enum LogLevel 
{
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

struct Logger 
{
    enum LogLevel level;
    FILE *handler;
};

struct Logger *create_logger(enum LogLevel level, FILE *handler);
time_t get_current_time(void);
void logger_log(const char *str, struct Logger *logger);
void clear_logger(struct Logger *logger);
void free_logger(struct Logger *logger);

#endif // LOGGER_H
