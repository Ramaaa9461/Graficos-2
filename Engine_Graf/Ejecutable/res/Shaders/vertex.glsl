		#version 330 core
		
		layout(location = 0) in vec3 position;
		
		layout(location = 1) in vec3 normal;

		layout(location = 2) in vec2 texCoord;
		
		out vec3 FragPos;				
		out vec3 v_Normal;				
		out vec2 v_TexCoord;	
		
		uniform mat4 projection;		
		uniform mat4 view;				
		uniform mat4 model;			
		
		void main()						
		{
			FragPos = vec3(model * vec4(position, 1.0));
			v_Normal = normal;
			v_TexCoord = texCoord;
		    gl_Position = projection * view * model * vec4(position,1.0);
		};


		