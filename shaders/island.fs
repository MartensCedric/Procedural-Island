uniform sampler2D texture;

uniform float sea_level;
uniform float beach_level;
uniform float grass_level;
uniform float mountain_level;

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    float alt = pixel.x;

    if(alt < sea_level)
    {
        float alt_norm = alt / sea_level;
        gl_FragColor = vec4(0.0f, 0.0f, alt_norm, 1.0f);
    }
    else if(alt < beach_level)
    {
         float alt_norm = (alt / beach_level);
         gl_FragColor = vec4(1.0f, 1.0f, (100.0f + alt_norm * 50.0f) / 255.0f, 1.0f);
    }
    else if(alt < grass_level)
    {
         float alt_norm = (alt / grass_level);
         gl_FragColor = vec4(50.0f / 255.0f, (200.0f + alt_norm * 55.0f) / 255.0f, 50.0f / 255.0f, 1.0f);
    }
    else if(alt < mountain_level)
    {
         float alt_norm = (alt / mountain_level);
         float v = alt_norm / 2.0f + 0.35f;
         gl_FragColor = vec4(vec3(v), 1.0f);
    }
    else
    {
        gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
}