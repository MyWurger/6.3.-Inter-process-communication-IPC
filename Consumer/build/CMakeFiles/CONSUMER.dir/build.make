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
CMAKE_SOURCE_DIR = "/home/dmitru/Проекты VisualCode/Shared_memory/Consumer"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/dmitru/Проекты VisualCode/Shared_memory/Consumer/build"

# Include any dependencies generated for this target.
include CMakeFiles/CONSUMER.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CONSUMER.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CONSUMER.dir/flags.make

CMakeFiles/CONSUMER.dir/main.c.o: CMakeFiles/CONSUMER.dir/flags.make
CMakeFiles/CONSUMER.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dmitru/Проекты VisualCode/Shared_memory/Consumer/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CONSUMER.dir/main.c.o"
	gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/CONSUMER.dir/main.c.o   -c "/home/dmitru/Проекты VisualCode/Shared_memory/Consumer/main.c"

CMakeFiles/CONSUMER.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CONSUMER.dir/main.c.i"
	gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dmitru/Проекты VisualCode/Shared_memory/Consumer/main.c" > CMakeFiles/CONSUMER.dir/main.c.i

CMakeFiles/CONSUMER.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CONSUMER.dir/main.c.s"
	gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dmitru/Проекты VisualCode/Shared_memory/Consumer/main.c" -o CMakeFiles/CONSUMER.dir/main.c.s

# Object files for target CONSUMER
CONSUMER_OBJECTS = \
"CMakeFiles/CONSUMER.dir/main.c.o"

# External object files for target CONSUMER
CONSUMER_EXTERNAL_OBJECTS =

CONSUMER: CMakeFiles/CONSUMER.dir/main.c.o
CONSUMER: CMakeFiles/CONSUMER.dir/build.make
CONSUMER: CMakeFiles/CONSUMER.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/dmitru/Проекты VisualCode/Shared_memory/Consumer/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable CONSUMER"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CONSUMER.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Копирование PROVIDER в директорию сборки"
	/usr/bin/cmake -E copy_if_different /home/dmitru/PROVIDER /home/dmitru/Проекты\ VisualCode/Shared_memory/Consumer/build

# Rule to build all files generated by this target.
CMakeFiles/CONSUMER.dir/build: CONSUMER

.PHONY : CMakeFiles/CONSUMER.dir/build

CMakeFiles/CONSUMER.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CONSUMER.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CONSUMER.dir/clean

CMakeFiles/CONSUMER.dir/depend:
	cd "/home/dmitru/Проекты VisualCode/Shared_memory/Consumer/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/dmitru/Проекты VisualCode/Shared_memory/Consumer" "/home/dmitru/Проекты VisualCode/Shared_memory/Consumer" "/home/dmitru/Проекты VisualCode/Shared_memory/Consumer/build" "/home/dmitru/Проекты VisualCode/Shared_memory/Consumer/build" "/home/dmitru/Проекты VisualCode/Shared_memory/Consumer/build/CMakeFiles/CONSUMER.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/CONSUMER.dir/depend

