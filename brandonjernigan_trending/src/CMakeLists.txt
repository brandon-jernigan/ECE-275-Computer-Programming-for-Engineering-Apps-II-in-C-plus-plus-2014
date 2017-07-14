# Author: Brandon Jernigan
# Net ID: brandonjernigan
# Date: September 29, 2014
# Assignment Number: 2

# Enable flags to report all warnings and enable debugging

set(CMAKE_C_FLAGS "-Wall -g")

# Make a list of all .c and .h files in the current directory and store in the variable SRCS

file(GLOB SRCS *.c *.h)

# Define target executable and the list of .c  and .h files

add_executable(trending ${SRCS})