#version 330 core

layout(points) in;
layout(points, max_vertices = 2) out;

in vec3 vVelocidad[];
in vec3 vDireccion[];
in float vEdad[];
in float vMaxEdad[];
in float vLimite[];


out vec4 fColor;

out vec3 posicion;
out vec3 direccion;
out vec3 velocidad;
out float edad;
out float maxEdad;
out float limite;

uniform mat4 model_view;
uniform mat4 projection;
uniform float deltaTime;
uniform float maxVida;
uniform float limitePro;



// 2D Random
float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(-0.360,0.310)))
                 * 43758.745);
}

// 2D Noise based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.000*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners porcentages
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

void main()
{
    vec4 posA;
    //vec4 posA =projection * model_view * gl_in[0].gl_Position;
    vec3 dirNueva = vDireccion[0];
    vec4 eyePos;

    float rz;

    if(vEdad[0]<vMaxEdad[0])
    //if(posA.x<=1)
    {
        posA = gl_in[0].gl_Position;

        float miLimite = vLimite[0]+limitePro;
        bool entro = false;

        float b = random(vec2(miLimite, miLimite));
        
        if(posA.x > miLimite || posA.x< -miLimite)
        {
            /*if(dirNueva.x >=0)
            {
                //dirNueva.x = -dirNueva.x+b;
            }
            else
            {
                //dirNueva.x = -dirNueva.x-b;
            }*/
            dirNueva.x = -dirNueva.x;
            //entro = true;
            
        }

        if(posA.z > miLimite || posA.z < -miLimite)
        {    
            /*if(dirNueva.z >=0)
            {
                //dirNueva.z = -dirNueva.z+b;
            }
            else
            {
                //dirNueva.z = -dirNueva.z-b;
            }*/
            dirNueva.z = -dirNueva.z;
            //entro = true;
        }

        if(entro)
        {
            miLimite = miLimite-1.0;
        }

        float a = random(vec2(vEdad[0], vEdad[0]));

        vec2 pos = vec2(posA.x+vEdad[0], posA.z+vEdad[0])*1.2;

        //posA =  posA + vec4( 0 , dirNueva.y, 0 , 0.0);
        posA =  posA + vec4( dirNueva.x , (noise(pos+a))+0, dirNueva.z , 0.0);
        
        posicion =  posA.xyz;


        eyePos = model_view *posA;
        gl_Position = projection * eyePos;
        gl_PointSize = 1;    
        
        
        velocidad = vVelocidad[0];
        direccion = dirNueva;
        edad = vEdad[0] + deltaTime;
        maxEdad = vMaxEdad[0];
        limite = miLimite-limitePro;


        if(entro)
        {
            fColor = vec4(0.1, 0.1, 0.1, 0);
        }
        else
        {
            fColor = vec4(1.0, 0.1, 0.01, 1.0);    
        }

        

        

        EmitVertex();






        /*posA = gl_in[0].gl_Position;
        rx = noise(posA.xy);
        rz = noise(posA.zy);
        ry = noise(posA.xz);

        posA =  posA + vec4( -rx , ry, rz , 0.0);
        
        posicion =  posA.xyz;

        eyePos = model_view *posA;
        gl_Position = projection * eyePos;
        gl_PointSize = 1;    
        
        tipo = 2;
        velocidad = vec3(1,2,3);
        edad = vEdad[0] + deltaTime;

        EmitVertex();*/


        EndPrimitive();
    }
}