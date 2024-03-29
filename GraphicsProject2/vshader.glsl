// ************
// vshader.glsl
// ************
#version 150 

in  vec4 vPosition;
in  vec3 vNormal;
out vec4 color;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat4 Position;
uniform mat4 Scale;
uniform mat4 Rotation;
uniform vec4 LightPosition;
uniform float Shininess;
uniform bool LightingEnabled;
uniform vec4 Diffuse;

void main()
{
    gl_Position = Projection * ModelView * Position * Rotation * Scale * vPosition;

    if (LightingEnabled) {
        // Transform vertex  position into eye coordinates
        vec3 pos = (Position * Rotation  * Scale * vPosition).xyz;
    
        vec3 L = normalize(LightPosition.xyz - pos);
        vec3 E = normalize(-pos);
        vec3 H = normalize(L + E);

        // Transform vertex normal into eye coordinates
        vec3 N = normalize(Rotation * vec4(vNormal, 0.0)).xyz;

        // Compute terms in the illumination equation
        vec4 ambient = AmbientProduct;

        float Kd = max( dot(L, N), 0.0 );
        vec4  diffuse = Kd * DiffuseProduct;

        float Ks = pow( max(dot(N, H), 0.0), Shininess );
        vec4  specular = Ks * SpecularProduct;
    
        if( dot(L, N) < 0.0 ) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
        } 

        color = ambient + diffuse + specular;
        color.a = 1.0;
    } else {
        color = Diffuse;
    }
}
