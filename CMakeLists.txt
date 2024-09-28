cmake_minimum_required (VERSION 3.11)
set (CMAKE_CXX_STANDARD 20)

include(FetchContent)
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

# Specify the Boost version you want to use
set(BOOST_VERSION 1.72.0)

# Extract major, minor, and patch version numbers
string(REGEX MATCH "([0-9]+).([0-9]+).([0-9]+)" BOOST_VERSION_MATCH ${BOOST_VERSION})
set(BOOST_VERSION_MAJOR ${CMAKE_MATCH_1})
set(BOOST_VERSION_MINOR ${CMAKE_MATCH_2})
set(BOOST_VERSION_PATCH ${CMAKE_MATCH_3})

# Print the versions to verify
message(STATUS "Boost Version: ${BOOST_VERSION}")
message(STATUS "Major: ${BOOST_VERSION_MAJOR}, Minor: ${BOOST_VERSION_MINOR}, Patch: ${BOOST_VERSION_PATCH}")

# Generate the URL with underscores
set(BOOST_URL https://boostorg.jfrog.io/artifactory/main/release/${BOOST_VERSION}/source/boost_${BOOST_VERSION_MAJOR}_${BOOST_VERSION_MINOR}_${BOOST_VERSION_PATCH}.tar.gz)

set(BOOST_SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/boost-src)

# Fetch the Boost library
FetchContent_Declare(
  BoostHeaders
  URL ${BOOST_URL}
  # Replace with the actual hash for the specified version found on dowload page https://www.boost.org/users/download/
  URL_HASH SHA256=c66e88d5786f2ca4dbebb14e06b566fb642a1a6947ad8cc9091f9f445134143f
  SOURCE_DIR ${BOOST_SOURCE_DIR}
)

FetchContent_MakeAvailable(BoostHeaders)

# Set the Boost include directory
set(Boost_INCLUDEDIR ${BOOST_SOURCE_DIR})

# Set the BOOST_ROOT variable to the source directory
set(BOOST_ROOT ${BOOST_SOURCE_DIR})

# Add include directories
include_directories(${Boost_INCLUDEDIR})

# --- Fetch other dependencies --------------------------------------------------------------

# cereal
FetchContent_Declare(
  cereal
  GIT_REPOSITORY https://github.com/USCiLab/cereal.git
  GIT_TAG v1.3.0 # Replace with the desired version or commit hash
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(cereal)

# hana
FetchContent_Declare(
  hana
  GIT_REPOSITORY https://github.com/boostorg/hana.git
  GIT_TAG v1.6.0 # Replace with the desired version or commit hash
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(hana)

# immer
FetchContent_Declare(
  immer
  GIT_REPOSITORY https://github.com/arximboldi/immer.git
  GIT_TAG v0.6.2 # Replace with the desired version or commit hash
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(immer)

# lager
FetchContent_Declare(
  lager
  GIT_REPOSITORY https://github.com/arximboldi/lager.git
  GIT_TAG v0.1.0 # Replace with the desired version or commit hash
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(lager)

# zug
FetchContent_Declare(
  zug
  GIT_REPOSITORY https://github.com/arximboldi/zug.git
  GIT_TAG v0.2.0 # Replace with the desired version or commit hash
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(zug)

# ------------------------------------------------------------------------------


project(snake
  LANGUAGES CXX
  VERSION 1.0.0
)

# Instead of listing each component individually, headers component is catch all. Includes all the header-only components of boost.
find_package(Boost REQUIRED COMPONENTS serialization)
# Check if Boost was found and output the include directories
if(Boost_FOUND)
  message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
else()
  message(FATAL_ERROR "Boost not found!")
endif()

add_executable(snake src/main.cpp)

target_include_directories(snake PUBLIC
    ${Boost_INCLUDEDIR}
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
  ${Boost_LIBRARIES}
)

if (EMSCRIPTEN) 
  string(APPEND CMAKE_CXX_FLAGS " -s USE_PTHREADS") 
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s ASYNCIFY") 
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s PROXY_TO_PTHREAD") 

  foreach(file "index.html" "run_webassembly.py")
    configure_file("src/${file}" ${file})
  endforeach(file)
endif() 