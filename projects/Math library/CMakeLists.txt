#--------------------------------------------------------------------------
# mathLib project
#--------------------------------------------------------------------------

PROJECT(mathLib)
FILE(GLOB mathLib_header code/*.h)
FILE(GLOB mathLib_sources code/*.cc)
FILE(GLOB mathLib_sources2 code/*.cpp)

SET(files_mathLib ${mathLib_headers} ${mathLib_sources} ${mathLib_sources2})
SOURCE_GROUP("mathLib" FILES ${files_mathLib})

ADD_EXECUTABLE(mathLib ${files_mathLib})
TARGET_LINK_LIBRARIES(mathLib core render)
ADD_DEPENDENCIES(mathLib core render)