#version 330 core
in vec3 aPos; 
in vec3 aColor;

uniform float aumentoPosY;
uniform float colorF;
uniform mat4 model_view;
uniform mat4 projection;

  
out vec3 ourColor; // output a color to the fragment shader

void main()
{
	float posAux = aPos.y+aumentoPosY;
	if(posAux>=1)
		posAux = posAux-1; 
	vec4 pos = vec4(aPos.x, posAux, aPos.z, 1.0);

	vec4 eyePos = model_view * pos;
    gl_Position = projection * eyePos;


    ourColor = vec3(aColor.x, 1-posAux, 0);


    float dist = length(eyePos.xyz);
    float att = inversesqrt(0.1f*dist);
    gl_PointSize = 1.0f * att;

} 