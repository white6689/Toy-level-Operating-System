# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ljy/OS_projects/make_HashTable

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ljy/OS_projects/make_HashTable/build

# Include any dependencies generated for this target.
include CMakeFiles/make_HashTable.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/make_HashTable.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/make_HashTable.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/make_HashTable.dir/flags.make

CMakeFiles/make_HashTable.dir/hw1.c.o: CMakeFiles/make_HashTable.dir/flags.make
CMakeFiles/make_HashTable.dir/hw1.c.o: ../hw1.c
CMakeFiles/make_HashTable.dir/hw1.c.o: CMakeFiles/make_HashTable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljy/OS_projects/make_HashTable/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/make_HashTable.dir/hw1.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/make_HashTable.dir/hw1.c.o -MF CMakeFiles/make_HashTable.dir/hw1.c.o.d -o CMakeFiles/make_HashTable.dir/hw1.c.o -c /home/ljy/OS_projects/make_HashTable/hw1.c

CMakeFiles/make_HashTable.dir/hw1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/make_HashTable.dir/hw1.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ljy/OS_projects/make_HashTable/hw1.c > CMakeFiles/make_HashTable.dir/hw1.c.i

CMakeFiles/make_HashTable.dir/hw1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/make_HashTable.dir/hw1.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ljy/OS_projects/make_HashTable/hw1.c -o CMakeFiles/make_HashTable.dir/hw1.c.s

CMakeFiles/make_HashTable.dir/main.c.o: CMakeFiles/make_HashTable.dir/flags.make
CMakeFiles/make_HashTable.dir/main.c.o: ../main.c
CMakeFiles/make_HashTable.dir/main.c.o: CMakeFiles/make_HashTable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljy/OS_projects/make_HashTable/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/make_HashTable.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/make_HashTable.dir/main.c.o -MF CMakeFiles/make_HashTable.dir/main.c.o.d -o CMakeFiles/make_HashTable.dir/main.c.o -c /home/ljy/OS_projects/make_HashTable/main.c

CMakeFiles/make_HashTable.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/make_HashTable.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ljy/OS_projects/make_HashTable/main.c > CMakeFiles/make_HashTable.dir/main.c.i

CMakeFiles/make_HashTable.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/make_HashTable.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ljy/OS_projects/make_HashTable/main.c -o CMakeFiles/make_HashTable.dir/main.c.s

# Object files for target make_HashTable
make_HashTable_OBJECTS = \
"CMakeFiles/make_HashTable.dir/hw1.c.o" \
"CMakeFiles/make_HashTable.dir/main.c.o"

# External object files for target make_HashTable
make_HashTable_EXTERNAL_OBJECTS =

make_HashTable: CMakeFiles/make_HashTable.dir/hw1.c.o
make_HashTable: CMakeFiles/make_HashTable.dir/main.c.o
make_HashTable: CMakeFiles/make_HashTable.dir/build.make
make_HashTable: CMakeFiles/make_HashTable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ljy/OS_projects/make_HashTable/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable make_HashTable"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/make_HashTable.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/make_HashTable.dir/build: make_HashTable
.PHONY : CMakeFiles/make_HashTable.dir/build

CMakeFiles/make_HashTable.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/make_HashTable.dir/cmake_clean.cmake
.PHONY : CMakeFiles/make_HashTable.dir/clean

CMakeFiles/make_HashTable.dir/depend:
	cd /home/ljy/OS_projects/make_HashTable/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ljy/OS_projects/make_HashTable /home/ljy/OS_projects/make_HashTable /home/ljy/OS_projects/make_HashTable/build /home/ljy/OS_projects/make_HashTable/build /home/ljy/OS_projects/make_HashTable/build/CMakeFiles/make_HashTable.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/make_HashTable.dir/depend
