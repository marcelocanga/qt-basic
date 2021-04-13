cmake_minimum_required(VERSION 3.8.2)

set(myapp helloworld)
project(${myapp}  CXX Fortran C)
#
#*********************************************      system libraries
#
#.............................................     windows cross compiler
#
if( ${U_ARCH} MATCHES  cros_64 )

 set(CMAKE_SYSTEM_NAME WindowsStore)
 set(CMAKE_SYSTEM_VERSION 10.0)
 set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
 set(CMAKE_FIND_LIBRARY_PREFIXES "lib")

 include_directories ( src/inc )
 
 find_library(GLPK_LIB      NAMES glpk   )
 find_library(BLAS_LIB      NAMES blas   )
 find_library(LAPACK_LIB    NAMES lapack )
 find_library(READLINE_LIB  NAMES readline )

 MESSAGE("CROS GLPK library ${GLPK_LIB}")
 MESSAGE("BLAS_FOUND ${BLAS_LIB}")
 MESSAGE("LAPACK_FOUND ${LAPACK_LIB}")
 MESSAGE("CMAKE_Fortran_COMPILER  ${CMAKE_Fortran_COMPILER}")

endif()
#.............................................      linux
#

if(${U_ARCH} MATCHES  linux )

 include_directories ( src/inc )

 find_library(GLPK_LIB      NAMES libglpk.a   HINTS  lib/linux  )
 find_library(BLAS_LIB      NAMES blas        HINTS /usr/lib )
 find_library(LAPACK_LIB    NAMES lapack      HINTS /usr/lib )
 find_library(READLINE_LIB  NAMES readline    HINTS /usr/lib )

 MESSAGE("the GLPK library ${GLPK_LIB}")
 
endif()
#.............................................      macos
#

if(${U_ARCH} MATCHES  mac_64 )

 include_directories ( src/inc )

 find_library(GLPK_LIB  NAMES libglpk.a     HINTS  lib/mac_64  )
 find_library(BLAS_LIB      NAMES blas      HINTS /usr/lib )
 find_library(LAPACK_LIB    NAMES lapack    HINTS /usr/lib )
 find_library(READLINE_LIB  NAMES readline  HINTS /usr/lib )

 MESSAGE("the GLPK library ${GLPK_LIB}")
 
endif()
#.............................................      windows 10 msys
#
if( ${U_ARCH} MATCHES  msys  )

 include_directories ( src/inc )

 find_library(GLPK_LIB      NAMES libglpk.a    )
 find_library(BLAS_LIB      NAMES libblas.a    )
 find_library(LAPACK_LIB    NAMES liblapack.a  )
 find_library(READLINE_LIB  NAMES libreadline.a)

 MESSAGE("the GLPK library ${GLPK_LIB}")

endif()
#
#*********************************************      package libraries
#
#.............................................      qt
#
find_package(Qt5  COMPONENTS Widgets OpenGL PrintSupport Qml Quick Concurrent  REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
#.............................................      opengl
#
find_package(OpenGL REQUIRED)
MESSAGE("the GL library ${OPENGL_LIBRARIES}") 
#
#*********************************************      system options
#
# Make this a GUI application on Windows
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()
#
#*********************************************      target
#

message("CMAKE_PREFIX_PATH:" ${CMAKE_PREFIX_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin) 

add_executable(${myapp}  src/main.cpp src/test.f src/mainwindow.cpp src/mainwindow.ui src/src2/test2.f src/resources.qrc )

target_link_libraries(${myapp}  -L${CMAKE_CURRENT_SOURCE_DIR}/lib/${U_ARCH} ${OPENGL_LIBRARIES} ${GLPK_LIB} ${READLINE_LIB} ${LAPACK_LIB} ${BLAS_LIB}   Qt5::Widgets Qt5::OpenGL Qt5::PrintSupport Qt5::Qml Qt5::Quick Qt5::Concurrent )

set_target_properties(${myapp}  PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS ${myapp} DESTINATION bin)
#
#*********************************************      
#
