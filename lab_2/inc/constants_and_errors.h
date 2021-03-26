#ifndef CONSTANTS_AND_ERRORS_H
#define CONSTANTS_AND_ERRORS_H

#define MAXIMUM_TABLE_SIZE 1000
#define MAXIMUM_LENGTH_OF_THEATER_NAME 23
#define MAXIMUM_LENGTH_OF_PERFORMANCE_NAME 20
#define MAXIMUM_LENGTH_OF_PRODUCER_NAME 20
#define MAXIMUM_COUNTRY_NAME_LENGTH 15
#define MAXIMUM_COMPOSER_NAME_LENGTH 20
#define MAXIMUM_LENGTH_TYPE_OF_PERFOMANCE_FOR_CHILDREN 5
#define MAXIMUM_LENGTH_TYPE_OF_PERFOMANCE_FOR_ADULTS 6
#define MAXIMUM_LENGTH_TYPE_OF_SPECTACL 7
#define MIN_COMMAND_NUMBER 0
#define MAX_COMMAND_NUMBER 12
#define MAXIMUM_AGE_OF_CHILD 17
#define MAXIMUM_AGE_FOR_MUSIC 23
#define NUMBER_OF_RUNS 500
#define HZ 2300000000

#define SUCCESS 0

#define ERROR_WHEN_OPENING_FILE 1
#define UNKNOWN_NUMBER_OF_ENTRIES_IN_FILE 2
#define INACCEPTABLE_NUMBER_OF_RECORDS_IN_FILE 3

#define UNABLE_TO_READ_THE_WORD 91
#define ERROR_IN_WORD 92
#define WORD_TOO_LONG 93

#define MISTAKE_IN_THE_NAME_OF_THE_THEATER 4
#define TOO_LONG_THEATER_NAME 5

#define MISTAKE_IN_THE_NAME_OF_THE_PERFORMANCE 6
#define TOO_LONG_PERFOMANCE_NAME 7

#define ERROR_IN_THE_NAME_OF_THE_PRODUCER 8
#define TOO_LONG_PRODUCER_NAME 9

#define UNABLE_TO_COUNT_THE_MINIMUM_TICKET_PRICE 10
#define UNABLE_TO_COUNT_THE_MAXIMUM_TICKET_PRICE 11
#define ICKET_PRICE_MUST_BE_GREATER_THAN_ZERO 12
#define MINIMUM_TICKET_PRICE_SHOULD_NOT_EXCEED_THE_MAXIMUM 13
#define WRONG_TYPE_OF_PERFORMANCE 14

#define FAILED_TO_COUNT_THE_MINIMUM_AGE 15
#define AGE_CANNOT_BE_NEGATIVE 16
#define CHILDS_AGE_TOO_GREAT 17
#define WRONG_TYPE_OF_PERFORMANCE_FOR_CHILDREN 18
#define EXCESSIVE_INFORMATION 19
#define WRONG_TYPE_OF_PERFORMANCE_FOR_ADULT 20

#define ERROR_IN_THE_NAME_OF_THE_COMPOSER 21
#define TOO_LONG_COMPOSER_NAME 22

#define ERROR_IN_THE_NAME_OF_THE_COUNTRY 23
#define TOO_LONG_COUNTRY_NAME 24
#define AGE_TOO_GREAT 25

#define UNABLE_TO_READ_THE_DURATION_OF_THE_PERFORMANCE 26
#define DURATION_OF_THE_PERFORMANCE_CANNOT_BE_NEGATIVE 27

#define FAILED_TO_READ_COMMAND_NUMBER 28
#define WRONG_COMMAND_NUMBER 29

#define TABLE_IS_FULL 30

#endif