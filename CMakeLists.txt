cmake_minimum_required (VERSION 3.11)
set (CMAKE_CXX_STANDARD 20)

include(FetchContent)
include(ExternalProject)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

# --- Fetch FTXUI --------------------------------------------------------------
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v4.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# ------------------------------------------------------------------------------

# --- Fetch Boost --------------------------------------------------------------
# Fetch and build Boost
set(BOOST_PROJECT_NAME boost_project)
set(BOOST_BASE_DIR ${CMAKE_BINARY_DIR}/${BOOST_PROJECT_NAME}-prefix)
set(BOOST_ROOT ${BOOST_BASE_DIR}/src/${BOOST_PROJECT_NAME})
ExternalProject_Add(
    ${BOOST_PROJECT_NAME}
    PREFIX ${BOOST_BASE_DIR}
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.72.0  # Specify the version
    UPDATE_DISCONNECTED 1 # Don't update each time
    CONFIGURE_COMMAND ${BOOST_ROOT}/bootstrap.sh
    BUILD_COMMAND ./b2 install
    INSTALL_DIR ${BOOST_ROOT}-build
    BUILD_IN_SOURCE 1  # Ensure that b2 is run from the source directory
)

# After the Boost project is fetched and built, include the headers and libraries
ExternalProject_Get_Property(${BOOST_PROJECT_NAME} install_dir)
ExternalProject_Get_Property(${BOOST_PROJECT_NAME} source_dir)
include_directories(${install_dir}/include)
link_directories(${install_dir}/lib)
# --- Fetch other dependencies --------------------------------------------------------------

# cereal
ExternalProject_Add(
  cereal
  GIT_REPOSITORY https://github.com/USCiLab/cereal.git
  GIT_TAG v1.3.0 # Replace with the desired version or commit hash
  CMAKE_ARGS
        -DBUILD_TESTING=OFF  # If this option is available, pass it
  BUILD_COMMAND ""         # Skip building anything
  TEST_COMMAND ""          # Disable running tests
  INSTALL_COMMAND ""       # Skip installation
)
ExternalProject_Get_Property(cereal source_dir)

# hana
ExternalProject_Add(
  hana
  GIT_REPOSITORY https://github.com/boostorg/hana.git
  GIT_TAG v1.6.0 # Replace with the desired version or commit hash
  CMAKE_ARGS
        -DBUILD_TESTING=OFF  # If this option is available, pass it
  BUILD_COMMAND ""         # Skip building anything
  TEST_COMMAND ""          # Disable running tests
  INSTALL_COMMAND ""       # Skip installation
)
ExternalProject_Get_Property(hana source_dir)

# immer
ExternalProject_Add(
  immer
  GIT_REPOSITORY https://github.com/arximboldi/immer.git
  GIT_TAG v0.6.2 # Replace with the desired version or commit hash
  CMAKE_ARGS
        -DBUILD_TESTING=OFF  # If this option is available, pass it
  BUILD_COMMAND ""         # Skip building anything
  TEST_COMMAND ""          # Disable running tests
  INSTALL_COMMAND ""       # Skip installation
)
ExternalProject_Get_Property(immer source_dir)

# lager
ExternalProject_Add(
  lager
  GIT_REPOSITORY https://github.com/arximboldi/lager.git
  GIT_TAG v0.1.0 # Replace with the desired version or commit hash
  CMAKE_ARGS
        -DBUILD_TESTING=OFF  # If this option is available, pass it
  BUILD_COMMAND ""         # Skip building anything
  TEST_COMMAND ""          # Disable running tests
  INSTALL_COMMAND ""       # Skip installation
)
ExternalProject_Get_Property(lager source_dir)

# zug
ExternalProject_Add(
  zug
  GIT_REPOSITORY https://github.com/arximboldi/zug.git
  GIT_TAG v0.2.0 # Replace with the desired version or commit hash
  CMAKE_ARGS
        -DBUILD_TESTING=OFF  # If this option is available, pass it
  BUILD_COMMAND ""         # Skip building anything
  TEST_COMMAND ""          # Disable running tests
  INSTALL_COMMAND ""       # Skip installation
)
ExternalProject_Get_Property(zug source_dir)

# ------------------------------------------------------------------------------


project(snake
  LANGUAGES CXX
  VERSION 1.0.0
)

# Instead of listing each component individually, headers component is catch all. Includes all the header-only components of boost.
# find_package(Boost REQUIRED COMPONENTS serialization)
# Check if Boost was found and output the include directories
# if(Boost_FOUND)
#   message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
# else()
#   message(FATAL_ERROR "Boost not found!")
# endif()

add_executable(snake src/main.cpp)

target_include_directories(snake PUBLIC
    # ${BOOST_INCLUDEDIR}
    src                    # Your source directory
    $<TARGET_PROPERTY:cereal,INTERFACE_INCLUDE_DIRECTORIES>  # Automatically get include dirs for cereal
    $<TARGET_PROPERTY:hana,INTERFACE_INCLUDE_DIRECTORIES>    # Automatically get include dirs for hana
    $<TARGET_PROPERTY:immer,INTERFACE_INCLUDE_DIRECTORIES>   # Automatically get include dirs for immer
    $<TARGET_PROPERTY:lager,INTERFACE_INCLUDE_DIRECTORIES>   # Automatically get include dirs for lager
    $<TARGET_PROPERTY:zug,INTERFACE_INCLUDE_DIRECTORIES>     # Automatically get include dirs for zug
)

target_link_libraries(snake
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
  # ${Boost_LIBRARIES}
)

if (EMSCRIPTEN) 
  string(APPEND CMAKE_CXX_FLAGS " -s USE_PTHREADS") 
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s ASYNCIFY") 
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s PROXY_TO_PTHREAD") 

  foreach(file "index.html" "run_webassembly.py")
    configure_file("src/${file}" ${file})
  endforeach(file)
endif() 