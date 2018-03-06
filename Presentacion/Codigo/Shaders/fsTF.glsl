#version 330 core
  
in vec4 fColor;
out vec4 FragColor; 
void main()
{
	FragColor = fColor;
    //FragColor = vec4(fColor, 1.0);
    //FragColor = vec4(1.0, 0.1, 0.01, 1.0);


    //discard; // yes: discard this fragment
}