/*pfdsl: Per Fragment Directional Single Lighting*/

#version 110

varying vec4 ambient, diffuse, specular;
varying vec3 normal, light, halfVector;

void main()
{
	normal = normalize(gl_NormalMatrix * gl_Normal);
	light = normalize(gl_LightSource[0].position.xyz);
	halfVector = gl_LightSource[0].halfVector.xyz;
	ambient = gl_FrontLightProduct[0].ambient;
	diffuse = gl_FrontLightProduct[0].diffuse;
	specular = gl_FrontLightProduct[0].specular;	
	gl_Position = ftransform();
}
