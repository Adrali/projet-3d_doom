#version 150

uniform sampler2D texture;

in vec2 v_texcoord;
in vec3 v_position;
in vec4 j_position;
in vec4 t_position;

in float red1;



//! [0]
void main()
{
    // Set fragment color from texture
    gl_FragColor = texture2D(texture, v_texcoord);

    float dist = sqrt(pow(j_position.x-t_position.x,2)+pow(j_position.y-t_position.y,2)+pow(j_position.z-t_position.z,2));

    int n=70;
    float factor=1.13;
    float distLimit=0;

    for(int i=0;i<n;i++)
    {
        factor-=(1.0/n);
        distLimit+=(330/n);
        if(dist<distLimit)
        {
            gl_FragColor = texture2D(texture, v_texcoord)*factor;
            i=n;
        }
        else
            gl_FragColor = texture2D(texture, v_texcoord)*0.12;
    }


    gl_FragColor.r=gl_FragColor.r+((255-gl_FragColor.r)*(red1/1000));


}
//! [0]

