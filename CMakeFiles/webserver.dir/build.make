# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /opt/cmake-3.21.4/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.21.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wrz/share/myWebServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wrz/share/myWebServer

# Include any dependencies generated for this target.
include CMakeFiles/webserver.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/webserver.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/webserver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/webserver.dir/flags.make

CMakeFiles/webserver.dir/version_0.3/src/main.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/version_0.3/src/main.cpp.o: version_0.3/src/main.cpp
CMakeFiles/webserver.dir/version_0.3/src/main.cpp.o: CMakeFiles/webserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wrz/share/myWebServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/webserver.dir/version_0.3/src/main.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserver.dir/version_0.3/src/main.cpp.o -MF CMakeFiles/webserver.dir/version_0.3/src/main.cpp.o.d -o CMakeFiles/webserver.dir/version_0.3/src/main.cpp.o -c /home/wrz/share/myWebServer/version_0.3/src/main.cpp

CMakeFiles/webserver.dir/version_0.3/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/version_0.3/src/main.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wrz/share/myWebServer/version_0.3/src/main.cpp > CMakeFiles/webserver.dir/version_0.3/src/main.cpp.i

CMakeFiles/webserver.dir/version_0.3/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/version_0.3/src/main.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wrz/share/myWebServer/version_0.3/src/main.cpp -o CMakeFiles/webserver.dir/version_0.3/src/main.cpp.s

CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.o: version_0.3/src/ntyreactor.cpp
CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.o: CMakeFiles/webserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wrz/share/myWebServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.o -MF CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.o.d -o CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.o -c /home/wrz/share/myWebServer/version_0.3/src/ntyreactor.cpp

CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wrz/share/myWebServer/version_0.3/src/ntyreactor.cpp > CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.i

CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wrz/share/myWebServer/version_0.3/src/ntyreactor.cpp -o CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.s

CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.o: version_0.3/src/export_fun.cpp
CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.o: CMakeFiles/webserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wrz/share/myWebServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.o -MF CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.o.d -o CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.o -c /home/wrz/share/myWebServer/version_0.3/src/export_fun.cpp

CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wrz/share/myWebServer/version_0.3/src/export_fun.cpp > CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.i

CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wrz/share/myWebServer/version_0.3/src/export_fun.cpp -o CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.s

CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.o: version_0.3/src/thread_pool.cpp
CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.o: CMakeFiles/webserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wrz/share/myWebServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.o -MF CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.o.d -o CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.o -c /home/wrz/share/myWebServer/version_0.3/src/thread_pool.cpp

CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wrz/share/myWebServer/version_0.3/src/thread_pool.cpp > CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.i

CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wrz/share/myWebServer/version_0.3/src/thread_pool.cpp -o CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.s

CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.o: version_0.3/src/deadlock_sucess.cpp
CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.o: CMakeFiles/webserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wrz/share/myWebServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.o -MF CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.o.d -o CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.o -c /home/wrz/share/myWebServer/version_0.3/src/deadlock_sucess.cpp

CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wrz/share/myWebServer/version_0.3/src/deadlock_sucess.cpp > CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.i

CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wrz/share/myWebServer/version_0.3/src/deadlock_sucess.cpp -o CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.s

# Object files for target webserver
webserver_OBJECTS = \
"CMakeFiles/webserver.dir/version_0.3/src/main.cpp.o" \
"CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.o" \
"CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.o" \
"CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.o" \
"CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.o"

# External object files for target webserver
webserver_EXTERNAL_OBJECTS =

webserver: CMakeFiles/webserver.dir/version_0.3/src/main.cpp.o
webserver: CMakeFiles/webserver.dir/version_0.3/src/ntyreactor.cpp.o
webserver: CMakeFiles/webserver.dir/version_0.3/src/export_fun.cpp.o
webserver: CMakeFiles/webserver.dir/version_0.3/src/thread_pool.cpp.o
webserver: CMakeFiles/webserver.dir/version_0.3/src/deadlock_sucess.cpp.o
webserver: CMakeFiles/webserver.dir/build.make
webserver: CMakeFiles/webserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wrz/share/myWebServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable webserver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/webserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/webserver.dir/build: webserver
.PHONY : CMakeFiles/webserver.dir/build

CMakeFiles/webserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/webserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/webserver.dir/clean

CMakeFiles/webserver.dir/depend:
	cd /home/wrz/share/myWebServer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wrz/share/myWebServer /home/wrz/share/myWebServer /home/wrz/share/myWebServer /home/wrz/share/myWebServer /home/wrz/share/myWebServer/CMakeFiles/webserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/webserver.dir/depend
