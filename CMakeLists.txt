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

# # Specify the Boost version you want to use
# set(BOOST_VERSION 1.72.0)

# # Extract major, minor, and patch version numbers
# string(REGEX MATCH "([0-9]+).([0-9]+).([0-9]+)" BOOST_VERSION_MATCH ${BOOST_VERSION})
# set(BOOST_VERSION_MAJOR ${CMAKE_MATCH_1})
# set(BOOST_VERSION_MINOR ${CMAKE_MATCH_2})
# set(BOOST_VERSION_PATCH ${CMAKE_MATCH_3})

# # Print the versions to verify
# message(STATUS "Boost Version: ${BOOST_VERSION}")
# message(STATUS "Major: ${BOOST_VERSION_MAJOR}, Minor: ${BOOST_VERSION_MINOR}, Patch: ${BOOST_VERSION_PATCH}")

# # Generate the URL with underscores
# set(BOOST_URL https://boostorg.jfrog.io/artifactory/main/release/${BOOST_VERSION}/source/boost_${BOOST_VERSION_MAJOR}_${BOOST_VERSION_MINOR}_${BOOST_VERSION_PATCH}.tar.gz)

# set(BOOST_SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/boost-src)

# # Fetch the Boost library
# FetchContent_Declare(
#   BoostHeaders
#   URL ${BOOST_URL}
#   # Replace with the actual hash for the specified version found on dowload page https://www.boost.org/users/download/
#   URL_HASH SHA256=c66e88d5786f2ca4dbebb14e06b566fb642a1a6947ad8cc9091f9f445134143f
#   SOURCE_DIR ${BOOST_SOURCE_DIR}
# )

# FetchContent_MakeAvailable(BoostHeaders)

# # Set the Boost include directory
# set(BOOST_INCLUDEDIR ${BOOST_SOURCE_DIR})

# # Set the BOOST_ROOT variable to the source directory
# set(BOOST_ROOT ${BOOST_SOURCE_DIR})

# find_package(Boost REQUIRED)

# # Add include directories
# include_directories(${BOOST_INCLUDEDIR})

# External project to fetch Boost headers
# ExternalProject_Add(
#     boost_headers
#     GIT_REPOSITORY https://github.com/boostorg/boost.git
#     GIT_TAG boost-1.72.0  # Specify the Boost version
#     CONFIGURE_COMMAND ""  # No configure step needed for headers
#     BUILD_COMMAND ""      # No build step needed for headers
#     INSTALL_COMMAND ""    # Skip the install step
#     UPDATE_DISCONNECTED 1 # Don’t fetch again if already downloaded
# )

# # Get the path to the Boost source directory
# ExternalProject_Get_Property(boost_headers source_dir)

# # Add the Boost include directory to your project
# include_directories(${source_dir})


# ExternalProject_Add(
#     boost_project
#     URL https://archives.boost.io/release/1.72.0/source/boost_1_72_0.tar.gz
#     DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/boost_download
#     DOWNLOAD_NAME boost_1_72_0.tar.gz
#     DOWNLOAD_NO_PROGRESS 1
#     UPDATE_COMMAND ""
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND ""
#     # INSTALL_DIR ${CMAKE_BINARY_DIR}/boost_install
#     INSTALL_COMMAND ""
# )

# ExternalProject_Get_Property(boost_project source_dir)
# message(STATUS "source_dir: ${source_dir}")
# include_directories(${source_dir}/boost)
# link_directories(${source_dir}/libs)

# Fetch and build Boost with the System library
ExternalProject_Add(
    boost_project
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.72.0  # Specify the version
    UPDATE_DISCONNECTED 1 # Don't update each time
    CMAKE_ARGS
        -DBoost_INCLUDE_DIR=${CMAKE_BINARY_DIR}/boost_project/include
        -DBoost_SYSTEM=ON    # Enable building the Boost.System component
        -sBOOST_ROOT=${CMAKE_BINARY_DIR}/boost_project-prefix/src/boost_project
    CONFIGURE_COMMAND ${CMAKE_BINARY_DIR}/boost_project-prefix/src/boost_project/bootstrap.sh
    BUILD_COMMAND ./b2 install --with-system --prefix=${CMAKE_BINARY_DIR}/boost_project
    # INSTALL_DIR ${CMAKE_BINARY_DIR}/boost_project
)

# After the Boost project is fetched and built, include the headers and libraries
ExternalProject_Get_Property(boost_project install_dir)
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