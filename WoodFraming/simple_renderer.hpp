//
//  simple_renderer.h
//  WoodFraming
//
//  Created by Mateusz Bugaj on 17.08.2015.
//  Copyright (c) 2015 Ocean Planet Studios. All rights reserved.
//

#ifndef __WoodFraming__simple_renderer__
#define __WoodFraming__simple_renderer__

#include "gl_wrapper.hpp"

namespace floppy {
    class simple_renderer
    {
        gl::program prog1;
        gl::res_pool<8, gl::texture> texpool512;
        gl::res_pool<4, gl::texture> texpool1024;
    public:
        simple_renderer();
        
    };
}






#endif /* defined(__WoodFraming__simple_renderer__) */
