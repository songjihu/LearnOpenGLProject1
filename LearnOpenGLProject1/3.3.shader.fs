#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = vec4(ourColor, 1.0f);
    //FragColor = vec4(ourPosition, 1.0); 
    FragColor = mix(texture(texture1, TexCoord)* vec4(ourColor, 1.0), texture(texture2, TexCoord)* vec4(ourColor, 1.0), 0.2);
}