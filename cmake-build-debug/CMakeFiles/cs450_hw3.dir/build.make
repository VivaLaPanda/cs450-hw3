# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = "T:\Program Files\JetBrains\CLion 2017.2.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "T:\Program Files\JetBrains\CLion 2017.2.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/cs450_hw3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cs450_hw3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cs450_hw3.dir/flags.make

CMakeFiles/cs450_hw3.dir/boardvalidate.c.obj: CMakeFiles/cs450_hw3.dir/flags.make
CMakeFiles/cs450_hw3.dir/boardvalidate.c.obj: ../boardvalidate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cs450_hw3.dir/boardvalidate.c.obj"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\cs450_hw3.dir\boardvalidate.c.obj   -c "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\boardvalidate.c"

CMakeFiles/cs450_hw3.dir/boardvalidate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cs450_hw3.dir/boardvalidate.c.i"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\boardvalidate.c" > CMakeFiles\cs450_hw3.dir\boardvalidate.c.i

CMakeFiles/cs450_hw3.dir/boardvalidate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cs450_hw3.dir/boardvalidate.c.s"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\boardvalidate.c" -o CMakeFiles\cs450_hw3.dir\boardvalidate.c.s

CMakeFiles/cs450_hw3.dir/boardvalidate.c.obj.requires:

.PHONY : CMakeFiles/cs450_hw3.dir/boardvalidate.c.obj.requires

CMakeFiles/cs450_hw3.dir/boardvalidate.c.obj.provides: CMakeFiles/cs450_hw3.dir/boardvalidate.c.obj.requires
	$(MAKE) -f CMakeFiles\cs450_hw3.dir\build.make CMakeFiles/cs450_hw3.dir/boardvalidate.c.obj.provides.build
.PHONY : CMakeFiles/cs450_hw3.dir/boardvalidate.c.obj.provides

CMakeFiles/cs450_hw3.dir/boardvalidate.c.obj.provides.build: CMakeFiles/cs450_hw3.dir/boardvalidate.c.obj


CMakeFiles/cs450_hw3.dir/chan.c.obj: CMakeFiles/cs450_hw3.dir/flags.make
CMakeFiles/cs450_hw3.dir/chan.c.obj: ../chan.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/cs450_hw3.dir/chan.c.obj"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\cs450_hw3.dir\chan.c.obj   -c "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\chan.c"

CMakeFiles/cs450_hw3.dir/chan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cs450_hw3.dir/chan.c.i"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\chan.c" > CMakeFiles\cs450_hw3.dir\chan.c.i

CMakeFiles/cs450_hw3.dir/chan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cs450_hw3.dir/chan.c.s"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\chan.c" -o CMakeFiles\cs450_hw3.dir\chan.c.s

CMakeFiles/cs450_hw3.dir/chan.c.obj.requires:

.PHONY : CMakeFiles/cs450_hw3.dir/chan.c.obj.requires

CMakeFiles/cs450_hw3.dir/chan.c.obj.provides: CMakeFiles/cs450_hw3.dir/chan.c.obj.requires
	$(MAKE) -f CMakeFiles\cs450_hw3.dir\build.make CMakeFiles/cs450_hw3.dir/chan.c.obj.provides.build
.PHONY : CMakeFiles/cs450_hw3.dir/chan.c.obj.provides

CMakeFiles/cs450_hw3.dir/chan.c.obj.provides.build: CMakeFiles/cs450_hw3.dir/chan.c.obj


CMakeFiles/cs450_hw3.dir/main.c.obj: CMakeFiles/cs450_hw3.dir/flags.make
CMakeFiles/cs450_hw3.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/cs450_hw3.dir/main.c.obj"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\cs450_hw3.dir\main.c.obj   -c "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\main.c"

CMakeFiles/cs450_hw3.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cs450_hw3.dir/main.c.i"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\main.c" > CMakeFiles\cs450_hw3.dir\main.c.i

CMakeFiles/cs450_hw3.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cs450_hw3.dir/main.c.s"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\main.c" -o CMakeFiles\cs450_hw3.dir\main.c.s

CMakeFiles/cs450_hw3.dir/main.c.obj.requires:

.PHONY : CMakeFiles/cs450_hw3.dir/main.c.obj.requires

CMakeFiles/cs450_hw3.dir/main.c.obj.provides: CMakeFiles/cs450_hw3.dir/main.c.obj.requires
	$(MAKE) -f CMakeFiles\cs450_hw3.dir\build.make CMakeFiles/cs450_hw3.dir/main.c.obj.provides.build
.PHONY : CMakeFiles/cs450_hw3.dir/main.c.obj.provides

CMakeFiles/cs450_hw3.dir/main.c.obj.provides.build: CMakeFiles/cs450_hw3.dir/main.c.obj


CMakeFiles/cs450_hw3.dir/parsetools.c.obj: CMakeFiles/cs450_hw3.dir/flags.make
CMakeFiles/cs450_hw3.dir/parsetools.c.obj: ../parsetools.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/cs450_hw3.dir/parsetools.c.obj"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\cs450_hw3.dir\parsetools.c.obj   -c "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\parsetools.c"

CMakeFiles/cs450_hw3.dir/parsetools.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cs450_hw3.dir/parsetools.c.i"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\parsetools.c" > CMakeFiles\cs450_hw3.dir\parsetools.c.i

CMakeFiles/cs450_hw3.dir/parsetools.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cs450_hw3.dir/parsetools.c.s"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\parsetools.c" -o CMakeFiles\cs450_hw3.dir\parsetools.c.s

CMakeFiles/cs450_hw3.dir/parsetools.c.obj.requires:

.PHONY : CMakeFiles/cs450_hw3.dir/parsetools.c.obj.requires

CMakeFiles/cs450_hw3.dir/parsetools.c.obj.provides: CMakeFiles/cs450_hw3.dir/parsetools.c.obj.requires
	$(MAKE) -f CMakeFiles\cs450_hw3.dir\build.make CMakeFiles/cs450_hw3.dir/parsetools.c.obj.provides.build
.PHONY : CMakeFiles/cs450_hw3.dir/parsetools.c.obj.provides

CMakeFiles/cs450_hw3.dir/parsetools.c.obj.provides.build: CMakeFiles/cs450_hw3.dir/parsetools.c.obj


CMakeFiles/cs450_hw3.dir/queue.c.obj: CMakeFiles/cs450_hw3.dir/flags.make
CMakeFiles/cs450_hw3.dir/queue.c.obj: ../queue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/cs450_hw3.dir/queue.c.obj"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\cs450_hw3.dir\queue.c.obj   -c "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\queue.c"

CMakeFiles/cs450_hw3.dir/queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cs450_hw3.dir/queue.c.i"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\queue.c" > CMakeFiles\cs450_hw3.dir\queue.c.i

CMakeFiles/cs450_hw3.dir/queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cs450_hw3.dir/queue.c.s"
	T:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\queue.c" -o CMakeFiles\cs450_hw3.dir\queue.c.s

CMakeFiles/cs450_hw3.dir/queue.c.obj.requires:

.PHONY : CMakeFiles/cs450_hw3.dir/queue.c.obj.requires

CMakeFiles/cs450_hw3.dir/queue.c.obj.provides: CMakeFiles/cs450_hw3.dir/queue.c.obj.requires
	$(MAKE) -f CMakeFiles\cs450_hw3.dir\build.make CMakeFiles/cs450_hw3.dir/queue.c.obj.provides.build
.PHONY : CMakeFiles/cs450_hw3.dir/queue.c.obj.provides

CMakeFiles/cs450_hw3.dir/queue.c.obj.provides.build: CMakeFiles/cs450_hw3.dir/queue.c.obj


# Object files for target cs450_hw3
cs450_hw3_OBJECTS = \
"CMakeFiles/cs450_hw3.dir/boardvalidate.c.obj" \
"CMakeFiles/cs450_hw3.dir/chan.c.obj" \
"CMakeFiles/cs450_hw3.dir/main.c.obj" \
"CMakeFiles/cs450_hw3.dir/parsetools.c.obj" \
"CMakeFiles/cs450_hw3.dir/queue.c.obj"

# External object files for target cs450_hw3
cs450_hw3_EXTERNAL_OBJECTS =

cs450_hw3.exe: CMakeFiles/cs450_hw3.dir/boardvalidate.c.obj
cs450_hw3.exe: CMakeFiles/cs450_hw3.dir/chan.c.obj
cs450_hw3.exe: CMakeFiles/cs450_hw3.dir/main.c.obj
cs450_hw3.exe: CMakeFiles/cs450_hw3.dir/parsetools.c.obj
cs450_hw3.exe: CMakeFiles/cs450_hw3.dir/queue.c.obj
cs450_hw3.exe: CMakeFiles/cs450_hw3.dir/build.make
cs450_hw3.exe: CMakeFiles/cs450_hw3.dir/linklibs.rsp
cs450_hw3.exe: CMakeFiles/cs450_hw3.dir/objects1.rsp
cs450_hw3.exe: CMakeFiles/cs450_hw3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable cs450_hw3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cs450_hw3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cs450_hw3.dir/build: cs450_hw3.exe

.PHONY : CMakeFiles/cs450_hw3.dir/build

CMakeFiles/cs450_hw3.dir/requires: CMakeFiles/cs450_hw3.dir/boardvalidate.c.obj.requires
CMakeFiles/cs450_hw3.dir/requires: CMakeFiles/cs450_hw3.dir/chan.c.obj.requires
CMakeFiles/cs450_hw3.dir/requires: CMakeFiles/cs450_hw3.dir/main.c.obj.requires
CMakeFiles/cs450_hw3.dir/requires: CMakeFiles/cs450_hw3.dir/parsetools.c.obj.requires
CMakeFiles/cs450_hw3.dir/requires: CMakeFiles/cs450_hw3.dir/queue.c.obj.requires

.PHONY : CMakeFiles/cs450_hw3.dir/requires

CMakeFiles/cs450_hw3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cs450_hw3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/cs450_hw3.dir/clean

CMakeFiles/cs450_hw3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3" "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3" "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\cmake-build-debug" "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\cmake-build-debug" "M:\Documents\Documents\SchoolWork\College\CS 450\cs450-hw3\cmake-build-debug\CMakeFiles\cs450_hw3.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/cs450_hw3.dir/depend

