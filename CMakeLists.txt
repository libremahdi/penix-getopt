cmake_minimum_required(VERSION 3.10)
project(pgetopt VERSION 4.2 LANGUAGES C)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src/lib)
include_directories(${PROJECT_SOURCE_DIR}/src/lib/mem_manage)

set(SOURCES
    src/pclass.c
    src/pinit.c
    src/pkey.c
    src/perror.c
    src/lib/mem_manage/salloc.c
)

add_library(pgetopt_static STATIC ${SOURCES})
add_library(pgetopt_shared SHARED ${SOURCES})

set_target_properties(pgetopt_shared PROPERTIES OUTPUT_NAME pgetopt)
set_target_properties(pgetopt_static PROPERTIES OUTPUT_NAME pgetopt)

install(TARGETS pgetopt_shared pgetopt_static
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(DIRECTORY include/ DESTINATION include/pgetopt-${PROJECT_VERSION})

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_INSTALL_PREFIX}/lib/libpgetopt.a
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_INSTALL_PREFIX}/lib/libpgetopt.so
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_INSTALL_PREFIX}/include/pgetopt-${PROJECT_VERSION}
)