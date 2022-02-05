cmake_minimum_required (VERSION 2.8.12)
project (log4c)

# add flag
add_definitions(-DHAVE_CONFIG_H)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# add var
set(CMAKE_DEBUG_POSTFIX d)
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(ARCH_POSTFIX "Win32")
else()
    set(ARCH_POSTFIX x64)
endif()


IF (CMAKE_BUILD_TYPE MATCHES "Release")
    SET(CMAKE_BUILD_POSTFIX "${CMAKE_RELEASE_POSTFIX}")
ELSEIF (CMAKE_BUILD_TYPE MATCHES "MinSizeRel")
    SET(CMAKE_BUILD_POSTFIX "${CMAKE_MINSIZEREL_POSTFIX}")
ELSEIF(CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
    SET(CMAKE_BUILD_POSTFIX "${CMAKE_RELWITHDEBINFO_POSTFIX}")
ELSEIF(CMAKE_BUILD_TYPE MATCHES "Debug")
    SET(CMAKE_BUILD_POSTFIX "${CMAKE_DEBUG_POSTFIX}")
ELSE()
    SET(CMAKE_BUILD_POSTFIX "")
ENDIF()

# add .c and .cpp
include_directories (./src ./src/log4c ./src/sd )
aux_source_directory (./src/log4c DIR_SRCS1)
aux_source_directory (./src/sd DIR_SRCS2)
list(REMOVE_ITEM DIR_SRCS1 "./src/log4c/appender_type_mmap.c") 
list(REMOVE_ITEM DIR_SRCS1 "./src/log4c/appender_type_mmap.h")  
list(REMOVE_ITEM DIR_SRCS1 "./src/log4c/appender_type_mmap.h")  
list(REMOVE_ITEM DIR_SRCS2 "./src/sd/sprintf.osf.c")  
list(REMOVE_ITEM DIR_SRCS2 "./src/sd/domnode.c")  

# add link dir
link_directories("./libexpat-R_2_4_4/lib/${ARCH_POSTFIX}")

# create dll(project1) or lib(project2)
add_library (log4c_shared SHARED ${DIR_SRCS1} ${DIR_SRCS2})
add_library (log4c_static STATIC ${DIR_SRCS1} ${DIR_SRCS2})
set_target_properties (log4c_shared PROPERTIES OUTPUT_NAME "log4c")
set_target_properties (log4c_static PROPERTIES OUTPUT_NAME "log4c_static")
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/${ARCH_POSTFIX})
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${ARCH_POSTFIX})
target_compile_definitions( log4c_shared PRIVATE LOG4C_EXPORTS )
target_compile_definitions( log4c_static PRIVATE LOG4C_EXPORTS )

# add libexpat library
list(APPEND EXTRA_LIBS libexpat)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/libexpat-R_2_4_4/include")
target_link_libraries(log4c_shared PUBLIC ${EXTRA_LIBS})
target_include_directories(log4c_shared PUBLIC "${PROJECT_BINARY_DIR}" ${EXTRA_INCLUDES})
target_link_libraries(log4c_static PUBLIC ${EXTRA_LIBS})
target_include_directories(log4c_static PUBLIC "${PROJECT_BINARY_DIR}" ${EXTRA_INCLUDES})

# create project3
add_executable(test ./examples/ConsoleApplication1.cpp)


