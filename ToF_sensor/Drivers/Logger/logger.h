/*
 * logger.h
 *
 *  Created on: Dec 4, 2024
 *      Author: reppl
 */

#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_


#define LOG_BUFFER_SIZE 512
void log_init(void* huart);
void log_printf(const char* format, ...);


#endif /* LOGGER_LOGGER_H_ */
