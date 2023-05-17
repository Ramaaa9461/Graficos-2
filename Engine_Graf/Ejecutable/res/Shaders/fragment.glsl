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
		
		in vec3 FragPos;            
		in vec3 v_Normal;           

		uniform Material material;      
		
		uniform DirectionalLight directionalLights[10];
		uniform PointLight pointLights[10];
		uniform SpotLight spotLights[10];
		uniform vec3 viewPos;           
		
		vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) 
		{
		    vec3 lightDir = normalize(-light.direction);
		    vec3 reflectDir = reflect(-lightDir, normal);
		
		    vec3 ambient = light.ambient * material.ambient;
		    vec3 diffuse = light.diffuse * max(dot(normal, lightDir), 0.0) * material.diffuse;
		    vec3 specular = light.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * material.specular;
		
		    return ambient + diffuse + specular;
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
		
		    return ambient + diffuse + specular;
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
		
		    return ambient + diffuse + specular;
		}
		
		void main()
		{
			vec3 norm = normalize(v_Normal);
			vec3 viewDir = normalize(viewPos - FragPos);

			vec3 result;

			for (int i = 0; i < 10; i++) 
			{
				result += CalculateDirectionalLight(directionalLights[i], norm, viewDir);
				result += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);
				result += CalculateSpotLight(spotLights[i], norm, FragPos, viewDir);
			}

			FragColor = vec4(result, 1.0);                                  
		};