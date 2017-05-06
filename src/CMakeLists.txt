include_directories(
        /usr/include/libircclient
        /usr/local/include/libircclient
        /usr/
        /lib/
        # for cmake_config.h
        ${PROJECT_BINARY_DIR}/include)

set(UNITTESTS 0)
option(ENABLE_UNITTESTS "Enable unit tests compilation" FALSE)
add_definitions(-std=c++11)
set(SOURCE_FILES
        main.cpp
        IRCThread.cpp
        CommandHandler.cpp
        Query.cpp)
set(PROJECT_LIBS
        ircclient
        curl
        )

if (ENABLE_UNITTESTS)
    message("-- Unittests enabled")
    set(UNITTESTS 1)
    set(PROJECT_LIBS ${PROJECT_LIBS} cppunit)
    set(SOURCE_FILES ${SOURCE_FILES} unittests/tests.h)
else()
    message("-- Unittests disabled")
endif()

find_package (Threads)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})
target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${BINDIR}
        BUNDLE DESTINATION .
        )
