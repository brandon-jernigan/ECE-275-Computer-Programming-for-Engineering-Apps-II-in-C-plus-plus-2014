# Author: Brandon Jernigan
# NetID: brandonjernigan
# Date: 11/20/2014
# Assignment Number: 4

# In src/CMakeLists.txt 
# CMake will do different stuff if we are on Unix
# (which means Linux/Unix/Mac OS here) 
if( UNIX ) 
# Sets the compilation flags to report all warnings 
# and enable debugging in the generated 
# object files and executable. 
set( CMAKE_CXX_FLAGS "-Wall -g" ) 
ELSE( UNIX ) 
# Now we do for everyone else (e.g., Windows) 
# Sets the compilation flags to report all meaningful warnings, and to ensure that 
# we don't get silly warnings for exception handling semantics and unwinding 
set( CMAKE_CXX_FLAGS "/W3 /EHsc" ) 
ENDIF(UNIX)

# The following file GLOB command will search for all files within the current directory
# that match the specified expressions (*.cpp and *.h), and assign the resulting files
# to the variable SRCS. Thus, SRCS is a list a all C source and header files in the 
# current directory.

file( GLOB SRCS *.cpp *.h )

# Define the target application executable and the list of CPP source
# and header files needed for the executable.

add_executable( visittest ${SRCS} )
