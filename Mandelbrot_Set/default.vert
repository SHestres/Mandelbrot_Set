#version 330 core

// Sets the framework for the two different pieces of info that are gleaned from the VAO
// The "hook" for VAO.LinkAttrib()
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}