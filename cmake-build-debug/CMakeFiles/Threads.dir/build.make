# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/barak/Documents/GitHub/Threads

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/barak/Documents/GitHub/Threads/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Threads.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Threads.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Threads.dir/flags.make

CMakeFiles/Threads.dir/stack.c.o: CMakeFiles/Threads.dir/flags.make
CMakeFiles/Threads.dir/stack.c.o: ../stack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/barak/Documents/GitHub/Threads/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Threads.dir/stack.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Threads.dir/stack.c.o   -c /mnt/c/Users/barak/Documents/GitHub/Threads/stack.c

CMakeFiles/Threads.dir/stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Threads.dir/stack.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/barak/Documents/GitHub/Threads/stack.c > CMakeFiles/Threads.dir/stack.c.i

CMakeFiles/Threads.dir/stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Threads.dir/stack.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/barak/Documents/GitHub/Threads/stack.c -o CMakeFiles/Threads.dir/stack.c.s

CMakeFiles/Threads.dir/client.c.o: CMakeFiles/Threads.dir/flags.make
CMakeFiles/Threads.dir/client.c.o: ../client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/barak/Documents/GitHub/Threads/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Threads.dir/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Threads.dir/client.c.o   -c /mnt/c/Users/barak/Documents/GitHub/Threads/client.c

CMakeFiles/Threads.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Threads.dir/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/barak/Documents/GitHub/Threads/client.c > CMakeFiles/Threads.dir/client.c.i

CMakeFiles/Threads.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Threads.dir/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/barak/Documents/GitHub/Threads/client.c -o CMakeFiles/Threads.dir/client.c.s

CMakeFiles/Threads.dir/server.c.o: CMakeFiles/Threads.dir/flags.make
CMakeFiles/Threads.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/barak/Documents/GitHub/Threads/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Threads.dir/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Threads.dir/server.c.o   -c /mnt/c/Users/barak/Documents/GitHub/Threads/server.c

CMakeFiles/Threads.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Threads.dir/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/barak/Documents/GitHub/Threads/server.c > CMakeFiles/Threads.dir/server.c.i

CMakeFiles/Threads.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Threads.dir/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/barak/Documents/GitHub/Threads/server.c -o CMakeFiles/Threads.dir/server.c.s

CMakeFiles/Threads.dir/queue.c.o: CMakeFiles/Threads.dir/flags.make
CMakeFiles/Threads.dir/queue.c.o: ../queue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/barak/Documents/GitHub/Threads/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Threads.dir/queue.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Threads.dir/queue.c.o   -c /mnt/c/Users/barak/Documents/GitHub/Threads/queue.c

CMakeFiles/Threads.dir/queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Threads.dir/queue.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/barak/Documents/GitHub/Threads/queue.c > CMakeFiles/Threads.dir/queue.c.i

CMakeFiles/Threads.dir/queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Threads.dir/queue.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/barak/Documents/GitHub/Threads/queue.c -o CMakeFiles/Threads.dir/queue.c.s

CMakeFiles/Threads.dir/test.c.o: CMakeFiles/Threads.dir/flags.make
CMakeFiles/Threads.dir/test.c.o: ../test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/barak/Documents/GitHub/Threads/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Threads.dir/test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Threads.dir/test.c.o   -c /mnt/c/Users/barak/Documents/GitHub/Threads/test.c

CMakeFiles/Threads.dir/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Threads.dir/test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/barak/Documents/GitHub/Threads/test.c > CMakeFiles/Threads.dir/test.c.i

CMakeFiles/Threads.dir/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Threads.dir/test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/barak/Documents/GitHub/Threads/test.c -o CMakeFiles/Threads.dir/test.c.s

# Object files for target Threads
Threads_OBJECTS = \
"CMakeFiles/Threads.dir/stack.c.o" \
"CMakeFiles/Threads.dir/client.c.o" \
"CMakeFiles/Threads.dir/server.c.o" \
"CMakeFiles/Threads.dir/queue.c.o" \
"CMakeFiles/Threads.dir/test.c.o"

# External object files for target Threads
Threads_EXTERNAL_OBJECTS =

Threads: CMakeFiles/Threads.dir/stack.c.o
Threads: CMakeFiles/Threads.dir/client.c.o
Threads: CMakeFiles/Threads.dir/server.c.o
Threads: CMakeFiles/Threads.dir/queue.c.o
Threads: CMakeFiles/Threads.dir/test.c.o
Threads: CMakeFiles/Threads.dir/build.make
Threads: CMakeFiles/Threads.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/barak/Documents/GitHub/Threads/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable Threads"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Threads.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Threads.dir/build: Threads

.PHONY : CMakeFiles/Threads.dir/build

CMakeFiles/Threads.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Threads.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Threads.dir/clean

CMakeFiles/Threads.dir/depend:
	cd /mnt/c/Users/barak/Documents/GitHub/Threads/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/barak/Documents/GitHub/Threads /mnt/c/Users/barak/Documents/GitHub/Threads /mnt/c/Users/barak/Documents/GitHub/Threads/cmake-build-debug /mnt/c/Users/barak/Documents/GitHub/Threads/cmake-build-debug /mnt/c/Users/barak/Documents/GitHub/Threads/cmake-build-debug/CMakeFiles/Threads.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Threads.dir/depend

