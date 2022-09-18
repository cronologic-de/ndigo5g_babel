cmake_minimum_required(VERSION 3.12)
set(CRONO_TARGET_NAME "ndigo_250M_ugex")
project(${CRONO_TARGET_NAME})

# _____________________________________________________________________________
# Build Windows(x86/x86_64)/Linux(x86_64) `ndigo_250M_ugex.exe/Linux` executable, 
# for (Debug/Release) configurations.
# _____________________________________________________________________________

# General Validations and Configurations ======================================

# cd indirection from /tools to the project source code, "." if no shift
set(PROJ_SRC_INDIR ..)  

# Get the platform and architecure ____________________________________________
# Check supported architecture, and set `CRONO_GEN_ARCH` to `x86_64` for all
# variations of `x64` platforms, and to `x86` for all variations of `x86` 
# platforms.
# Set `CRONO_GEN_PLATFORM` to either `windows` or `linux`
SET(CRONO_GEN_PLATFORM "windows")
IF(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(CRONO_GEN_PLATFORM "linux")
ENDIF()

list(APPEND x64_archs Win64 AMD64 X86 x86_64)
IF(CMAKE_GENERATOR_PLATFORM STREQUAL "Win32")
        set(CRONO_GEN_ARCH "x86")
ELSEIF(CMAKE_SYSTEM_PROCESSOR IN_LIST x64_archs)
        set(CRONO_GEN_ARCH "x86_64")
ENDIF()

# Dependency directories ______________________________________________________
set(CRONO_DEP_PKG_DIR           
        ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_SRC_INDIR}/driver)
set(CRONO_DEP_PKG_INC_DIR       ${CRONO_DEP_PKG_DIR}/include)

# Include directories paths ___________________________________________________
include_directories(${CRONO_TARGET_NAME} PRIVATE ${CRONO_DEP_PKG_INC_DIR})

# Link to ndigo_driver library ________________________________________
IF(CRONO_GEN_ARCH STREQUAL "x86" AND CRONO_GEN_PLATFORM STREQUAL "windows")
        add_library(ndigo_driver SHARED IMPORTED GLOBAL)
        set_target_properties(ndigo_driver PROPERTIES IMPORTED_IMPLIB 
                ndigo_driver.lib)  
        set(CRONO_DEP_PKG_LIB_DIR ${CRONO_DEP_PKG_DIR}/x86)
        set(CRONO_NDIGO_250M_LIB_NAME ndigo_driver.lib)
ELSEIF(CRONO_GEN_ARCH STREQUAL "x86_64" AND CRONO_GEN_PLATFORM STREQUAL "windows")
        add_library(ndigo_driver_64 SHARED IMPORTED GLOBAL)
        set_target_properties(ndigo_driver_64 PROPERTIES IMPORTED_IMPLIB 
                ndigo_driver_64.lib)  
        set(CRONO_DEP_PKG_LIB_DIR ${CRONO_DEP_PKG_DIR}/x64)
        set(CRONO_NDIGO_250M_LIB_NAME ndigo_driver_64.lib)
ELSEIF(CRONO_GEN_PLATFORM STREQUAL "linux")
        set(CRONO_DEP_PKG_LIB_DIR ${CRONO_DEP_PKG_DIR}/x64)
        set(CRONO_NDIGO_250M_LIB_NAME ndigo_driver.a)
ENDIF()
link_directories(${CRONO_DEP_PKG_LIB_DIR})

# Set output directory_________________________________________________________
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CRONO_DEP_PKG_LIB_DIR})

# Validate that directories exist _____________________________________________
IF(     NOT EXISTS "${CRONO_DEP_PKG_LIB_DIR}" 
     OR NOT EXISTS "${CRONO_DEP_PKG_INC_DIR}"
) 
        message(FATAL_ERROR 
                "Crono: Please copy driver installation folder driver to the project root. "
"Lib: <${CRONO_DEP_PKG_LIB_DIR}>, Include: <${CRONO_DEP_PKG_INC_DIR}>.")
ENDIF()
        
# Add the EXE ytarget  ________________________________________________________
add_executable(${CRONO_TARGET_NAME} 
        ${PROJ_SRC_INDIR}/src/ndigo_user_guide_example_250M.cpp)

# Windows-specific Configurations _____________________________________________
IF ( CRONO_GEN_PLATFORM  STREQUAL "windows")
        IF( CRONO_GEN_ARCH STREQUAL "x86" 
            AND CRONO_GEN_PLATFORM STREQUAL "windows")
                target_link_libraries(${CRONO_TARGET_NAME} ndigo_driver)
        ELSEIF( CRONO_GEN_ARCH STREQUAL "x86_64" 
                AND CRONO_GEN_PLATFORM STREQUAL "windows")
                target_link_libraries(${CRONO_TARGET_NAME} ndigo_driver_64)
        ENDIF()

        # Command that copies the corresponding library to the output folder
        string(
        APPEND _copy_cmd
                "xcopy;/c;/f;/y;\"${CRONO_DEP_PKG_LIB_DIR}/*.*\";"
                "\"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<IF:$<CONFIG:Debug>,Debug,Release>\""
        )
        # Copy library to executable directory to run and debug
        add_custom_command(TARGET ${CRONO_TARGET_NAME} POST_BUILD 
                COMMAND "${_copy_cmd}"
                COMMAND_EXPAND_LISTS
        )

# Linux-specific Configurations _______________________________________________
ELSEIF (CRONO_GEN_PLATFORM STREQUAL "linux") 
        # Compilation options 
        IF(NOT CMAKE_BUILD_TYPE)
                message(STATUS  
                        "Crono: assuming build type is `Release` as none was specified.")
                set(CMAKE_BUILD_TYPE Release)
        ENDIF()
        IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
                add_compile_options(-Wall -g>)
                add_compile_definitions(CRONO_DEBUG_ENABLED)
        ENDIF()

        # Adjust .o files names, remove .cpp from .o file name
        set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON) 
        
        # Link to ndigo_driver library 
        add_library(ndigo_driver STATIC IMPORTED GLOBAL)
        set_target_properties(ndigo_driver PROPERTIES IMPORTED_IMPLIB ndigo_driver.a)  
        target_link_libraries(${CRONO_TARGET_NAME} ndigo_driver.a)

        # Rename the library with prefix `lib` for the linker to find it
        add_custom_command(TARGET ${CRONO_TARGET_NAME} PRE_BUILD 
                COMMAND "cp" ${CRONO_DEP_PKG_LIB_DIR}/ndigo_driver.a 
                        ${CRONO_DEP_PKG_LIB_DIR}/libndigo_driver.a)
        
        # No need to copy ndigo_driver.a to output folder similar to Windows
        # as it's statically linked.
ENDIF()
