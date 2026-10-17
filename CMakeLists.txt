cmake_minimum_required(VERSION 3.25)
project(MonkeyTyperSFML)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_VERSION                2.5.1)
set(SFML_ZIP_URL                "https://www.sfml-dev.org/files/SFML-${SFML_VERSION}-windows-gcc-7.3.0-mingw-64-bit.zip")
set(SFML_ZIP_MD5                "57fa9ce9c0cd96d2570f8f845d80e3be")  # official checksum
set(SFML_EXTRACT_DIR            "${CMAKE_SOURCE_DIR}/_deps/sfml-${SFML_VERSION}")
set(SFML_INSTALL_SUBDIR         "SFML-${SFML_VERSION}")

configure_file("${CMAKE_SOURCE_DIR}/times.ttf" "${CMAKE_BINARY_DIR}/times.ttf" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/arial.ttf" "${CMAKE_BINARY_DIR}/arial.ttf" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/comic.ttf" "${CMAKE_BINARY_DIR}/comic.ttf" COPYONLY)


include(FetchContent)

set(sfml_zip "${CMAKE_BINARY_DIR}/_deps/sfml-${SFML_VERSION}.zip")
file(DOWNLOAD
        "${SFML_ZIP_URL}"
        "${sfml_zip}"
        EXPECTED_MD5 "${SFML_ZIP_MD5}"
        SHOW_PROGRESS
)

if(EXISTS "${SFML_EXTRACT_DIR}")
    message(STATUS "Extracting SFML to ${SFML_EXTRACT_DIR}")
    file(MAKE_DIRECTORY "${SFML_EXTRACT_DIR}")
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xzf "${sfml_zip}"
            WORKING_DIRECTORY "${SFML_EXTRACT_DIR}"
    )
endif()

set(SFML_DIR "${SFML_EXTRACT_DIR}/${SFML_INSTALL_SUBDIR}/lib/cmake/SFML")

message(STATUS "SFML downloaded/extracted; SFML_DIR = ${SFML_DIR}")

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(MonkeyTyperSFML main.cpp)

target_link_libraries(MonkeyTyperSFML PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)
