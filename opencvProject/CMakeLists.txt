cmake_minimum_required(VERSION 3.20)

project(opencvProjects LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ★OpenCV を探す（OpenCV_DIR を渡せばここで見つかる）
find_package(OpenCV REQUIRED)

add_executable(app
    src/TestMain.cpp
)

# include を通す（OpenCV_INCLUDE_DIRS が入る）
target_include_directories(app PRIVATE ${OpenCV_INCLUDE_DIRS})

# link を通す（OpenCV_LIBS が入る）
target_link_libraries(app PRIVATE ${OpenCV_LIBS})

# ついでに出力場所を揃えたいなら（任意）
set_target_properties(app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
