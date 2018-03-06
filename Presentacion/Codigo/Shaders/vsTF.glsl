#version 330 core
in vec3 pos; 
in vec3 direccion;
in vec3 velocidad;
in float edad;
in float maxEdad;
in float limite;


out vec3 vVelocidad;
out vec3 vDireccion;
out float vEdad;
out float vMaxEdad;
out float vLimite;



void main()
{
    vec4 posN = vec4(pos, 1.0);
    //gl_Position = projection * model_view * posN;
    gl_Position = posN;

	vVelocidad = velocidad;
	vDireccion = direccion;
	vEdad = edad;
	vMaxEdad = maxEdad;
	vLimite = limite;
} 