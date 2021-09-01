#--------------------------------------------------------------------------
# render
#--------------------------------------------------------------------------

SET(files_render_display
	window.h
	window.cc
	Camera.h
	Camera.cpp
	GraphicsNode.h
	GraphicsNode.cpp
	MeshResource.h
	MeshResource.cpp
	TextureResource.h
	TextureResource.cpp
	ShaderResource.h
	ShaderResource.cpp
	Lighting.cpp
	Lighting.h
	Vertex.h
	stb_Image.h
	FragShader.glsl
	VertShader.glsl)

SOURCE_GROUP("display" FILES ${files_render_display})


SET(files_render
	${files_render_display}
	${files_render_pch})

SET(files_pch ../config.h ../config.cc)
SOURCE_GROUP("pch" FILES ${files_pch})
ADD_LIBRARY(render STATIC ${files_render} ${files_pch})
TARGET_PCH(render ../)	
ADD_DEPENDENCIES(render glew glfw)
TARGET_LINK_LIBRARIES(render PUBLIC engine exts glew glfw imgui ${OPENGL_LIBS})