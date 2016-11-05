/*pvdsl: Per Vertex Directional Single Lighting*/

#version 110

void main()
{
	vec3 normal = normalize(gl_NormalMatrix * gl_Normal);
	vec3 light = normalize(gl_LightSource[0].position.xyz);
	float NdotL = max(dot(normal,light),0.0);
	float NdotH = max(dot(normal,gl_LightSource[0].halfVector.xyz),0.0);
	gl_FrontColor = gl_FrontLightModelProduct.sceneColor + 
		gl_FrontLightProduct[0].ambient + 
		gl_FrontLightProduct[0].diffuse * NdotL;
	if(NdotL > 0.0)	
		gl_FrontColor += gl_FrontLightProduct[0].specular * pow(NdotH,gl_FrontMaterial.shininess);
	gl_Position = ftransform();
}
