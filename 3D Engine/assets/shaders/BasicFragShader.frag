#version 400 core
layout(location = 0) out vec4 color;

in vec3 normal;
in vec3 fragPos;

struct Material
{
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;

	float shininess;
};

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material u_Material;
uniform Light u_Light;


uniform vec3 viewPosition;

void main()
{

// Ambient Calculation
	vec3 ambient = u_Material.ambientColor * u_Light.ambient;

// Diffuse Calculation
	vec3 lightDirection = normalize(u_Light.position - fragPos);
	vec3 fragNormal = normalize(normal);
	float diffuseStrength = max(dot(normal, lightDirection), 0.0f);

	vec3 diffuse = u_Light.diffuse * diffuseStrength * u_Material.diffuseColor;

// Specular Calculation
	vec3 viewDir = normalize(viewPosition - fragPos);
	vec3 reflection = reflect(-lightDirection, fragNormal);

	float spec = pow(max(dot(viewDir, reflection), 0.0f), u_Material.shininess);
	vec3 specular =  spec * u_Light.specular * u_Material.specularColor;
	
// Final Result
	vec3 result = ambient + diffuse + specular;

	color = vec4(result, 1.0f);
}