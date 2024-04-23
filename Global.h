//
// Created by tsukasa on 2/3/24.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#ifndef GLOBAL_H
#define GLOBAL_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "stb_image.h"

struct GLFWDestroyWindow
{
	void operator()(GLFWwindow *win) const { glfwDestroyWindow(win); }
};

#endif // GLOBAL_H

#pragma clang diagnostic pop