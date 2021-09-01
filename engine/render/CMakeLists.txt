#--------------------------------------------------------------------------
# render
#--------------------------------------------------------------------------

FILE(GLOB Render_header *.h)
FILE(GLOB Render_sources *.cc)
FILE(GLOB Render_sources *.cpp)

SOURCE_GROUP("display" FILES ${files_render_display})


SET(files_render
	${Render_header}
	${Render_sources}
	${files_render_pch})

SET(files_pch ../config.h ../config.cc)
SOURCE_GROUP("pch" FILES ${files_pch})
ADD_LIBRARY(render STATIC ${files_render} ${files_pch})
TARGET_PCH(render ../)	
ADD_DEPENDENCIES(render glew glfw)
TARGET_LINK_LIBRARIES(render PUBLIC engine exts glew glfw imgui ${OPENGL_LIBS})
