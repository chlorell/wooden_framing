//
//  simple_renderer.cpp
//  WoodFraming
//
//  Created by Mateusz Bugaj on 17.08.2015.
//  Copyright (c) 2015 Ocean Planet Studios. All rights reserved.
//

#include "simple_renderer.hpp"


#include <iostream>
#include <fstream>
#include <sstream>
#include <system_error>

#include <boost/filesystem.hpp>

floppy::simple_renderer::simple_renderer(const std::string& base_path)
{
    gl::vertex_shader vertex_s;
    
    std::fstream vsource,psource;
    boost::filesystem::path base(base_path);
    
    std::stringstream buffer;
 
    
    vsource.open((base/"Shader.vsh").string());
    psource.open((base/"Shader.fsh").string());
    
    
    buffer<<vsource.rdbuf();
    
    vertex_s.src(buffer.str().c_str());
    vertex_s.compile();
    auto status_v=vertex_s.status();
    if(!status_v.first)
    {
        std::cerr<<status_v.second;
        throw std::runtime_error("compilation of VS failed");
    }
    
    prog1.attach(vertex_s);
    
    std::stringstream buffer1;
    buffer1<<psource.rdbuf();
    gl::fragment_shader fragment_s;
    fragment_s.src(buffer1.str().c_str());
    fragment_s.compile();
    auto status_f=fragment_s.status();
    if(!status_f.first)
    {
        std::cerr<<status_f.second;
        throw std::runtime_error("compilation of FS failed");
    }
    prog1.attach(fragment_s);
    
    prog1.link();
    
    auto status_p=prog1.link_status();
    if(!status_p.first)
    {
        std::cerr<<status_f.second;
        throw std::runtime_error("linking failed");
    }
}


void floppy::simple_renderer::draw()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClearDepthf(100.f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}