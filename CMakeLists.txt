cmake_minimum_required(VERSION 3.29.2)

set(PROGRAM_VERSION_NUMBER 1.2.0.0)

project("KalaMove" VERSION ${PROGRAM_VERSION_NUMBER} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Platform Detection
if (WIN32)
    message(STATUS "[KALAMOVE] Platform = Windows")
else()
    message(FATAL_ERROR "[KALAMOVE] Unsupported platform. Only Windows is supported.")
endif()

# Build Type Detection
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(IS_DEBUG TRUE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(IS_RELEASE TRUE)
else()
    message(FATAL_ERROR "Unknown CMAKE_BUILD_TYPE: '${CMAKE_BUILD_TYPE}'! Must be Debug, Release, or RelWithDebInfo.")
endif()

# Runtime lib handling for MSVC
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

# Directory Setup
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(EXT_SHARED_DIR "${CMAKE_SOURCE_DIR}/_external_shared")

set(EXT_CLI_DIR "${EXT_SHARED_DIR}/KalaCLI")

# Library Paths
if(IS_RELEASE)
    set(CLI_LIBRARY_PATH "${EXT_CLI_DIR}/release/_KalaCLI1.lib")
else()
    set(CLI_LIBRARY_PATH "${EXT_CLI_DIR}/debug/_KalaCLI1d.lib")
endif()

# Source Files
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*/*.cpp"
)

# Executable
add_executable(KalaMove ${SOURCE_FILES})

# Enable exception handling for MSVC
if (MSVC)
    target_compile_options(KalaMove PRIVATE /EHsc)
endif()

set_target_properties(KalaMove PROPERTIES OUTPUT_NAME "KalaMove")
target_compile_features(KalaMove PRIVATE cxx_std_20)

# Includes
file(GLOB_RECURSE HEADERS
	configure_depends
	"${CMAKE_SOURCE_DIR}/include/*.hpp"
)
target_sources(KalaMove PRIVATE ${HEADERS})
target_include_directories(KalaMove PRIVATE
	"${INCLUDE_DIR}"
	"${EXT_SHARED_DIR}"
	"${EXT_SHARED_DIR}/KalaCLI/include"
)

# Preprocessor Defines
target_compile_definitions(KalaMove PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)

# Link libraries
target_link_libraries(KalaMove PRIVATE
	${CLI_LIBRARY_PATH})

# Hide console in release mode
#if(IS_RELEASE)
#    set_target_properties(KalaMove PROPERTIES WIN32_EXECUTABLE TRUE)
#    if (MSVC)
#        set_target_properties(KalaMove PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
#    endif()
#endif()

# Installation
set(CMAKE_INSTALL_BINDIR bin)
install(TARGETS KalaMove DESTINATION ${CMAKE_INSTALL_BINDIR})

# Copy external binaries
if(IS_RELEASE)
	set(BIN_KALACLI "${EXT_CLI_DIR}/release")
else()
	set(BIN_KALACLI "${EXT_CLI_DIR}/debug")
endif()

if (IS_RELEASE)
	file(GLOB BIN_FILES
		"${BIN_KALACLI}/*.dll"
	)
else()
	file(GLOB BIN_FILES
		"${BIN_KALACLI}/*.dll"
		"${BIN_KALACLI}/*.pdb"
	)
endif()

set(BIN_TARGET_DIR "$<TARGET_FILE_DIR:KalaMove>")

foreach(BIN_FILE ${BIN_FILES})
    get_filename_component(BIN_NAME ${BIN_FILE} NAME)
    add_custom_command(TARGET KalaMove POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy 
			"${BIN_FILE}"
			"${BIN_TARGET_DIR}/${BIN_NAME}"
    )
endforeach()

# Copy important files
set(COPY_TARGETS README.md LICENSE.md CHANGES.md)
foreach(FILE ${COPY_TARGETS})
add_custom_command(TARGET KalaMove POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E rm -f 
        "$<TARGET_FILE_DIR:KalaMove>/${FILE}"
    COMMAND ${CMAKE_COMMAND} -E copy
		"${CMAKE_SOURCE_DIR}/${FILE}"
		"$<TARGET_FILE_DIR:KalaMove>/${FILE}"
)
endforeach()

# Package
include(CPack)
