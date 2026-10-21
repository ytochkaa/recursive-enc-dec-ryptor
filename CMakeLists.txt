cmake_minimum_required(VERSION 3.21)
project(recursive_enc_dec_ryptor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

qt_add_executable(encryptor
    src/main.cpp
    src/crypto_manager/crypto_manager.cpp
    src/directory_wolker/directory_wolker.cpp
)

target_include_directories(encryptor PRIVATE src)
target_link_libraries(encryptor PRIVATE Qt6::Core)

# Copy Qt DLLs next to the exe so it runs without touching PATH
add_custom_command(TARGET encryptor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:encryptor> $<TARGET_FILE_DIR:encryptor>
    COMMAND_EXPAND_LISTS
)
