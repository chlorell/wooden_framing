//
//  simple_renderer.cpp
//  WoodFraming
//
//  Created by Mateusz Bugaj on 17.08.2015.
//  Copyright (c) 2015 Ocean Planet Studios. All rights reserved.
//

#include "simple_renderer.hpp"

#include <iostream>
#include <system_error>

floppy::simple_renderer::simple_renderer()
{
    gl::shader<gl::vertex> vertex_s;
    vertex_s.source("fuck you freddy!!!");
    auto status_v=vertex_s.status();
    if(!status_v.first)
    {
        std::cerr<<status_v.second;
        throw std::runtime_error("compilation of VS failed");
    }
    
    prog1.attach(vertex_s);
    
    gl::shader<gl::fragment> fragment_s;
    fragment_s.source("fuck you freddy!!!");
    auto status_f=fragment_s.status();
    if(!status_f.first)
    {
        std::cerr<<status_f.second;
        throw std::runtime_error("compilation of FS failed");
    }
}