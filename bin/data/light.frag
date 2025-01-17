// Tex coord gen
uniform sampler2D texture;

//Lighting
varying vec3 L;
varying vec3 N;
varying vec3 P;

void main (void)
{
	vec3 E = normalize(-P);
	vec3 R = normalize(-reflect(L,N));

	vec4 Iamb = gl_FrontLightProduct[0].ambient; 
	vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);
	vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R,E),0.0),0.3 * gl_FrontMaterial.shininess);

	vec4 color = texture2D(texture, vec2(gl_TexCoord[0]));
	gl_FragColor = color * (Iamb + Idiff + Ispec);         
}