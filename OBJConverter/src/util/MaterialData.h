#pragma once
#include "pch.h"
struct MaterialData {
    std::string ambient_texname;             // map_Ka
    std::string diffuse_texname;             // map_Kd
    std::string specular_texname;            // map_Ks
    std::string specular_highlight_texname;  // map_Ns
    std::string bump_texname;                // map_bump, map_Bump, bump
    std::string displacement_texname;        // disp
    std::string alpha_texname;               // map_d
    std::string reflection_texname;          // refl

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 transmittance;
    glm::vec3 emission;
    float shininess;
    float ior;       // index of refraction
    float dissolve;  // 1 == opaque; 0 == fully transparent
    int illum;
};