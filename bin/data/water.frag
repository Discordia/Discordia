// Simple water fragment shader

// Tex coord gen
uniform sampler2D reflectTex;

//Lighting
varying vec3 L;
varying vec3 N;
varying vec3 P;

void main (void)
{
	// Calc per-fragment lighting
	vec3 E = normalize(-P);
	vec3 R = normalize(-reflect(L,N));

	vec4 Iamb = gl_FrontLightProduct[0].ambient; 
	vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);
	vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R,E),0.0),0.3 * gl_FrontMaterial.shininess);

	// s/q t/q
	vec4 color = texture2DProj(reflectTex, gl_TexCoord[0]);
	
	// Color is dependent of lighting and projective texturing
	gl_FragColor.xyz = color.xyz * (Iamb + Idiff + Ispec).xyz;         
	gl_FragColor.w = 0.8;
}