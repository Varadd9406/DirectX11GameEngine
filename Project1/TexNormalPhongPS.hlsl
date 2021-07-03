#include "PointLight.hlsli"
#include "ShaderOps.hlsli"


cbuffer Cbuf : register(b2)
{
    matrix modelView;
    matrix modelViewProj;
};

cbuffer ObjectCbuf : register(b1)
{
    float specularIntensity;
    float specularPower;
    bool normalMapEnabled;
    float padding[1];
};


Texture2D tex : register(t0);
Texture2D nmap : register(t1);

SamplerState splr;




float4 main(float3 viewPos : Position, float3 viewNormal : Normal, float3 tan : Tangent, float3 bitan : BiTangent, float2 tc : Texcoord) : SV_Target
{
    
    viewNormal = normalize(viewNormal);
    
    
    //Fragment to light
    //const float3 viewFragToL = viewLightPos - viewPos;
    //const float distFragToL = length(viewFragToL);
    //const float3 viewDirFragToL = viewFragToL / distFragToL;
    
    
    //Create unit normals
    viewNormal = MapNormalViewSpace(tan, bitan, viewNormal, tc, nmap, splr);
    
    //Create Attenuation
    const float att = Attenuate(viewPos, viewNormal, viewLightPos, attConst, attLin, attQuad);
    
    //Calculate Diffuse light color
    const float3 diffuse = tex.Sample(splr, tc).rgb * diffuseColor * diffuseIntensity * diffuseCalculation(viewPos, viewNormal, viewLightPos, att);
    
    //Calculate Specular light color
    
    const float3 specular = specularMapCalculation(viewPos, viewNormal, viewLightPos, diffuseColor, specularIntensity, specularIntensity, att);
    
    //Calculate emissive light color
    const float3 emission = float3(0.0f, 0.0f, 0.0f);
    

    //const float a = spec.Sample(splr, tc).r;
    return float4(saturate((diffuse + ambient) * tex.Sample(splr, tc).rgb + specular + emission), 1.0f);
}