#version 130
//layout (location = 0) is not supported in 130, It is also possible to omit the layout (location = 0) specifier and query for the attribute locations in your OpenGL code via glGetAttribLocation, but I'd prefer to set them in the vertex shader. It is easier to understand and saves you (and OpenGL) some work. 



in vec3 position;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}
