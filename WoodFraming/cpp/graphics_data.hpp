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
#include <glm/gtx/quaternion.hpp>
namespace floppy {
    struct camera
    {
        glm::mat4 proj;
        glm::mat4 view;
        glm::vec3 pos;
        glm::quat rot;
        glm::vec4 perspective;
        
        void compose()
        {
            proj=glm::perspective(perspective.x, perspective.y, perspective.z, perspective.w);
            view=glm::translate(glm::toMat4(rot), pos);
        }
        
        bool decompose(const glm::mat4&  transform)
        {
            glm::vec3 scale,skew;
            
            
            return glm::decompose (transform, scale, rot, pos,  skew, perspective);
        }
     
    };
    
    struct node
    {
        glm::mat4 world;
        glm::vec3 pos;
        glm::quat rot;
        glm::vec3 scale;
        
        void compose()
        {
            world=glm::translate(glm::scale(glm::toMat4(rot), scale),pos);
        }
        
        bool decompose()
        {
            glm::vec3 skew;
            glm::vec4 perspective;
            
            return glm::decompose (world, scale, rot, pos,  skew, perspective);
        }
    };
    
}




#endif
