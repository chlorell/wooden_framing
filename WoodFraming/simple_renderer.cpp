//
//  simple_renderer.cpp
//  WoodFraming
//
//  Created by Mateusz Bugaj on 17.08.2015.
//  Copyright (c) 2015 Ocean Planet Studios. All rights reserved.
//
#define GLM_SWIZZLE 

#include "simple_renderer.hpp"


#include <iostream>
#include <fstream>
#include <sstream>
#include <system_error>

#include <boost/filesystem.hpp>


#include "collada_loader.hpp"
#include <glm/glm.hpp>

struct posnnormal
{
    glm::vec3 pos, normal;
};

floppy::simple_renderer::simple_renderer(const std::string& base_path)
{
    gl::vertex_shader vertex_s;
    
    std::ifstream vsource,psource;
    boost::filesystem::path base(base_path);
    
    std::stringstream buffer;
 
    
    vsource.open((base/"Shader.vsh").string());
   
    psource.open((base/"Shader.fsh").string());
    
  
    buffer<<vsource.rdbuf();
    std::string v_src_str=buffer.str();
    vertex_s.src(v_src_str.c_str());
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
    std::string f_src_str=buffer1.str();
    fragment_s.src(f_src_str.c_str());
    fragment_s.compile();
    auto status_f=fragment_s.status();
    if(!status_f.first)
    {
        std::cerr<<status_f.second;
        throw std::runtime_error("compilation of FS failed");
    }
    prog1.attach(fragment_s);
    
    prog1.bind_attrib_location("position", 1);
    prog1.bind_attrib_location("normal", 2);
    
    prog1.link();
   
    
    auto status_p=prog1.link_status();
    if(!status_p.first)
    {
        std::cout<<status_p.second;
        throw std::runtime_error("linking failed");
    }
    
    collada_loader loader;
    std::ifstream collada_file((base/"example.dae").string());
    loader.traverse(collada_file);
    auto mesh_data=loader.load_mesh_data("Sphere-mesh");
    mesh_count=mesh_data.size();
    if (mesh_data.size()>0) {
      
        
        std::vector<posnnormal> simplemesh;
        simplemesh.reserve(mesh_count);
        for (auto& p: mesh_data)
        {
            simplemesh.push_back(posnnormal{p.pos, p.normal});
        }
        mesh.data((GLsizei)mesh_data.size()*sizeof(posnnormal), simplemesh.data(), GL_STATIC_DRAW);
        
        prog1.use();
        prog1_modelViewProjectionMatrix=prog1.uniform_location("modelViewProjectionMatrix");
        prog1_normalMatrix=prog1.uniform_location("normalMatrix");
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        prog1.bind_attrib_to_buffer(mesh, 1, 3, GL_FLOAT, false, 24,0);
        prog1.bind_attrib_to_buffer(mesh, 2, 3, GL_FLOAT, false, 24,12);
    }
    
    
 
    camera_perspective=loader.get_camera_projection("Camera-camera");
    
    node cube, cam_node;
    
    cube.world=loader.get_node_transform("Sphere");
    cam_node.world=loader.get_node_transform("Camera");
    camera cam;
    cam.proj=camera_perspective;
  
    cam.view=glm::inverse(cam_node.world);
    
  
    model=cube.world;
 
    camera_perspective=cam.proj*cam.view;
    
   
    
    glm::mat4 normal_pre=cam.view*model;
    model_normal[0]=normal_pre[0].xyz();
    model_normal[1]=normal_pre[1].xyz();
    model_normal[2]=normal_pre[2].xyz();
    
    glDisable(GL_CULL_FACE);
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClearDepthf(100.f);
    
    glm::mat4  modelViewProjectionMatrix(glm::one<glm::mat4>());
    glm::mat3  normalMatrix(glm::one<glm::mat3>());
    
    normalMatrix=model_normal;
    modelViewProjectionMatrix=camera_perspective*model;
    
    
    std::vector<posnnormal> simplemesh;
    simplemesh.reserve(mesh_count);
    
    for (auto& p: mesh_data)
    {
        glm::vec4 t(p.pos,1.0);
        t=modelViewProjectionMatrix*t;
        t=t/t.w;
        
        simplemesh.push_back(posnnormal{t.xyz(), normalMatrix*p.normal});
    }
    
    for (auto& p: simplemesh)
    {
        std::cout<<p.pos.x<<", "<<p.pos.y<<", "<<p.pos.z<<std::endl;
    }
    
}


void floppy::simple_renderer::draw()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    prog1.use();
    if(mesh_count>0)
    {
        
        //uniform mat4 modelViewProjectionMatrix;
        //uniform mat3 normalMatrix;
        glm::mat4  modelViewProjectionMatrix(glm::one<glm::mat4>());
        glm::mat3  normalMatrix(glm::one<glm::mat3>());
        
        normalMatrix=model_normal;
        
        modelViewProjectionMatrix=camera_perspective*model;
        

        prog1.uniform_value(prog1_modelViewProjectionMatrix, modelViewProjectionMatrix);
        prog1.uniform_value(prog1_normalMatrix, normalMatrix);
        mesh.bind();
        prog1.draw_elements(GL_TRIANGLES, (GLsizei)mesh_count);
    }
}