cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

function(BUILD_LIBRARY Name)
    string(TOUPPER ${Name} NAME)
    set(SOURCES ${${NAME}_SOURCES})
    set(HEADERS ${${NAME}_HEADERS})
    set(PUBLIC_HEADERS ${${NAME}_PUBLIC_HEADERS})
    set(LINK_LIBRARIES ${${NAME}_LINK_LIBRARIES})
    string(REGEX REPLACE "^lib" "" OUTPUTNAME ${Name})

    add_library(${Name} STATIC ${SOURCES} ${HEADERS} ${PUBLIC_HEADERS})
    target_link_libraries(${Name} ${LINK_LIBRARIES})
    set_target_properties(${Name} PROPERTIES OUTPUT_NAME ${OUTPUTNAME})
endfunction()

function(BUILD_APPLICATION Name)
    string(TOUPPER ${Name} NAME)
    set(SOURCES ${${NAME}_SOURCES})
    set(HEADERS ${${NAME}_HEADERS})
    set(LINK_LIBRARIES ${${NAME}_LINK_LIBRARIES})

    add_executable(${Name} ${SOURCES} ${HEADERS})
    target_link_libraries(${Name} ${LINK_LIBRARIES})
endfunction()

function(BUILD_UNITTEST Name)
    string(TOUPPER ${Name} NAME)
    set(SOURCES ${${NAME}_SOURCES})
    set(HEADERS ${${NAME}_HEADERS})
    set(LINK_LIBRARIES ${${NAME}_LINK_LIBRARIES})

    add_executable(${Name} ${SOURCES} ${HEADERS})
    target_link_libraries(${Name} ${LINK_LIBRARIES})
    add_custom_command(TARGET ${Name}
        POST_BUILD
        COMMAND ${Name}
    )
endfunction()

#Set version info
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
if(VERSION_PRERELEASE)
    set(VERSION ${VERSION}-${VERSION_PRERELEASE})
endif()
if(VERSION_BUILDMETADATA)
    set(VERSION ${VERSION}+${VERSION_BUILDMETADATA})
endif()

#Add default compiler stuff
set(COMMON_GCC_FLAGS "-Wall -Wextra -Werror -Winvalid-pch -Winit-self -Wno-unknown-pragmas")

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_GCC_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_GCC_FLAGS} -Wsign-promo -Wvla")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuninitialized")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

