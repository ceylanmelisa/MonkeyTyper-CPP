cmake_minimum_required(VERSION 3.25)

project(MonkeyTyperSFML)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML 2 on macOS
if(APPLE)
    list(PREPEND CMAKE_PREFIX_PATH
            "/opt/homebrew/opt/sfml@2"
    )
endif()

find_package(SFML 2.6 COMPONENTS
        graphics
        window
        system
        REQUIRED
)

add_executable(MonkeyTyperSFML main.cpp)

target_link_libraries(MonkeyTyperSFML PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)

# Copy game resources
foreach(file
        arial.ttf
        comic.ttf
        times.ttf
        words.txt
)
    configure_file(
            "${CMAKE_SOURCE_DIR}/${file}"
            "${CMAKE_BINARY_DIR}/${file}"
            COPYONLY
    )
endforeach()
