cmake
cmake_minimum_required(VERSION 3.18)
project(torchchess LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Find OpenMP
find_package(OpenMP REQUIRED)
# Find LibTorch
set(Torch_DIR "/path/to/libtorch/share/cmake/Torch") # Or set via environment
find_package(Torch REQUIRED)
# Add executable
add_executable(torchchess 
    src/torchchess.cpp
    src/board/board.cpp
    src/search/alpha_beta.cpp
    src/search/mcts.cpp
    src/nn/nnue.cpp
    src/nn/transformer.cpp
    src/nn/wrapper.cpp
    src/uci/uci.cpp
    src/uci/option.cpp
)
target_link_libraries(torchchess PRIVATE
    OpenMP::OpenMP_CXX
    ${TORCH_LIBRARIES}
)
# Copy the networks to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/networks DESTINATION ${CMAKE_BINARY_DIR})
