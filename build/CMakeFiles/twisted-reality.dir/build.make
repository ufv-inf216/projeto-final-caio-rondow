# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/oica/dev/sdl2-projects/projeto-final-caio-rondow

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build

# Include any dependencies generated for this target.
include CMakeFiles/twisted-reality.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/twisted-reality.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/twisted-reality.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/twisted-reality.dir/flags.make

CMakeFiles/twisted-reality.dir/Source/Main.cpp.o: CMakeFiles/twisted-reality.dir/flags.make
CMakeFiles/twisted-reality.dir/Source/Main.cpp.o: ../Source/Main.cpp
CMakeFiles/twisted-reality.dir/Source/Main.cpp.o: CMakeFiles/twisted-reality.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/twisted-reality.dir/Source/Main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/twisted-reality.dir/Source/Main.cpp.o -MF CMakeFiles/twisted-reality.dir/Source/Main.cpp.o.d -o CMakeFiles/twisted-reality.dir/Source/Main.cpp.o -c /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Main.cpp

CMakeFiles/twisted-reality.dir/Source/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twisted-reality.dir/Source/Main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Main.cpp > CMakeFiles/twisted-reality.dir/Source/Main.cpp.i

CMakeFiles/twisted-reality.dir/Source/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twisted-reality.dir/Source/Main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Main.cpp -o CMakeFiles/twisted-reality.dir/Source/Main.cpp.s

CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.o: CMakeFiles/twisted-reality.dir/flags.make
CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.o: ../Source/Utils/Math.cpp
CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.o: CMakeFiles/twisted-reality.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.o -MF CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.o.d -o CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.o -c /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Utils/Math.cpp

CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Utils/Math.cpp > CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.i

CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Utils/Math.cpp -o CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.s

CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.o: CMakeFiles/twisted-reality.dir/flags.make
CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.o: ../Source/Utils/AudioSystem.cpp
CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.o: CMakeFiles/twisted-reality.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.o -MF CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.o.d -o CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.o -c /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Utils/AudioSystem.cpp

CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Utils/AudioSystem.cpp > CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.i

CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Utils/AudioSystem.cpp -o CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.s

CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.o: CMakeFiles/twisted-reality.dir/flags.make
CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.o: ../Source/Game/ConcreteGame.cpp
CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.o: CMakeFiles/twisted-reality.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.o -MF CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.o.d -o CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.o -c /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Game/ConcreteGame.cpp

CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Game/ConcreteGame.cpp > CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.i

CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Game/ConcreteGame.cpp -o CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.s

CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.o: CMakeFiles/twisted-reality.dir/flags.make
CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.o: ../Source/Actors/Actor.cpp
CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.o: CMakeFiles/twisted-reality.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.o -MF CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.o.d -o CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.o -c /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Actors/Actor.cpp

CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Actors/Actor.cpp > CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.i

CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Actors/Actor.cpp -o CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.s

CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.o: CMakeFiles/twisted-reality.dir/flags.make
CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.o: ../Source/Actors/Piece.cpp
CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.o: CMakeFiles/twisted-reality.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.o -MF CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.o.d -o CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.o -c /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Actors/Piece.cpp

CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Actors/Piece.cpp > CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.i

CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Actors/Piece.cpp -o CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.s

CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.o: CMakeFiles/twisted-reality.dir/flags.make
CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.o: ../Source/Actors/Block.cpp
CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.o: CMakeFiles/twisted-reality.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.o -MF CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.o.d -o CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.o -c /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Actors/Block.cpp

CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Actors/Block.cpp > CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.i

CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Actors/Block.cpp -o CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.s

CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.o: CMakeFiles/twisted-reality.dir/flags.make
CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.o: ../Source/Actors/Table.cpp
CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.o: CMakeFiles/twisted-reality.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.o -MF CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.o.d -o CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.o -c /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Actors/Table.cpp

CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Actors/Table.cpp > CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.i

CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Actors/Table.cpp -o CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.s

CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.o: CMakeFiles/twisted-reality.dir/flags.make
CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.o: ../Source/Components/Component.cpp
CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.o: CMakeFiles/twisted-reality.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.o -MF CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.o.d -o CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.o -c /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/Component.cpp

CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/Component.cpp > CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.i

CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/Component.cpp -o CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.s

CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.o: CMakeFiles/twisted-reality.dir/flags.make
CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.o: ../Source/Components/DrawComponents/DrawComponent.cpp
CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.o: CMakeFiles/twisted-reality.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.o -MF CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.o.d -o CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.o -c /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/DrawComponents/DrawComponent.cpp

CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/DrawComponents/DrawComponent.cpp > CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.i

CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/DrawComponents/DrawComponent.cpp -o CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.s

CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.o: CMakeFiles/twisted-reality.dir/flags.make
CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.o: ../Source/Components/DrawComponents/DrawSpriteComponent.cpp
CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.o: CMakeFiles/twisted-reality.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.o -MF CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.o.d -o CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.o -c /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/DrawComponents/DrawSpriteComponent.cpp

CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/DrawComponents/DrawSpriteComponent.cpp > CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.i

CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/DrawComponents/DrawSpriteComponent.cpp -o CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.s

CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.o: CMakeFiles/twisted-reality.dir/flags.make
CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.o: ../Source/Components/DrawComponents/DrawAnimatedComponent.cpp
CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.o: CMakeFiles/twisted-reality.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.o -MF CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.o.d -o CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.o -c /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/DrawComponents/DrawAnimatedComponent.cpp

CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/DrawComponents/DrawAnimatedComponent.cpp > CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.i

CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/DrawComponents/DrawAnimatedComponent.cpp -o CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.s

CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.o: CMakeFiles/twisted-reality.dir/flags.make
CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.o: ../Source/Components/ColliderComponents/AABBColliderComponent.cpp
CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.o: CMakeFiles/twisted-reality.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.o -MF CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.o.d -o CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.o -c /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/ColliderComponents/AABBColliderComponent.cpp

CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/ColliderComponents/AABBColliderComponent.cpp > CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.i

CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/Source/Components/ColliderComponents/AABBColliderComponent.cpp -o CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.s

# Object files for target twisted-reality
twisted__reality_OBJECTS = \
"CMakeFiles/twisted-reality.dir/Source/Main.cpp.o" \
"CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.o" \
"CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.o" \
"CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.o" \
"CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.o" \
"CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.o" \
"CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.o" \
"CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.o" \
"CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.o" \
"CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.o" \
"CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.o" \
"CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.o" \
"CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.o"

# External object files for target twisted-reality
twisted__reality_EXTERNAL_OBJECTS =

twisted-reality: CMakeFiles/twisted-reality.dir/Source/Main.cpp.o
twisted-reality: CMakeFiles/twisted-reality.dir/Source/Utils/Math.cpp.o
twisted-reality: CMakeFiles/twisted-reality.dir/Source/Utils/AudioSystem.cpp.o
twisted-reality: CMakeFiles/twisted-reality.dir/Source/Game/ConcreteGame.cpp.o
twisted-reality: CMakeFiles/twisted-reality.dir/Source/Actors/Actor.cpp.o
twisted-reality: CMakeFiles/twisted-reality.dir/Source/Actors/Piece.cpp.o
twisted-reality: CMakeFiles/twisted-reality.dir/Source/Actors/Block.cpp.o
twisted-reality: CMakeFiles/twisted-reality.dir/Source/Actors/Table.cpp.o
twisted-reality: CMakeFiles/twisted-reality.dir/Source/Components/Component.cpp.o
twisted-reality: CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawComponent.cpp.o
twisted-reality: CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawSpriteComponent.cpp.o
twisted-reality: CMakeFiles/twisted-reality.dir/Source/Components/DrawComponents/DrawAnimatedComponent.cpp.o
twisted-reality: CMakeFiles/twisted-reality.dir/Source/Components/ColliderComponents/AABBColliderComponent.cpp.o
twisted-reality: CMakeFiles/twisted-reality.dir/build.make
twisted-reality: /opt/SDL2/lib/libSDL2.so
twisted-reality: /opt/SDL2_image/lib/libSDL2_image.so
twisted-reality: /opt/SDL2_mixer/lib/libSDL2_mixer.so
twisted-reality: CMakeFiles/twisted-reality.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable twisted-reality"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/twisted-reality.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/twisted-reality.dir/build: twisted-reality
.PHONY : CMakeFiles/twisted-reality.dir/build

CMakeFiles/twisted-reality.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/twisted-reality.dir/cmake_clean.cmake
.PHONY : CMakeFiles/twisted-reality.dir/clean

CMakeFiles/twisted-reality.dir/depend:
	cd /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oica/dev/sdl2-projects/projeto-final-caio-rondow /home/oica/dev/sdl2-projects/projeto-final-caio-rondow /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build /home/oica/dev/sdl2-projects/projeto-final-caio-rondow/build/CMakeFiles/twisted-reality.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/twisted-reality.dir/depend

