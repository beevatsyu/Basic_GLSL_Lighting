/*pfdsl: Per Fragment Directional Single Lighting*/

#version 110

varying vec4 ambient, diffuse, specular;
varying vec3 normal, light, halfVector;

void main()
{
	vec3 n = normalize(normal);
	vec3 l = normalize(light); //Already normalized though(due to directional light)
	vec3 h = normalize(halfVector);
	float NdotL = max(dot(n,l),0.0);
	float NdotH = max(dot(n,h),0.0);
	gl_FragColor = gl_FrontLightModelProduct.sceneColor + 
		ambient + diffuse * NdotL;
	if(NdotL > 0.0)
		gl_FragColor += specular * pow(NdotH,gl_FrontMaterial.shininess);
}
