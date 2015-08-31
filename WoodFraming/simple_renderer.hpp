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

namespace floppy {
    class simple_renderer
    {
        gl::program prog1;
        gl::texture_2d textures[8];
     public:
        simple_renderer();
        
        
    };
}






#endif /* defined(__WoodFraming__simple_renderer__) */
