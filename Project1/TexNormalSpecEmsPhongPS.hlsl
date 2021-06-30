#include "PointLight.hlsli"
#include "ShaderOps.hlsli"


cbuffer Cbuf
{
    matrix modelView;
    matrix modelViewProj;
};

Texture2D tex : register(t0);
Texture2D spec : register(t1);
Texture2D nmap : register(t2);
Texture2D ems : register(t3);

SamplerState splr;




float4 main(float3 viewPos : Position, float3 viewNormal : Normal, float3 tan : Tangent, float3 bitan : BiTangent, float2 tc : Texcoord) : SV_Target
{    
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
    
    const float4 specularSample = spec.Sample(splr, tc);
    const float ra = spec.Sample(splr, tc).r;
    const float3 specularReflectionColor = float3(ra, ra, ra);
    const float specularPower = pow(2.0f, ra * 13.0f);
    const float specularIntensity = 1.0f;
    
    
    const float3 specular = specularMapCalculation(viewPos, viewNormal, viewLightPos, specularReflectionColor, specularIntensity, specularIntensity, att) ;
    
    //Calculate emissive light color
    const float3 emission = ems.Sample(splr, tc).rgb;
    

    //const float a = spec.Sample(splr, tc).r;
    return float4(saturate((diffuse + ambient) * tex.Sample(splr, tc).rgb + specular +  emission), 1.0f);
}