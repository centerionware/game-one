# The name of our project is "HELLO". CMakeLists files in this project can 
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and 
# to the root binary directory of the project as ${HELLO_BINARY_DIR}. 
cmake_minimum_required (VERSION 2.6) 
project (Game-One) 

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually 
# cause another cmake executable to run. The same process will walk through 
# the project's entire directory structure. 

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON) 
set(Boost_USE_STATIC_RUNTIME OFF)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
Find_Package(CEGUI REQUIRED COMPONENTS Falagard OgreRenderer)
Find_Package(OGRE)

find_package(Boost 1.49.0 COMPONENTS filesystem regex thread iostreams system)
find_package(TinyXML)
find_package(OIS)
find_package(MySQL)
find_package(Lua52)
include_directories(${LUA_INCLUDE_DIR} )
include_directories(${CEGUI_INCLUDE_DIR})
include_directories(${OGRE_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${TinyXML_INCLUDE_DIR})
include_directories(${OIS_INCLUDE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/dotscene")
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(${MYSQL_INCLUDE_DIR})
#LINK_DIRECTORIES(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})
#LINK_DIRECTORIES(${LINK_DIRECTORIES} ${CEGUI_LIBRARIES})
#LINK_DIRECTORIES(${LINK_DIRECTORIES} ${OGRE_LIBRARIES})
#LINK_DIRECTORIES(${LINK_DIRECTORIES} ${TINYXML_LIBRARIES})
#LINK_DIRECTORIES(${LINK_DIRECTORIES} ${OIS_LIBRARIES})
#LINK_DIRECTORIES($(OGRE_LIB_DIR))

set(LIBS ${LIBS} ${LUA_INCLUDE_DIR} )
set(LIBS ${LIBS} ${CEGUI_OGRERENDERER_LIBRARIES})
set(LIBS ${LIBS} ${CEGUI_LIBRARIES})
set(LIBS ${LIBS} ${OGRE_LIBRARIES})
set(LIBS ${LIBS} ${Boost_LIBRARIES})
set(LIBS ${LIBS} ${TINYXML_LIBRARIES})
set(LIBS ${LIBS} ${OIS_LIBRARIES})

ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x

    -msse
    -mfpmath=sse
    -mtune=native
    -march=native
    # Other flags
)

add_subdirectory (src)
