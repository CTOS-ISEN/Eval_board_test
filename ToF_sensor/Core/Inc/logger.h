#ifndef INC_LOGGER_H_
#define INC_LOGGER_H_
#define LOG_BUFFER_SIZE 512
void log_init(void* huart);
void log_printf(const char* format, ...);
#endif // INC_LOGGER_H_
