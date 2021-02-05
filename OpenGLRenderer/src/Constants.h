#pragma once
#include "pch.h"

const uint32_t INIT_WIDTH = 1024;
const uint32_t INIT_HEIGHT = 768;

const std::string UNIFORM_TEXTURE_VALID = "Valid";

// XML parse IDs
const std::string MODEL_ATTRIBUTE_NAME = "model";
const std::string MODEL_NAME = "modelName";
const std::string MATERIAL_ATTRIBUTE_NAME = "material";
const std::string SCENE = "scene";
const std::string SCENE_NAME = "sceneName";
const std::string SHADER_NAME = "shader";
const std::string TEXTURE_NAME = "texture";
const std::string GRID_NAME = "grid";
const std::string MESH_ATTRIBUTE_NAME = "mesh";
const std::string DIFFUSE_ATTRIBUTE_NAME = "diffuse";
const std::string NORMAL_ATTRIBUTE_NAME = "normal";
const std::string SKYBOX_NAME = "skybox";
const std::string SRC_FOLDER = "srcFolder";

// Directory Structure
const std::string ASSET_FOLDER = "assets/";
const std::string SHADER_FOLDER = ASSET_FOLDER + "shaders/";
const std::string SCENE_FOLDER = ASSET_FOLDER + "scenes/";
const std::string TEXTURE_FOLDER = ASSET_FOLDER + "textures/";
const std::string MODEL_FOLDER = ASSET_FOLDER + "models/";
const std::string MATERIAL_FOLDER = ASSET_FOLDER + "materials/";

// Master Config
const std::string MASTER_CONFIG = ASSET_FOLDER + "masterconfig.xml";

// Attributes
const std::string ATTR_SIZE = "size";

// Camera
const uint32_t MOUSE_BUTTON_0 = 0;
const uint32_t MOUSE_BUTTON_1 = 1;

// Model
const std::string TRANSFORM = "transform";
const std::string TRANSFORM_POS = "position";
const std::string TRANSFORM_ROT = "rotation";
const std::string TRANSFORM_SCALE = "scale";
const std::string VECTOR_X = "x";
const std::string VECTOR_Y = "y";
const std::string VECTOR_Z = "z";
const std::string VECTOR_W = "w";

// Light
const std::string LIGHTS = "lights";
const std::string LIGHT = "light";
const std::string COLOR = "color";
const std::string DIRECTION = "direction";
const std::string ATTENUATION = "attenuation";
const std::string INNERANGLE = "innerAngle";
const std::string OUTERANGLE = "outerAngle";
const std::string CUTOFF = "cutoffAngle";
const std::string STRENGTH = "strength";
const std::string AMBIENT = "ambient";
const std::string POINTLIGHT = "pointlight";
const std::string VECTOR_R = "r";
const std::string VECTOR_G = "g";
const std::string VECTOR_B = "b";
const std::string VECTOR_A = "a";