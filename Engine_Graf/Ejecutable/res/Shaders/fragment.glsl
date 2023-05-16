		#version 330 core
		
		    layout(location = 0) out vec4 color;
		
		    in vec3 FragPos;            
		    in vec3 v_Normal;           
		
		struct Material 
		{				
		vec3 ambient;					
		vec3 diffuse;					
		vec3 specular;					
		float shininess;				
		};								
		
		struct Light 
		{					
		vec3 position;					
		vec3 direction;				
		vec3 ambient;					
		vec3 diffuse;					
		vec3 specular;					
		float constant;					
		float linear;					
		float quadratic;				
		};								
		
		uniform Material material;      
		uniform Light light;		    
		uniform vec3 viewPos;           
		
		void main()
		{
				vec3 ambient = light.ambient * material.ambient; 
		
				vec3 norm = normalize(v_Normal);                        
				vec3 lightDir = normalize(light.position - FragPos);    
				float diff = max(dot(norm, lightDir), 0.0);             
				vec3 diffuse = light.diffuse * (diff * material.diffuse);  
		
				vec3 viewDir = normalize(viewPos - FragPos);			
				vec3 reflectDir = reflect(-lightDir, norm);				
				float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
				vec3 specular =  light.specular * (spec * material.specular);			
		
				float distance = length(light.position - FragPos);														    
				float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
		
				vec3 result = attenuation * (ambient + diffuse + specular);      
				color = vec4(result,1.0);                                      
		};