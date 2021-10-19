#version 440 core

out vec4 outputColor;

in vsOut 
{
	vec2 vUV;
	vec3 vNormal;
	vec3 vPosition;
	vec3 vTangent;
	vec3 vBinormal;
} vsIn;

uniform sampler2D texture0;
uniform float sunAngle;
uniform vec3 viewPos;

uniform float metalic        ;
uniform float roughness      ;
uniform float specValue      ;
uniform vec3  sunColor       ;
uniform vec3  ambientColor   ;
uniform float ambientStrength;

const float PI = 3.14159265359;
// a lot of functions in here https://gist.github.com/galek/53557375251e1a942dfa
inline float Distance(in vec3 a, in vec3 b) {
    float diff_x = a.x - b.x;
    float diff_y = a.y - b.y;
    float diff_z = a.z - b.z;
    return sqrt(diff_x * diff_x + diff_y * diff_y + diff_z * diff_z);
}

inline float saturate(in float x) {
  return max(0, min(1, x));
}

// compute fresnel specular factor for given base specular and product
vec3 fresnelSchlick(in float cosTheta, in vec3 F0, in float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}

// product could be NdV or VdH depending on used technique
vec3 fresnel_factor(in vec3 f0, in float product)
{
    return mix(f0, vec3(1.0 ), pow(1.01 - product, 5.0));
}

float G_schlick(in float roughness, in float NdV, in float NdL)
{
    float k = roughness * roughness * 0.5;
    float V = NdV * (1.0 - k) + k;
    float L = NdL * (1.0 - k) + k;
    return 0.25 / (V * L);
}

// following functions are copies of UE4
// for computing cook-torrance specular lighting terms

float D_blinn(in float roughness, in float NdH)
{
    float m = roughness * roughness;
    float m2 = m * m;
    float n = 2.0 / m2 - 2.0;
    return (n + 2.0) / (2.0 * PI) * pow(NdH, n);
}

float D_beckmann(in float roughness, in float NdH)
{
    float m = roughness * roughness;
    float m2 = m * m;
    float NdH2 = NdH * NdH;
    return exp((NdH2 - 1.0) / (m2 * NdH2)) / (PI * m2 * NdH2 * NdH2);
}

float D_GGX(in float roughness, in float NdH)
{
    float m = roughness * roughness;
    float m2 = m * m;
    float d = (NdH * m2 - NdH) * NdH + 1.0;
    return m2 / (PI * d * d);
}

// cook-torrance specular calculation                      
vec3 cooktorrance_specular(in float NdL, in float NdV, in float NdH, in vec3 specular, in float roughness)
{
    // float D = D_blinn(roughness, NdH);
    // float D = D_beckmann(roughness, NdH);
    float D = D_GGX(roughness, NdH);

    float G = G_schlick(roughness, NdV, NdL);

    float rim = mix(1.0 - roughness * metalic * 0.9, 1.0, NdV);

    return (1.0 / rim) * specular * G * D;
}

void main() {
	
	 // sun direction
    vec3 L = -vec3(0, sin(sunAngle), cos(sunAngle)); // wi
    
    vec4 tex = texture(texture0, vsIn.vUV);

    if (tex.a == 0) discard; // alpha clipping
    
    // float ao        = 1 - max(.2 , min(1, texture(AOTex, texCoord).r * AOIntensity));
    // float roughness = texture(roughnessTex, texCoord).r * roughnessPow;
    // float specValue = texture(specularTex, texCoord).r * max(specPower, 0);
    const float ao = 1;

    vec3 N = vsIn.vNormal;
    vec3 V = normalize(viewPos - vsIn.vPosition);
    vec3 H = normalize(V + L);

    float NdL = max(0.015, dot(N, L));
    float NdV = max(0.015, dot(N, V));
    float NdH = max(0.015, dot(N, H));
    float HdV = max(0.015, dot(H, V));

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, tex.xyz, metalic);

    vec3 specfresnel = fresnel_factor(F0, HdV);
    vec3 specular = cooktorrance_specular(NdL, NdV, NdH, specfresnel, roughness) * specValue * NdL * ao;

    vec3 ambient = ambientColor * (ambientStrength / 10);

    vec3 diffuse = tex.xyz * NdL * sunColor * ao;
    // vec3 indirectLights = CalculateIndirectLights(ao, roughness, specValue, F0);

    outputColor = vec4(diffuse + specular + ambient, 1);
}

