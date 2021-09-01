#pragma once
//------------------------------------------------------------------------------
/**
	Manages the opening and closing of a window.
	
	(C) 2015-2020 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <nanovg.h>
#include <string>

namespace Display
{
class Window
{
public:
	/// constructor
	Window();
	/// destructor
	~Window();

	/// set size of window
	void SetSize(int width, int height);
	/// get size of windows
	void GetSize(int & width, int & height);
	/// set title of window
	void SetTitle(const std::string& title);

	/// open window
	bool Open();
	/// close window
	void Close();
	/// returns true if window is open
	const bool IsOpen() const;

	/// make this window current, meaning all draws will direct to this window context
	void MakeCurrent();

	/// update a tick
	void Update();
	/// swap buffers at end of frame
	void SwapBuffers();

	/// set key press function callback
	void SetKeyPressFunction(const std::function<void(int, int, int, int)>& func);
	/// set mouse press function callback
	void SetMousePressFunction(const std::function<void(int, int, int)>& func);
	/// set mouse move function callback
	void SetMouseMoveFunction(const std::function<void(double, double)>& func);
	/// set mouse enter leave function callback
	void SetMouseEnterLeaveFunction(const std::function<void(bool)>& func);
	/// set mouse scroll function callback
	void SetMouseScrollFunction(const std::function<void(double, double)>& func);

	/// set optional UI render function
	void SetUiRender(const std::function<void()>& func);
	/// set optional nanovg render function
	void SetNanoVGRender(const std::function<void(NVGcontext *)> & func);

private:

	/// static key press callback
	static void StaticKeyPressCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
	/// static mouse press callback
	static void StaticMousePressCallback(GLFWwindow* win, int button, int action, int mods);
	/// static mouse move callback
	static void StaticMouseMoveCallback(GLFWwindow* win, double x, double y);
	/// static mouse enter/leave callback
	static void StaticMouseEnterLeaveCallback(GLFWwindow* win, int mode);
	/// static mouse scroll callback
	static void StaticMouseScrollCallback(GLFWwindow* win, double x, double y);

	/// resize update
	void Resize();
	/// title rename update
	void Retitle(); 

	static int WindowCount;

	/// function for key press callbacks
	std::function<void(int, int, int, int)> keyPressCallback;
	/// function for mouse press callbacks
	std::function<void(int, int, int)> mousePressCallback;
	/// function for mouse move callbacks
	std::function<void(double, double)> mouseMoveCallback;
	/// function for mouse enter/leave callbacks
	std::function<void(bool)> mouseLeaveEnterCallback;
	/// function for mouse scroll callbacks
	std::function<void(double, double)> mouseScrollCallback;
	/// function for ui rendering callback
	std::function<void()> uiFunc;
	/// function for nanovg rendering callback
	std::function<void(NVGcontext *)> nanoFunc;


	int width;
	int height;
	std::string title;
	GLFWwindow* window;
	NVGcontext * vg;
};

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
	if (nullptr != this->window)
	{
		this->Resize();
	}
}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::GetSize(int & width, int & height)
{
	width = this->width;
	height = this->height;

}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetTitle(const std::string& title)
{
	this->title = title;
	if (nullptr != this->window)
	{
		this->Retitle();
	}
}

//------------------------------------------------------------------------------
/**
*/
inline const bool
Window::IsOpen() const
{
	return nullptr != this->window;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetKeyPressFunction(const std::function<void(int, int, int, int)>& func)
{
	this->keyPressCallback = func;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetMousePressFunction(const std::function<void(int, int, int)>& func)
{
	this->mousePressCallback = func;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetMouseMoveFunction(const std::function<void(double, double)>& func)
{
	this->mouseMoveCallback = func;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetMouseEnterLeaveFunction(const std::function<void(bool)>& func)
{
	this->mouseLeaveEnterCallback = func;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetMouseScrollFunction(const std::function<void(double, double)>& func)
{
	this->mouseScrollCallback = func;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetUiRender(const std::function<void()>& func)
{
	this->uiFunc = func;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetNanoVGRender(const std::function<void(NVGcontext *)> & func)
{
	this->nanoFunc = func;
}
} // namespace Display