//
//  graphics_data.hpp
//  WoodFraming
//
//  Created by Mateusz Bugaj on 04.09.2015.
//  Copyright (c) 2015 Ocean Planet Studios. All rights reserved.
//

#ifndef WoodFraming_graphics_data_hpp
#define WoodFraming_graphics_data_hpp

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace floppy {
    struct camera
    {
        glm::mat4 proj;
        glm::mat4 view;
        glm::vec3 pos;
        glm::quat rot;
    };
    
    struct node
    {
        glm::mat4 world;
        glm::vec3 pos;
        glm::quat rot;
        glm::vec3 scale;
    };
    
}




#endif
