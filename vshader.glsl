#version 150

uniform mat4 mvp_matrix;

in vec4 a_position;
in vec2 a_texcoord;
in float red;

out vec2 v_texcoord;
out vec4 j_position;
out vec4 t_position;
out float red1;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * a_position;

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;


    t_position=a_position;
    j_position=gl_Position;
    red1=red;
}
//! [0]
