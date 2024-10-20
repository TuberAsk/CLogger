#define _DEFAULT_SOURCE
#include"logger.h"

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

struct Logger *create_logger(enum LogLevel level, FILE *handler) 
{
    struct Logger *logger = (struct Logger *)malloc(sizeof(struct Logger));
    if (logger == NULL) return NULL;

    logger->handler = handler;
    logger->level = level;

    return logger;
}

time_t get_current_time(void) 
{
    return time(NULL);
}

void logger_log(const char *str, struct Logger *logger) 
{
    time_t current_time = get_current_time();

    switch (logger->level) 
    {
        case INFO: 
        {
            fprintf(logger->handler, "[%s] [INFO] %s\n", ctime(&current_time), str);
        } break;

        case WARNING: 
        {
            fprintf(logger->handler, "[%s] [WARNING] %s\n", ctime(&current_time), str);
        } break;

        case ERROR:
        {
            fprintf(logger->handler, "[%s] [ERROR] %s\n", ctime(&current_time), str);
        } break;

        case DEBUG: 
        {
            fprintf(logger->handler, "[%s] [DEBUG] %s\n", ctime(&current_time), str);
        } break;
    }
}

void clear_logger(struct Logger *logger) 
{
    fflush(logger->handler);

    int fd = fileno(logger->handler);

    if (ftruncate(fd, 0) == -1) 
    {
        perror("ftruncate");
        return;
    }
}

void free_logger(struct Logger *logger) 
{
    fclose(logger->handler);
    free(logger);
}

int main(void) 
{
    FILE *file = fopen("log_file.log", "a");
    if (file == NULL) return -1;

    struct Logger *logger = create_logger(DEBUG, file);
    logger_log("Hello, World!", logger);
    logger_log("Hello, World!", logger);
    
    clear_logger(logger);
    free_logger(logger);
    return 0;
}
