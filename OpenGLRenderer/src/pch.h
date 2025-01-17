// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H
//#define TINYOBJLOADER_IMPLEMENTATION
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <functional>
#include <cstdlib>
#include <vector>
#include <array>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <set>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>
#include <mutex>

#include <pugixml.hpp>

#include <chrono>
#include <fstream>
#include "core/util/Vertex.h"

#include "core/util/TimeStep.h"
#include "spdlog/spdlog.h"
#include "Constants.h"
#include "core/Core.h"
#include "Log.h"
#include "core/util/ImageLoader.h"

#endif //PCH_H
