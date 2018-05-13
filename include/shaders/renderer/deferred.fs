#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

//uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D albedo;
uniform sampler2D depth;

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

uniform mat4 view;
uniform mat4 projection;

vec3 getViewPositionFromDepth(float depth)
{
    depth = (depth * 2.0) - 1.0;
    vec2 ndc = (TexCoords * 2.0) - 1.0;
    vec4 pos = vec4(ndc, depth, 1.0);
    mat4 matInvProj = inverse(projection * view);
    pos = matInvProj * pos;
    return vec3(pos.xyz / pos.w);
}

void main()
{
  // gBuffer
  //vec3 FragPos = texture(position, TexCoords).rgb;
  float d = texture(depth, TexCoords).r;
  vec3 FragPos = getViewPositionFromDepth(d);
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
  //FragColor = vec4(d, d, d, 1.0);
}