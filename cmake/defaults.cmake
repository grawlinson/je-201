# set CXX standard
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)

# set Release if build type isn't defined
if(NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

# avoid issues with binary data + fPIC
# https://forum.juce.com/t/linux-cmake-and-fpic/54149
# https://forum.juce.com/t/add-extra-compiler-flags-in-cmake-workflow/47708/2
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND UNIX AND NOT APPLE AND NOT JE201_SKIP_PIE_CHANGE)
  message(STATUS "Setting -no-pie on EXE flags; use JE201_SKIP_PIE_CHANGE=TRUE to avoid" )
  set(CMAKE_EXE_LINKER_FLAGS "-no-pie")
endif()
