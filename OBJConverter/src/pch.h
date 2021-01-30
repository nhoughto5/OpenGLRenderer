#pragma once

#ifndef PCH_H
#define PCH_H
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <fstream>
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <mutex>
#include <string>
#include <set>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <functional>
#include <pugixml.hpp>
#include <glm/gtx/hash.hpp>

#include "util/Log.h"
#include "util/MaterialData.h"

#include "util/Vertex.h"
#endif //PCH_H