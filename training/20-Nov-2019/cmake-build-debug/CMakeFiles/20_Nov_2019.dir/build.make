# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.2.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.2.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\haleyk\Documents\GitHub\HPtt\training\20-Nov-2019

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\haleyk\Documents\GitHub\HPtt\training\20-Nov-2019\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/20_Nov_2019.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/20_Nov_2019.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/20_Nov_2019.dir/flags.make

CMakeFiles/20_Nov_2019.dir/main.cpp.obj: CMakeFiles/20_Nov_2019.dir/flags.make
CMakeFiles/20_Nov_2019.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\haleyk\Documents\GitHub\HPtt\training\20-Nov-2019\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/20_Nov_2019.dir/main.cpp.obj"
	C:\PROGRA~1\mingw-w64\x86_64-7.2.0-posix-seh-rt_v5-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\20_Nov_2019.dir\main.cpp.obj -c C:\Users\haleyk\Documents\GitHub\HPtt\training\20-Nov-2019\main.cpp

CMakeFiles/20_Nov_2019.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/20_Nov_2019.dir/main.cpp.i"
	C:\PROGRA~1\mingw-w64\x86_64-7.2.0-posix-seh-rt_v5-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\haleyk\Documents\GitHub\HPtt\training\20-Nov-2019\main.cpp > CMakeFiles\20_Nov_2019.dir\main.cpp.i

CMakeFiles/20_Nov_2019.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/20_Nov_2019.dir/main.cpp.s"
	C:\PROGRA~1\mingw-w64\x86_64-7.2.0-posix-seh-rt_v5-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\haleyk\Documents\GitHub\HPtt\training\20-Nov-2019\main.cpp -o CMakeFiles\20_Nov_2019.dir\main.cpp.s

# Object files for target 20_Nov_2019
20_Nov_2019_OBJECTS = \
"CMakeFiles/20_Nov_2019.dir/main.cpp.obj"

# External object files for target 20_Nov_2019
20_Nov_2019_EXTERNAL_OBJECTS =

20_Nov_2019.exe: CMakeFiles/20_Nov_2019.dir/main.cpp.obj
20_Nov_2019.exe: CMakeFiles/20_Nov_2019.dir/build.make
20_Nov_2019.exe: CMakeFiles/20_Nov_2019.dir/linklibs.rsp
20_Nov_2019.exe: CMakeFiles/20_Nov_2019.dir/objects1.rsp
20_Nov_2019.exe: CMakeFiles/20_Nov_2019.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\haleyk\Documents\GitHub\HPtt\training\20-Nov-2019\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 20_Nov_2019.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\20_Nov_2019.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/20_Nov_2019.dir/build: 20_Nov_2019.exe

.PHONY : CMakeFiles/20_Nov_2019.dir/build

CMakeFiles/20_Nov_2019.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\20_Nov_2019.dir\cmake_clean.cmake
.PHONY : CMakeFiles/20_Nov_2019.dir/clean

CMakeFiles/20_Nov_2019.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\haleyk\Documents\GitHub\HPtt\training\20-Nov-2019 C:\Users\haleyk\Documents\GitHub\HPtt\training\20-Nov-2019 C:\Users\haleyk\Documents\GitHub\HPtt\training\20-Nov-2019\cmake-build-debug C:\Users\haleyk\Documents\GitHub\HPtt\training\20-Nov-2019\cmake-build-debug C:\Users\haleyk\Documents\GitHub\HPtt\training\20-Nov-2019\cmake-build-debug\CMakeFiles\20_Nov_2019.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/20_Nov_2019.dir/depend

