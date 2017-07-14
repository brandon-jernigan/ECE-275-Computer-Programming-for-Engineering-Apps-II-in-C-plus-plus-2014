# Author: Brandon Jernigan
# NetID: brandonjernigan
# Date: 12/6/2014
# Assignment: 5

if(UNIX)

# Report all warnings in unix.

set(CMAKE_CXX_FLAGS "-Wall -g")

else(UNIX)

#only report imortant warnings in windows.

set(CMAKE_CXX_FLAGS "/W3 /EHsc")

endif(UNIX)

# search for all .h & .cpp files in the current directory, store into SRCS.

file(GLOB SRCS *.cpp *.h)

# Define application executable and list of source and header files needed.

add_executable(weighs ${SRCS})