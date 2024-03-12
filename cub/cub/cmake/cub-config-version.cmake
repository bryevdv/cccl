# Parse version information from version.cuh:
include("${CMAKE_CURRENT_LIST_DIR}/cub-header-search.cmake")

set(CUB_VERSION_MAJOR 2)
set(CUB_VERSION_MINOR 3)
set(CUB_VERSION_PATCH 2)
set(CUB_VERSION_TWEAK 0)
set(CUB_VERSION "${CUB_VERSION_MAJOR}.${CUB_VERSION_MINOR}.${CUB_VERSION_PATCH}.${CUB_VERSION_TWEAK}")

set(PACKAGE_VERSION ${CUB_VERSION})
set(PACKAGE_VERSION_COMPATIBLE FALSE)
set(PACKAGE_VERSION_EXACT FALSE)
set(PACKAGE_VERSION_UNSUITABLE FALSE)

if(PACKAGE_VERSION VERSION_GREATER_EQUAL PACKAGE_FIND_VERSION)
  if(CUB_VERSION_MAJOR VERSION_EQUAL PACKAGE_FIND_VERSION_MAJOR AND
     CUB_VERSION_MINOR VERSION_GREATER_EQUAL PACKAGE_FIND_VERSION_MINOR)
    set(PACKAGE_VERSION_COMPATIBLE TRUE)
  endif()

  if(PACKAGE_FIND_VERSION VERSION_EQUAL PACKAGE_VERSION)
    set(PACKAGE_VERSION_EXACT TRUE)
  endif()
endif()
