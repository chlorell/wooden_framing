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


#include "collada_loader.hpp"
#include <glm/glm.hpp>



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
    
    collada_loader loader;
    std::ifstream collada_file((base/"example.dae").string());
    loader.traverse(collada_file);
    auto mesh_data=loader.load_mesh_data("Sphere-mesh");
    mesh_count=mesh_data.size();
    if (mesh_data.size()>0) {
        mesh.data(mesh_data.size()*sizeof(vertex), mesh_data.data(), GL_STATIC_DRAW);
        prog1.bind_attrib_location("position", 1);
        prog1.bind_attrib_location("normal", 2);
        prog1.bind_attrib_to_buffer(mesh, 1, sizeof(vertex), GL_FLOAT, false, 0);
        prog1.bind_attrib_to_buffer(mesh, 2, sizeof(vertex), GL_TRUE, false, sizeof(float)*3);
    }
    
    
}


void floppy::simple_renderer::draw()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClearDepthf(100.f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    if(mesh_count>0)
    {
        
        //uniform mat4 modelViewProjectionMatrix;
        //uniform mat3 normalMatrix;
        glm::mat4  modelViewProjectionMatrix(glm::one<glm::mat4>());
        glm::mat3  normalMatrix(glm::one<glm::mat3>());
        
        
        int mvpId=prog1.uniform_location("modelViewProjectionMatrix");
        int normId=prog1.uniform_location("normalMatrix");

        prog1.uniform_value(mvpId, modelViewProjectionMatrix);
        prog1.uniform_value(normId, normalMatrix);
        
        prog1.draw_elements(GL_TRIANGLES, mesh_count, GL_UNSIGNED_BYTE);
    }
}