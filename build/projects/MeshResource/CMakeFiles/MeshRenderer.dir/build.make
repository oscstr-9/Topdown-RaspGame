# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ogge/Repos/S0017D

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ogge/Repos/S0017D/build

# Include any dependencies generated for this target.
include projects/MeshResource/CMakeFiles/MeshRenderer.dir/depend.make

# Include the progress variables for this target.
include projects/MeshResource/CMakeFiles/MeshRenderer.dir/progress.make

# Include the compile flags for this target's objects.
include projects/MeshResource/CMakeFiles/MeshRenderer.dir/flags.make

projects/MeshResource/CMakeFiles/MeshRenderer.dir/code/Main.cpp.o: projects/MeshResource/CMakeFiles/MeshRenderer.dir/flags.make
projects/MeshResource/CMakeFiles/MeshRenderer.dir/code/Main.cpp.o: ../projects/MeshResource/code/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ogge/Repos/S0017D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object projects/MeshResource/CMakeFiles/MeshRenderer.dir/code/Main.cpp.o"
	cd /home/ogge/Repos/S0017D/build/projects/MeshResource && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MeshRenderer.dir/code/Main.cpp.o -c /home/ogge/Repos/S0017D/projects/MeshResource/code/Main.cpp

projects/MeshResource/CMakeFiles/MeshRenderer.dir/code/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MeshRenderer.dir/code/Main.cpp.i"
	cd /home/ogge/Repos/S0017D/build/projects/MeshResource && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ogge/Repos/S0017D/projects/MeshResource/code/Main.cpp > CMakeFiles/MeshRenderer.dir/code/Main.cpp.i

projects/MeshResource/CMakeFiles/MeshRenderer.dir/code/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MeshRenderer.dir/code/Main.cpp.s"
	cd /home/ogge/Repos/S0017D/build/projects/MeshResource && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ogge/Repos/S0017D/projects/MeshResource/code/Main.cpp -o CMakeFiles/MeshRenderer.dir/code/Main.cpp.s

projects/MeshResource/CMakeFiles/MeshRenderer.dir/code/TestApp.cpp.o: projects/MeshResource/CMakeFiles/MeshRenderer.dir/flags.make
projects/MeshResource/CMakeFiles/MeshRenderer.dir/code/TestApp.cpp.o: ../projects/MeshResource/code/TestApp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ogge/Repos/S0017D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object projects/MeshResource/CMakeFiles/MeshRenderer.dir/code/TestApp.cpp.o"
	cd /home/ogge/Repos/S0017D/build/projects/MeshResource && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MeshRenderer.dir/code/TestApp.cpp.o -c /home/ogge/Repos/S0017D/projects/MeshResource/code/TestApp.cpp

projects/MeshResource/CMakeFiles/MeshRenderer.dir/code/TestApp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MeshRenderer.dir/code/TestApp.cpp.i"
	cd /home/ogge/Repos/S0017D/build/projects/MeshResource && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ogge/Repos/S0017D/projects/MeshResource/code/TestApp.cpp > CMakeFiles/MeshRenderer.dir/code/TestApp.cpp.i

projects/MeshResource/CMakeFiles/MeshRenderer.dir/code/TestApp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MeshRenderer.dir/code/TestApp.cpp.s"
	cd /home/ogge/Repos/S0017D/build/projects/MeshResource && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ogge/Repos/S0017D/projects/MeshResource/code/TestApp.cpp -o CMakeFiles/MeshRenderer.dir/code/TestApp.cpp.s

# Object files for target MeshRenderer
MeshRenderer_OBJECTS = \
"CMakeFiles/MeshRenderer.dir/code/Main.cpp.o" \
"CMakeFiles/MeshRenderer.dir/code/TestApp.cpp.o"

# External object files for target MeshRenderer
MeshRenderer_EXTERNAL_OBJECTS =

projects/MeshResource/MeshRenderer: projects/MeshResource/CMakeFiles/MeshRenderer.dir/code/Main.cpp.o
projects/MeshResource/MeshRenderer: projects/MeshResource/CMakeFiles/MeshRenderer.dir/code/TestApp.cpp.o
projects/MeshResource/MeshRenderer: projects/MeshResource/CMakeFiles/MeshRenderer.dir/build.make
projects/MeshResource/MeshRenderer: engine/core/libcore.a
projects/MeshResource/MeshRenderer: engine/render/librender.a
projects/MeshResource/MeshRenderer: engine/core/libcore.a
projects/MeshResource/MeshRenderer: engine/render/librender.a
projects/MeshResource/MeshRenderer: exts/glew/libglew.a
projects/MeshResource/MeshRenderer: exts/glfw/src/libglfw3.a
projects/MeshResource/MeshRenderer: /usr/lib/x86_64-linux-gnu/librt.so
projects/MeshResource/MeshRenderer: /usr/lib/x86_64-linux-gnu/libm.so
projects/MeshResource/MeshRenderer: /usr/lib/x86_64-linux-gnu/libX11.so
projects/MeshResource/MeshRenderer: /usr/lib/x86_64-linux-gnu/libXrandr.so
projects/MeshResource/MeshRenderer: /usr/lib/x86_64-linux-gnu/libXinerama.so
projects/MeshResource/MeshRenderer: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
projects/MeshResource/MeshRenderer: /usr/lib/x86_64-linux-gnu/libXcursor.so
projects/MeshResource/MeshRenderer: exts/libimgui.a
projects/MeshResource/MeshRenderer: exts/libnanovg.a
projects/MeshResource/MeshRenderer: exts/libimgui.a
projects/MeshResource/MeshRenderer: exts/libnanovg.a
projects/MeshResource/MeshRenderer: projects/MeshResource/CMakeFiles/MeshRenderer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ogge/Repos/S0017D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable MeshRenderer"
	cd /home/ogge/Repos/S0017D/build/projects/MeshResource && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MeshRenderer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
projects/MeshResource/CMakeFiles/MeshRenderer.dir/build: projects/MeshResource/MeshRenderer

.PHONY : projects/MeshResource/CMakeFiles/MeshRenderer.dir/build

projects/MeshResource/CMakeFiles/MeshRenderer.dir/clean:
	cd /home/ogge/Repos/S0017D/build/projects/MeshResource && $(CMAKE_COMMAND) -P CMakeFiles/MeshRenderer.dir/cmake_clean.cmake
.PHONY : projects/MeshResource/CMakeFiles/MeshRenderer.dir/clean

projects/MeshResource/CMakeFiles/MeshRenderer.dir/depend:
	cd /home/ogge/Repos/S0017D/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ogge/Repos/S0017D /home/ogge/Repos/S0017D/projects/MeshResource /home/ogge/Repos/S0017D/build /home/ogge/Repos/S0017D/build/projects/MeshResource /home/ogge/Repos/S0017D/build/projects/MeshResource/CMakeFiles/MeshRenderer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : projects/MeshResource/CMakeFiles/MeshRenderer.dir/depend

