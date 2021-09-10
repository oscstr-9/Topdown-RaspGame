#--------------------------------------------------------------------------
# gltfLoader project
#--------------------------------------------------------------------------

PROJECT(gltfLoader)
FILE(GLOB gltfLoader_header code/*.h)
FILE(GLOB gltfLoader_cc_sources code/*.cc)
FILE(GLOB gltfLoader_cpp_sources code/*.cpp)

SET(files_gltfLoader ${gltfLoader_headers} ${gltfLoader_cc_sources} ${gltfLoader_cpp_sources})
SOURCE_GROUP("gltfLoader" FILES ${files_gltfLoader})

ADD_EXECUTABLE(gltfLoader ${files_gltfLoader})
TARGET_LINK_LIBRARIES(gltfLoader core render)
ADD_DEPENDENCIES(gltfLoader core render)
set_property(TARGET gltfLoader PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")