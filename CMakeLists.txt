cmake_minimum_required(VERSION 3.0)
project(gui-test CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Adding Raylib
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(raylib)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp") 
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/") 

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})

#if(${PLATFORM} STREQUAL "Web")
if (EMSCRIPTEN)
  set_target_properties(${PROJECT_NAME}
          PROPERTIES SUFFIX ".html"
          LINK_FLAGS " --bind -s WASM=0 -s MIN_WEBGL_VERSION=1 -s ABORT_ON_WASM_EXCEPTIONS=1 -g2 -s USE_GLFW=3 --shell-file ${CMAKE_SOURCE_DIR}/src/minshell.html")
endif()

#
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
#    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
#endif ()

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /WX /W4)
  target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
  
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
  set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
  
  file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.h")
  source_group("Header Files" FILES ${PROJECT_HEADERS})
  target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_HEADERS})
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror -Wno-unused-variable -Wno-unused-parameter -Wno-unused-but-set-variable)
  target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
endif()
