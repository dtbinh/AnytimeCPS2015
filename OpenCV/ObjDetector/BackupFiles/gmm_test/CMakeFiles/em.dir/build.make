# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/mlab-retro/Downloads/opencv-3.0.0-beta/release/Workspace/gmm_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mlab-retro/Downloads/opencv-3.0.0-beta/release/Workspace/gmm_test

# Include any dependencies generated for this target.
include CMakeFiles/em.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/em.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/em.dir/flags.make

CMakeFiles/em.dir/em.cpp.o: CMakeFiles/em.dir/flags.make
CMakeFiles/em.dir/em.cpp.o: em.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/mlab-retro/Downloads/opencv-3.0.0-beta/release/Workspace/gmm_test/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/em.dir/em.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/em.dir/em.cpp.o -c /home/mlab-retro/Downloads/opencv-3.0.0-beta/release/Workspace/gmm_test/em.cpp

CMakeFiles/em.dir/em.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/em.dir/em.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/mlab-retro/Downloads/opencv-3.0.0-beta/release/Workspace/gmm_test/em.cpp > CMakeFiles/em.dir/em.cpp.i

CMakeFiles/em.dir/em.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/em.dir/em.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/mlab-retro/Downloads/opencv-3.0.0-beta/release/Workspace/gmm_test/em.cpp -o CMakeFiles/em.dir/em.cpp.s

CMakeFiles/em.dir/em.cpp.o.requires:
.PHONY : CMakeFiles/em.dir/em.cpp.o.requires

CMakeFiles/em.dir/em.cpp.o.provides: CMakeFiles/em.dir/em.cpp.o.requires
	$(MAKE) -f CMakeFiles/em.dir/build.make CMakeFiles/em.dir/em.cpp.o.provides.build
.PHONY : CMakeFiles/em.dir/em.cpp.o.provides

CMakeFiles/em.dir/em.cpp.o.provides.build: CMakeFiles/em.dir/em.cpp.o

# Object files for target em
em_OBJECTS = \
"CMakeFiles/em.dir/em.cpp.o"

# External object files for target em
em_EXTERNAL_OBJECTS =

em: CMakeFiles/em.dir/em.cpp.o
em: CMakeFiles/em.dir/build.make
em: /usr/local/lib/libopencv_videostab.a
em: /usr/local/lib/libopencv_videoio.a
em: /usr/local/lib/libopencv_video.a
em: /usr/local/lib/libopencv_ts.a
em: /usr/local/lib/libopencv_superres.a
em: /usr/local/lib/libopencv_stitching.a
em: /usr/local/lib/libopencv_shape.a
em: /usr/local/lib/libopencv_photo.a
em: /usr/local/lib/libopencv_objdetect.a
em: /usr/local/lib/libopencv_ml.a
em: /usr/local/lib/libopencv_imgproc.a
em: /usr/local/lib/libopencv_imgcodecs.a
em: /usr/local/lib/libopencv_highgui.a
em: /usr/local/lib/libopencv_flann.a
em: /usr/local/lib/libopencv_features2d.a
em: /usr/local/lib/libopencv_core.a
em: /usr/local/lib/libopencv_calib3d.a
em: /usr/local/lib/libopencv_features2d.a
em: /usr/local/lib/libopencv_ml.a
em: /usr/local/lib/libopencv_highgui.a
em: /usr/local/lib/libopencv_videoio.a
em: /usr/local/lib/libopencv_imgcodecs.a
em: /usr/lib/x86_64-linux-gnu/libjpeg.so
em: /usr/lib/x86_64-linux-gnu/libwebp.so
em: /usr/lib/x86_64-linux-gnu/libpng.so
em: /usr/lib/x86_64-linux-gnu/libtiff.so
em: /usr/lib/x86_64-linux-gnu/libjasper.so
em: /usr/lib/x86_64-linux-gnu/libjpeg.so
em: /usr/lib/x86_64-linux-gnu/libwebp.so
em: /usr/lib/x86_64-linux-gnu/libpng.so
em: /usr/lib/x86_64-linux-gnu/libtiff.so
em: /usr/lib/x86_64-linux-gnu/libjasper.so
em: /usr/lib/x86_64-linux-gnu/libImath.so
em: /usr/lib/x86_64-linux-gnu/libIlmImf.so
em: /usr/lib/x86_64-linux-gnu/libIex.so
em: /usr/lib/x86_64-linux-gnu/libHalf.so
em: /usr/lib/x86_64-linux-gnu/libIlmThread.so
em: /usr/local/lib/libopencv_flann.a
em: /usr/local/lib/libopencv_video.a
em: /usr/local/lib/libopencv_imgproc.a
em: /usr/local/lib/libopencv_core.a
em: /usr/lib/x86_64-linux-gnu/libz.so
em: /usr/local/share/OpenCV/3rdparty/lib/libippicv.a
em: CMakeFiles/em.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable em"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/em.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/em.dir/build: em
.PHONY : CMakeFiles/em.dir/build

CMakeFiles/em.dir/requires: CMakeFiles/em.dir/em.cpp.o.requires
.PHONY : CMakeFiles/em.dir/requires

CMakeFiles/em.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/em.dir/cmake_clean.cmake
.PHONY : CMakeFiles/em.dir/clean

CMakeFiles/em.dir/depend:
	cd /home/mlab-retro/Downloads/opencv-3.0.0-beta/release/Workspace/gmm_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mlab-retro/Downloads/opencv-3.0.0-beta/release/Workspace/gmm_test /home/mlab-retro/Downloads/opencv-3.0.0-beta/release/Workspace/gmm_test /home/mlab-retro/Downloads/opencv-3.0.0-beta/release/Workspace/gmm_test /home/mlab-retro/Downloads/opencv-3.0.0-beta/release/Workspace/gmm_test /home/mlab-retro/Downloads/opencv-3.0.0-beta/release/Workspace/gmm_test/CMakeFiles/em.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/em.dir/depend

