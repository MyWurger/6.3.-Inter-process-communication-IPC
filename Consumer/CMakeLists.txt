cmake_minimum_required(VERSION 3.0.0)
project(PROVIDER VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

# Компилятор и его опции
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

# Внешний синтаксический анализатор cppcheck
find_program(CPPCHECK cppcheck)
if(CPPCHECK)
set(CPPCHECK_OPTIONS --enable=all)
set(CPPCHECK_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
add_custom_target(cppcheck COMMAND ${CPPCHECK} ${CPPCHECK_OPTIONS} ${CPPCHECK_SOURCE_DIR})
endif()

# Путь к исполняемому файлу PROVIDER
set(PROVIDER_EXECUTABLE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../Provider/PROVIDER)

add_executable(CONSUMER main.c)

# Добавляем команду для копирования исполняемого файла PROVIDER в директорию сборки
add_custom_command(
    TARGET CONSUMER POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${PROVIDER_EXECUTABLE_PATH}
    $<TARGET_FILE_DIR:CONSUMER>
    COMMENT "Копирование PROVIDER в директорию сборки"
)

target_include_directories(CONSUMER PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)