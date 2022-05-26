#version 330 core

out vec4 FragColor;

#define maxIterations 200

uniform int width;
uniform int height;
uniform float xScale;
uniform float yScale;
uniform float xOffset;
uniform float yOffset;

int iterations()
{
    int iterations = 0;

    //Convert screen coordinate to complex number
    float real = (gl_FragCoord.x / width - 0.5f) * xScale + xOffset;
    float imag = (gl_FragCoord.y / height - 0.5f) * yScale + yOffset;

    //Store c (for the function Z_n = Z_(n-1) ^ 2 + c)
    float cReal = real;
    float cImag = imag;

    while(iterations < maxIterations)
    {
        float tempReal = real;

        //Execute the square and add
        real = (real * real - imag * imag) + cReal;
        imag = (2 * tempReal * imag) + cImag;

        if(real * real + imag * imag > 4.0f) break;

        iterations++;
    }

    return iterations;
}

vec4 HtoRGB(float H){

    float C = 1;
    float X = (1 - abs( mod(H/60.0, 2) - 1));

    float r,g,b;
    if(H >= 0 && H < 60){
        r = C,g = X,b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X,g = C,b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0,g = C,b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0,g = X,b = C;
    }
    else if(H >= 240 && H < 300){
        r = X,g = 0,b = C;
    }
    else{
        r = C,g = 0,b = X;
    }

    return vec4(r, g, b, 1.0f);
}


vec4 ptColor()
{
    vec4 color;

    int iterations = iterations();

    if(iterations == maxIterations)
        color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    else
    {
        color = HtoRGB(float(iterations) * 360 * 1 / maxIterations);
    }

    return color;
}




void main()
{
   FragColor = ptColor();
}