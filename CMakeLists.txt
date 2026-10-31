cmake_minimum_required(VERSION 3.21)
project(recursive_enc_dec_ryptor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt5 REQUIRED COMPONENTS Core)

add_executable(encryptor
    src/main.cpp
    src/crypto_manager/crypto_manager.cpp
    src/directory_wolker/directory_wolker.cpp
)

target_include_directories(encryptor PRIVATE src)
target_link_libraries(encryptor PRIVATE Qt5::Core)

# Копировать DLL Qt рядом с exe, чтобы программа запускалась без изменения PATH
add_custom_command(TARGET encryptor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:encryptor> $<TARGET_FILE_DIR:encryptor>
    COMMAND_EXPAND_LISTS
)
