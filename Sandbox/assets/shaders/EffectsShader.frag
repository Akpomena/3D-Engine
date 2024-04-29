#version 400 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform int selectedEffect;

const float offset = 1.0 / 300.0;  

float edgeKernel[9] = float[](
    1.0, 1.0, 1.0,
    1.0, -8.0, 1.0,
    1.0, 1.0, 1.0  
    );

float sharpenKernel[9] = float[](
    -1, -1, -1,
    -1,  9, -1,
    -1, -1, -1
    );

float blurKernel[9] = float[](
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16  
    );
    


void main()
{ 
       vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );


    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);

    switch(selectedEffect)
    {
        case 0:
            col = 1.0 - texture(screenTexture, TexCoords).rgb;
            break;
        case 1:
             vec3 tempColor = texture(screenTexture, TexCoords).rgb;
             float average = 0.2126 * tempColor.r + 0.7152 * tempColor.g + 0.0722 * tempColor.b;
             col = vec3(average, average, average);
            break;
        case 2:
            for(int i = 0; i < 9; i++)
                col += sampleTex[i] * sharpenKernel[i];
            break;
        case 3:
            for(int i = 0; i < 9; i++)
                col += sampleTex[i] * blurKernel[i];
            break;
        case 4:
            for(int i = 0; i < 9; i++)
                col += sampleTex[i] * edgeKernel[i];
            break;
    }

    
    
    FragColor = vec4(col, 1.0);
}