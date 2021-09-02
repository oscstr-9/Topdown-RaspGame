#--------------------------------------------------------------------------
# MeshRenderer project
#--------------------------------------------------------------------------

PROJECT(MeshRenderer)
FILE(GLOB MeshRenderer_header code/*.h)
FILE(GLOB MeshRenderer_sources code/*.cc)
FILE(GLOB MeshRenderer_sources2 code/*.cpp)

SET(files_MeshRenderer ${MeshRenderer_headers} ${MeshRenderer_sources} ${MeshRenderer_sources2})
SOURCE_GROUP("MeshRenderer" FILES ${files_MeshRenderer})

ADD_EXECUTABLE(MeshRenderer ${files_MeshRenderer})
TARGET_LINK_LIBRARIES(MeshRenderer core render)
ADD_DEPENDENCIES(MeshRenderer core render)
set_property(TARGET MeshRenderer PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")