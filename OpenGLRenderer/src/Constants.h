#pragma once
#include "pch.h"

const uint32_t INIT_WIDTH = 1024;
const uint32_t INIT_HEIGHT = 768;

// XML parse IDs
const std::string MODEL_ATTRIBUTE_NAME = "model";
const std::string MODEL_NAME = "modelName";
const std::string MATERIAL_ATTRIBUTE_NAME = "material";
const std::string SCENE_NAME = "sceneName";
const std::string SHADER_NAME = "shader";
const std::string TEXTURE_NAME = "texture";
const std::string GRID_NAME = "grid";

// Directory Structure
const std::string ASSET_FOLDER = "assets/";
const std::string SHADER_FOLDER = ASSET_FOLDER + "shaders/";
const std::string SCENE_FOLDER = ASSET_FOLDER + "scenes/";
const std::string TEXTURE_FOLDER = ASSET_FOLDER + "textures/";

// Attributes
const std::string ATTR_SIZE = "size";

// Camera
const uint32_t MOUSE_BUTTON_0 = 0;
const uint32_t MOUSE_BUTTON_1 = 1;