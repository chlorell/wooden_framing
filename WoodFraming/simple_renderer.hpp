//
//  simple_renderer.h
//  WoodFraming
//
//  Created by Mateusz Bugaj on 17.08.2015.
//  Copyright (c) 2015 Ocean Planet Studios. All rights reserved.
//

#ifndef __WoodFraming__simple_renderer__
#define __WoodFraming__simple_renderer__

#include "cpp/gl_elements.hpp"
#include <string>

namespace floppy {
    class simple_renderer
    {
        gl::program prog1;
        int prog1_modelViewProjectionMatrix, prog1_normalMatrix;
        
        gl::vertex_buffer mesh;
        
        glm::mat4 model;
        glm::mat3 model_normal;
        glm::mat4 camera_perspective;
        
        
        unsigned long mesh_count;
     public:
        simple_renderer(const std::string& base_path);
        void draw();
        
    };
}






#endif /* defined(__WoodFraming__simple_renderer__) */
