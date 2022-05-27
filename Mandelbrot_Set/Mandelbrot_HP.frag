#version 330 core

out vec4 FragColor;

#define maxIterations 2000

uniform int width;
uniform int height;
uniform float xScale;
uniform float yScale;
uniform float xOffset;
uniform float yOffset;

int iterations()
{
    int iterations = 0;

    float Br = xOffset;
    float Bi = yOffset;

    float Sr = (gl_FragCoord.x / width - 0.5f) * xScale;
    float Si = (gl_FragCoord.y / height - 0.5f) * yScale;

    //Store c (for the function Z_n = Z_(n-1) ^ 2 + c)
    float Bcr = Br; //Real part of big
    float Scr = Sr; //Real part of small
    float Bci = Bi; //Imag part of big
    float Sci = Si; //Imag part of small

    while(iterations < maxIterations)
    {
        float Br_temp = Br;
        float Sr_temp = Sr;

        float Zr = Br + Sr;
        float Zi = Bi + Si;

        //Values needed for precision calculation
        float Br_sq = Br * Br;
        float Sr_sq = Sr * Sr;
        float Bi_sq = Bi * Bi;
        float Si_sq = Si * Si;
        float BrSr = Br * Sr;
        float BiSi = Bi * Si;
        float BrSi = Br * Si;
        float BiSr = Bi * Sr;

        //Execute the square and add
        Br = Br_sq - Bi_sq + Bcr;
        Sr = Sr_sq - Si_sq + 2 * (BrSr - BiSi) + Scr;
        Bi = Br_temp * (Bi + Bi) + Bci;
        Si = Sr_temp * (Si + Si) + 2 * (BrSi + BiSr) + Sci;


        if((Zr * Zr + Zi * Zi) > 4.0f) break;

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