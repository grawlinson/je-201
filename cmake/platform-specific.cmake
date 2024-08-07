if(APPLE)
  # universal binary
  set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
  # minimum macOS version
  set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum macOS version" FORCE)
endif()

if(WIN32)
  # static linking by default
  cmake_policy(SET CMP0091 NEW)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE INTERNAL "")
endif()

if(LINUX)
endif()
