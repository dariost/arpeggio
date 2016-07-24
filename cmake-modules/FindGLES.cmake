find_path(GLES_INCLUDES "GLES3/gl3.h"
          HINTS ${CMAKE_INSTALL_PREFIX}
          PATH_SUFFIXES include)

find_library(GLES_LIBRARIES "GLESv3" "GLESv2"
             HINTS ${CMAKE_INSTALL_PREFIX}
             PATH_SUFFIXES lib lib64 lib32)

if(GLES_INCLUDES AND GLES_LIBRARIES)
    set(GLES_FOUND TRUE)
else()
    set(GLES_FOUND FALSE)
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(GLES DEFAULT_MSG GLES_LIBRARIES GLES_INCLUDES)
