#version 400 core
layout(location = 0) out vec4 FragColor;

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

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutoff;
	float outterCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

#define NR_POINT_LIGHTS 4

uniform PointLight u_PointLights[NR_POINT_LIGHTS];
uniform DirLight u_dirLight;
uniform SpotLight u_SpotLight;

uniform Material u_Material;

uniform float u_Time;

uniform vec3 viewPosition;

vec3 CalcDirLight(DirLight dirLight, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight pointLight, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 viewDir);

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform PointLight u_PointLight;

void main()
{
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPosition - fragPos);
	
// Emission Calculation

	vec3 emission;
	if(texture(u_Material.specular, texCoord).r == 0.0f)
		emission = texture(u_Material.emission, texCoord + vec2(0.0, u_Time)).rgb;
	else
		emission = vec3(0.0f);

	// Lighting Calculations

	// Directional Light
	vec3 result = CalcDirLight(u_dirLight, norm, viewDir);

	// Point Light
	for(int i=0; i<NR_POINT_LIGHTS; i++)
		result += CalcPointLight(u_PointLights[i], norm, viewDir);


	// Spot Light
	result = CalcPointLight(u_PointLight, norm, viewDir);

	FragColor = vec4(result, 1.0f);
}


vec3 CalcDirLight(DirLight dirLight, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-dirLight.direction);

	// Calculate Diffuse 
	float diff = max(dot(normal, lightDir), 0.0f);

	// Calculate Specular
	vec3 reflection = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflection), 0.0f), u_Material.shininess);

	vec3 ambient = dirLight.ambient * texture(u_Material.diffuse, texCoord).rgb;
	vec3 diffuse = dirLight.diffuse * diff * texture(u_Material.diffuse, texCoord).rgb;
	vec3 specular = dirLight.specular * spec * texture(u_Material.specular, texCoord).rgb;

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight pointLight, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(pointLight.position - fragPos);

	// Calculate Diffuse 
	float diff = max(dot(normal, lightDir), 0.0f);

	// Calculate Specular
	vec3 reflection = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflection), 0.0f), 32.0f);

	vec3 ambient = pointLight.ambient * texture(texture_diffuse1, texCoord).rgb;
	vec3 diffuse = pointLight.diffuse * diff * texture(texture_diffuse1, texCoord).rgb;
	vec3 specular = pointLight.specular * spec * texture(texture_specular1, texCoord).rgb;

	// Attenuation
	float Distance = length(pointLight.position - fragPos);

	float attenuation = 1.0f / (pointLight.constant + pointLight.linear * Distance + pointLight.quadratic * (Distance * Distance));
	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(spotLight.position - fragPos);

	// Calculate Diffuse 
	float diff = max(dot(normal, lightDir), 0.0f);

	// Calculate Specular
	vec3 reflection = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflection), 0.0f), u_Material.shininess);

	vec3 ambient = spotLight.ambient * texture(u_Material.diffuse, texCoord).rgb;
	vec3 diffuse = spotLight.diffuse * diff * texture(u_Material.diffuse, texCoord).rgb;
	vec3 specular = spotLight.specular * spec * texture(u_Material.specular, texCoord).rgb;

	// Attenuation
	float Distance = length(spotLight.position - fragPos);

	float attenuation = 1.0f / (spotLight.constant + spotLight.linear * Distance + spotLight.quadratic * (Distance * Distance));
	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	// Intensity

	float theta = dot(lightDir, normalize(-spotLight.direction));
	float epsilon = spotLight.cutoff - spotLight.outterCutOff;
	float intensity = clamp((theta - spotLight.outterCutOff) / epsilon, 0.0f, 1.0f);

	diffuse *= intensity;
	specular *= intensity;

	return (ambient + diffuse + specular);
}