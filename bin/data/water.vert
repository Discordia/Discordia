// Simple water vertex shader

// Used for projective texturing coordinates generation
uniform mat4 projMatrix;

// Used for lighting calculations
varying vec3 L;
varying vec3 N;
varying vec3 P;

void main(void)
{
	// Lighting
	P = vec3(gl_ModelViewMatrix * gl_Vertex);
	L = normalize(gl_LightSource[0].position.xyz-P);
	N = normalize(gl_NormalMatrix * gl_Normal);
	
	// Distortion of texture coords depending of the normal.
	// This is done to get distorted reflections when the water moves.
	float d = 2.0;
	vec4 dPos;
	dPos.xy = gl_Vertex.xy + d * gl_Normal.xy;
	dPos.z = gl_Vertex.z;
	dPos.w = 1.0;
  
	gl_TexCoord[0] = projMatrix * dPos;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}