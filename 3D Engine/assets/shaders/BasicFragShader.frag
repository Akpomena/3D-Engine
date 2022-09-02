#version 400 core
layout(location = 0) out vec4 color;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;

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

uniform float u_Time;

uniform vec3 viewPosition;

void main()
{

// Ambient Calculation
	vec3 ambient = vec3(texture(u_Material.diffuse, texCoord)) * u_Light.ambient;

// Diffuse Calculation
	vec3 lightDirection = normalize(u_Light.position - fragPos);
	vec3 fragNormal = normalize(normal);
	float diffuseStrength = max(dot(normal, lightDirection), 0.0f);

	vec3 diffuse = u_Light.diffuse * diffuseStrength * vec3(texture(u_Material.diffuse, texCoord));

// Specular Calculation
	vec3 viewDir = normalize(viewPosition - fragPos);
	vec3 reflection = reflect(-lightDirection, fragNormal);

	float spec = pow(max(dot(viewDir, reflection), 0.0f), u_Material.shininess);
	vec3 specular =  spec * u_Light.specular * vec3(texture(u_Material.specular, texCoord));
	
// Final Result

	vec3 emission;
	if(texture(u_Material.specular, texCoord).r == 0.0f)
		emission = texture(u_Material.emission, texCoord + vec2(0.0, u_Time)).rgb;
	else
		emission = vec3(0.0f);

	vec3 result = ambient + diffuse + specular + emission;

	color = vec4(result, 1.0f);
}