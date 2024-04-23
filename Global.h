//
// Created by tsukasa on 2/3/24.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#ifndef GLOBAL_H
#define GLOBAL_H
#define GLFW_INCLUDE_VULKAN
#include <string>
#include <GLFW/glfw3.h>
#include "stb_image.h"

const std::string MODEL_PATH = "./assets/models/weathley.obj";
#ifndef SQUARE_EXAMPLE
const std::string TEXTURE_PATH = "./assets/textures/personality_sphere.jpg";
#else
const std::string TEXTURE_PATH = "./assets/textures/texture.jpg";
#endif

#endif // GLOBAL_H

#pragma clang diagnostic pop