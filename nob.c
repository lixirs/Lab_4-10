#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"


// This is optionnal, will default to "build"
// #define BUILD_FOLDER "path/to/build/folder"
// This is optionnal, will default to "Libraries/raylib"
// #define RAYLIB_PATH "./raylib"
// The file will include the implementation by default, if making another noblib_*
// that uses raylib(exemple: rlImGui) and needs it's includes and flags, do :
// #define RAYLIB_NOIMPLEMENTATION 
#include "noblib_raylib.c"

#define LAB_NAME "entrypoint"
int main(int argc, char** argv){
  NOB_GO_REBUILD_URSELF_PLUS(argc, argv,RAYLIB_FILE);
  // ^--- Only needed if you intend on changing the build file, use NOB_GO_REBUILD_URSELF otherwise
  if (!mkdir_if_not_exists("Deployment")){ return 1;}
  if (!mkdir_if_not_exists("build")){ return 1;}
  // ^---- UPDATE THE PATH IF LIBRARIES ARE SOMEWHERE ELSE
  File_Paths o_files = {0};
  if(!build_raylib(&o_files)) return 1;

  Cmd cmd = {0};

  // Use g++ (C++ compiler) instead of cc
  cmd_append(&cmd, "g++");
  cmd_append(&cmd,"-ggdb3");
  cmd_append(&cmd,"-std=c++17");  // Enable C++17 features

  // Automatically append all .cpp files in src/ directory
  const char *src_files[] = {
    "Ball.cpp",
    "Breakout.cpp",
    "Brick.cpp",
    "main.cpp",
    "Paddle.cpp",
    "StartButton.cpp",
    "World.cpp",
    "entrypoint.cpp"
  };
  
  for (size_t i = 0; i < ARRAY_LEN(src_files); ++i) {
    cmd_append(&cmd, temp_sprintf("./src/%s", src_files[i]));
  }

  cmd_append(&cmd,RAYLIB_INCLUDES);
  for(int i =0; i < o_files.count;++i){
      cmd_append(&cmd,o_files.items[i]);
  }
  cmd_append(&cmd, "-o");
  cmd_append(&cmd, "./Deployment/game.exe");
  cmd_append(&cmd,RAYLIB_LFLAGS);
  cmd_append(&cmd, "-lstdc++");  // Link C++ standard library
  if(!cmd_run_sync_and_reset(&cmd)) return 1;
}