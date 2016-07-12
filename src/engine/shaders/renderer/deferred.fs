#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D albedo;

struct Light {
  vec3 Position;
  vec3 Color;
  float Linear;
  float Quadratic;
  float Radius;
};

const int MAX_LIGHTS = 32;
uniform Light lights[MAX_LIGHTS];
uniform vec3 viewPos;

void main()
{
  // gBuffer
  vec3 FragPos = texture(position, TexCoords).rgb;
  vec3 Normal = texture(normal, TexCoords).rgb;
  vec3 Diffuse = texture(albedo, TexCoords).rgb;
  float Specular = texture(albedo, TexCoords).a;

  // Lighting
  vec3 lighting  = Diffuse * 0.1; // Ambient lighting
  vec3 viewDir  = normalize(viewPos - FragPos);

  for(int i = 0; i < MAX_LIGHTS; ++i)
  {
    // Calculate distance between light source and current fragment
    float distance = length(lights[i].Position - FragPos);
    if(distance < lights[i].Radius)
    {
      // Diffuse
      vec3 lightDir = normalize(lights[i].Position - FragPos);
      vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].Color;

      // Specular
      vec3 halfwayDir = normalize(lightDir + viewDir);
      float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
      vec3 specular = lights[i].Color * spec * Specular;

      // Attenuation
      float attenuation = 1.0 / (1.0 + lights[i].Linear * distance + lights[i].Quadratic * distance * distance);
      diffuse *= attenuation;
      specular *= attenuation;
      lighting += diffuse + specular;
    }
  }
  FragColor = vec4(lighting, 1.0);
}