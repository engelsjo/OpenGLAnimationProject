//
//  TPillar.cpp
//  ProjectOne
//
//  Created by Joshua Engelsma on 2/7/15.
//
//

#include "TPillar.h"
#include <vector>

/* NOTE: Pillar is centered on bottom rectangular corner */

using glm::vec3;

void TPillar::build_with_params(float length, float width, float height, float r, float g, float b){
    LENGTH = length;
    WIDTH = width;
    HEIGHT = height;
    
    COLOR_R = r / 255.0f;
    COLOR_G = g / 255.0f;
    COLOR_B = b / 255.0f;
    
    build((void*)0);
}

void TPillar::build(void* data) {
    
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    glGenBuffers(1, &color_buffer);
    
    //build the 6 vertexes
    vec3 v0 = vec3{0, 0, 0};
    vec3 v1 = vec3{LENGTH, 0, 0};
    vec3 v2 = vec3{LENGTH, WIDTH, 0};
    vec3 v3 = vec3{0, WIDTH, 0};
    vec3 v4 = vec3{LENGTH, WIDTH, HEIGHT};
    vec3 v5 = vec3{LENGTH, 0, HEIGHT};
    
    //get 6 colors
    all_colors.push_back(vec3{COLOR_R, COLOR_G, COLOR_B});
    all_colors.push_back(vec3{COLOR_R-10/255.0f, COLOR_G-10/255.0f, COLOR_B-10/255.0f});
    all_colors.push_back(vec3{COLOR_R+10/255.0f, COLOR_G+10/255.0f, COLOR_B+10/255.0f});
    all_colors.push_back(vec3{COLOR_R-15/255.0f, COLOR_G-15/255.0f, COLOR_B-15/255.0f});
    all_colors.push_back(vec3{COLOR_R+15/255.0f, COLOR_G+15/255.0f, COLOR_B+15/255.0f});
    all_colors.push_back(vec3{COLOR_R-20/255.0f, COLOR_G-20/255.0f, COLOR_B-20/255.0f});
    
    all_points.push_back(v0); //add vertices
    all_points.push_back(v1);
    all_points.push_back(v2);
    all_points.push_back(v3);
    all_points.push_back(v4);
    all_points.push_back(v5);
    
    //quad - strip indices
    vector<int> quad_indices = vector<int>{0, 3, 1, 2, 5, 4, 0, 3};
    for (auto index : quad_indices){
        all_index.push_back(index);
    }
    
    //front triangle side
    vector<int> front_indices = vector<int>{5, 0, 1};
    for (auto index : front_indices){
        all_index.push_back(index);
    }
    
    //back triangle side
    vector<int> back_indices = vector<int>{2, 3, 4};
    for (auto index : back_indices){
        all_index.push_back(index);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
    float *vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    
    /* Initialize the vertices */
    float *ptr = vertex_ptr;
    for (auto v : all_points) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, all_colors.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
    float *color_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    
    /* Initialize the vertices */
    float *cptr = color_ptr;
    for (auto v : all_colors) {
        cptr[0] = v.x;
        cptr[1] = v.y;
        cptr[2] = v.z;
        cptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, all_index.size() * sizeof(GLushort), all_index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TPillar::render(bool outline) const {
    glPushAttrib(GL_ENABLE_BIT);
    /* bind vertex buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glColorPointer(3, GL_FLOAT, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    
    glDrawElements(GL_QUAD_STRIP, 8, GL_UNSIGNED_SHORT, 0);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*) (sizeof(GLushort) * 8));
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*) (sizeof(GLushort) * 11));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glPopAttrib();
    
}