# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/zxg/mycode/github/ChatServer/03moduo/01cmake_moduo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zxg/mycode/github/ChatServer/03moduo/01cmake_moduo/build

# Include any dependencies generated for this target.
include CMakeFiles/cmake_moduo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cmake_moduo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmake_moduo.dir/flags.make

CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o: CMakeFiles/cmake_moduo.dir/flags.make
CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o: ../cmake_moduo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zxg/mycode/github/ChatServer/03moduo/01cmake_moduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o -c /home/zxg/mycode/github/ChatServer/03moduo/01cmake_moduo/cmake_moduo.cpp

CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zxg/mycode/github/ChatServer/03moduo/01cmake_moduo/cmake_moduo.cpp > CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.i

CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zxg/mycode/github/ChatServer/03moduo/01cmake_moduo/cmake_moduo.cpp -o CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.s

CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o.requires:

.PHONY : CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o.requires

CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o.provides: CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o.requires
	$(MAKE) -f CMakeFiles/cmake_moduo.dir/build.make CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o.provides.build
.PHONY : CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o.provides

CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o.provides.build: CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o


# Object files for target cmake_moduo
cmake_moduo_OBJECTS = \
"CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o"

# External object files for target cmake_moduo
cmake_moduo_EXTERNAL_OBJECTS =

../bin/cmake_moduo: CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o
../bin/cmake_moduo: CMakeFiles/cmake_moduo.dir/build.make
../bin/cmake_moduo: CMakeFiles/cmake_moduo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zxg/mycode/github/ChatServer/03moduo/01cmake_moduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/cmake_moduo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmake_moduo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmake_moduo.dir/build: ../bin/cmake_moduo

.PHONY : CMakeFiles/cmake_moduo.dir/build

CMakeFiles/cmake_moduo.dir/requires: CMakeFiles/cmake_moduo.dir/cmake_moduo.cpp.o.requires

.PHONY : CMakeFiles/cmake_moduo.dir/requires

CMakeFiles/cmake_moduo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cmake_moduo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cmake_moduo.dir/clean

CMakeFiles/cmake_moduo.dir/depend:
	cd /home/zxg/mycode/github/ChatServer/03moduo/01cmake_moduo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zxg/mycode/github/ChatServer/03moduo/01cmake_moduo /home/zxg/mycode/github/ChatServer/03moduo/01cmake_moduo /home/zxg/mycode/github/ChatServer/03moduo/01cmake_moduo/build /home/zxg/mycode/github/ChatServer/03moduo/01cmake_moduo/build /home/zxg/mycode/github/ChatServer/03moduo/01cmake_moduo/build/CMakeFiles/cmake_moduo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cmake_moduo.dir/depend

