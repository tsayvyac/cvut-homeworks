# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = "/mnt/c/Users/slava/OneDrive/Documents/Studium/FEL SIT/FEL SIT 4/DSA/sort"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/slava/OneDrive/Documents/Studium/FEL SIT/FEL SIT 4/DSA/sort/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/sort.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sort.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sort.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sort.dir/flags.make

CMakeFiles/sort.dir/sort.cpp.o: CMakeFiles/sort.dir/flags.make
CMakeFiles/sort.dir/sort.cpp.o: /mnt/c/Users/slava/OneDrive/Documents/Studium/FEL\ SIT/FEL\ SIT\ 4/DSA/sort/sort.cpp
CMakeFiles/sort.dir/sort.cpp.o: CMakeFiles/sort.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/slava/OneDrive/Documents/Studium/FEL SIT/FEL SIT 4/DSA/sort/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sort.dir/sort.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sort.dir/sort.cpp.o -MF CMakeFiles/sort.dir/sort.cpp.o.d -o CMakeFiles/sort.dir/sort.cpp.o -c "/mnt/c/Users/slava/OneDrive/Documents/Studium/FEL SIT/FEL SIT 4/DSA/sort/sort.cpp"

CMakeFiles/sort.dir/sort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sort.dir/sort.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/slava/OneDrive/Documents/Studium/FEL SIT/FEL SIT 4/DSA/sort/sort.cpp" > CMakeFiles/sort.dir/sort.cpp.i

CMakeFiles/sort.dir/sort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sort.dir/sort.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/slava/OneDrive/Documents/Studium/FEL SIT/FEL SIT 4/DSA/sort/sort.cpp" -o CMakeFiles/sort.dir/sort.cpp.s

# Object files for target sort
sort_OBJECTS = \
"CMakeFiles/sort.dir/sort.cpp.o"

# External object files for target sort
sort_EXTERNAL_OBJECTS =

sort: CMakeFiles/sort.dir/sort.cpp.o
sort: CMakeFiles/sort.dir/build.make
sort: CMakeFiles/sort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/slava/OneDrive/Documents/Studium/FEL SIT/FEL SIT 4/DSA/sort/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sort"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sort.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sort.dir/build: sort
.PHONY : CMakeFiles/sort.dir/build

CMakeFiles/sort.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sort.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sort.dir/clean

CMakeFiles/sort.dir/depend:
	cd "/mnt/c/Users/slava/OneDrive/Documents/Studium/FEL SIT/FEL SIT 4/DSA/sort/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/slava/OneDrive/Documents/Studium/FEL SIT/FEL SIT 4/DSA/sort" "/mnt/c/Users/slava/OneDrive/Documents/Studium/FEL SIT/FEL SIT 4/DSA/sort" "/mnt/c/Users/slava/OneDrive/Documents/Studium/FEL SIT/FEL SIT 4/DSA/sort/cmake-build-debug" "/mnt/c/Users/slava/OneDrive/Documents/Studium/FEL SIT/FEL SIT 4/DSA/sort/cmake-build-debug" "/mnt/c/Users/slava/OneDrive/Documents/Studium/FEL SIT/FEL SIT 4/DSA/sort/cmake-build-debug/CMakeFiles/sort.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/sort.dir/depend

