cmake_minimum_required(VERSION 3.10)
project(pgetopt VERSION 4.3 LANGUAGES C)

# Set C standard and prevent compilation if not supported
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Internal include directories for the build process
# These paths are needed to resolve headers during compilation
include_directories(
    include
    src/lib
    src/pclass
    src/pinit
)

# Define source files based on the new project structure
set(SOURCES
    src/pclass.c
    src/perror.c
    src/pinit.c
    # Files in src/lib
    src/lib/alloc.c
    src/lib/popt_class.c
    src/lib/popt_error.c
    src/lib/popt_init.c
    # Files in src/pclass
    src/pclass/pclass_key.c
    src/pclass/pclass_loop_get_opt_id.c
    src/pclass/pclass_set_allowed_options.c
    # Files in src/pinit
    src/pinit/pinit_master.c
    src/pinit/pinit_parser.c
    src/pinit/pinit_set_main_class.c
)

# Create Static and Shared library targets
add_library(pgetopt_static STATIC ${SOURCES})
add_library(pgetopt_shared SHARED ${SOURCES})

# Set output names to libpgetopt.a and libpgetopt.so
set_target_properties(pgetopt_static PROPERTIES OUTPUT_NAME pgetopt)
set_target_properties(pgetopt_shared PROPERTIES OUTPUT_NAME pgetopt)

# --- Installation Logic ---

# Install library binaries to the system lib directory
install(TARGETS pgetopt_shared pgetopt_static
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

# Install ONLY the public API header
# This prevents internal headers like master.h or branch.h from being exposed to the user
install(FILES include/pgetopt.h 
        DESTINATION include/pgetopt-${PROJECT_VERSION})

# --- Uninstall Target ---

# Custom command to remove installed files and directories
add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_INSTALL_PREFIX}/lib/libpgetopt.a
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_INSTALL_PREFIX}/lib/libpgetopt.so
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_INSTALL_PREFIX}/include/pgetopt-${PROJECT_VERSION}
)