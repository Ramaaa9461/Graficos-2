		#version 330 core
		
		struct Material 
		{				
		vec3 ambient;					
		vec3 diffuse;					
		vec3 specular;					
		float shininess;				
		};								
		
		struct DirectionalLight 
		{
		    vec3 direction;
			vec3 color;
		    vec3 ambient;
		    vec3 diffuse;
		    vec3 specular;
		};							
		
		struct PointLight 
		{
		    vec3 position;
			vec3 color;
		    vec3 ambient;
		    vec3 diffuse;
		    vec3 specular;
		    float constant;
		    float linear;
		    float quadratic;
		};

		struct SpotLight 
		{
		    vec3 position;
		    vec3 direction;
			vec3 color;
		    vec3 ambient;
		    vec3 diffuse;
		    vec3 specular;
		    float constant;
		    float linear;
		    float quadratic;
		    float cutoff;
		    float outerCutoff;
		};

		layout(location = 0) out vec4 FragColor;
		
		const int MAX_DIRECTIONAL_LIGHTS = 10;
		const int MAX_POINT_LIGHTS = 10;
		const int MAX_SPOT_LIGHTS = 10;

		in vec3 FragPos;            
		in vec3 v_Normal;           

		uniform Material material;      
		
		uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
		uniform PointLight pointLights[MAX_POINT_LIGHTS];
		uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

		uniform int numDirectionalLights;
		uniform int numPointLights;
		uniform int numSpotLights;


		uniform vec3 viewPos;           
		
		vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) 
		{
		    vec3 lightDir = normalize(-light.direction);
		    vec3 reflectDir = reflect(-lightDir, normal);
		
		    vec3 ambient = light.ambient * material.ambient;
		    vec3 diffuse = light.diffuse * max(dot(normal, lightDir), 0.0) * material.diffuse;
		    vec3 specular = light.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * material.specular;
		
		    return (ambient + diffuse + specular) * light.color;
		}

		vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) 
		{
		    vec3 lightDir = normalize(light.position - fragPos);
		    vec3 reflectDir = reflect(-lightDir, normal);
		
		    float distance = length(light.position - fragPos);
		    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
		
		    vec3 ambient = light.ambient * material.ambient;
		    vec3 diffuse = light.diffuse * max(dot(normal, lightDir), 0.0) * material.diffuse;
		    vec3 specular = light.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * material.specular;
		
		    ambient *= attenuation;
		    diffuse *= attenuation;
		    specular *= attenuation;
		
		    return (ambient + diffuse + specular) * light.color;
		}

		vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) 
		{
		    vec3 lightDir = normalize(light.position - fragPos);
		    vec3 reflectDir = reflect(-lightDir, normal);
		
		    float distance = length(light.position - fragPos);
		    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
		    float theta = dot(lightDir, normalize(-light.direction));
		    float epsilon = light.cutoff - light.outerCutoff;
		    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
		
		    vec3 ambient = light.ambient * material.ambient;
		    vec3 diffuse = light.diffuse * max(dot(normal, lightDir), 0.0) * material.diffuse;
		    vec3 specular = light.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * material.specular;
		
		    ambient *= attenuation * intensity;
		    diffuse *= attenuation * intensity;
		    specular *= attenuation * intensity;
		
		    return (ambient + diffuse + specular) * light.color;
		}
		
		void main()
		{
			vec3 norm = normalize(v_Normal);
			vec3 viewDir = normalize(viewPos - FragPos);

		    vec3 resultDir = vec3(0.0);
			vec3 resultPoint = vec3(0.0);
			vec3 resultSpot = vec3(0.0);

			for (int i = 0; i < numDirectionalLights; i++) 
			{
			    if (i >= MAX_DIRECTIONAL_LIGHTS)
				{
					break;
				}

			    resultDir += CalculateDirectionalLight(directionalLights[i], norm, viewDir);
			}

			for (int i = 0; i < numPointLights; i++) 
			{
			    if (i >= MAX_POINT_LIGHTS) 
				{
					break;
				}

			    resultPoint += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);
			}

			for (int i = 0; i < numSpotLights; i++) 
			{
			  if (i >= MAX_SPOT_LIGHTS) 
			  {
				break;
			  }

			  resultSpot += CalculateSpotLight(spotLights[i], norm, FragPos, viewDir);
			}

			vec3 result = resultDir + resultSpot + resultPoint;

			FragColor = vec4(result, 1.0);                                
		};