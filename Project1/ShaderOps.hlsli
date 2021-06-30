float3 MapNormalViewSpace
(
    const float3 tan,
    const float3 bitan,
    float3 viewNormal,
    const float2 tc,
    Texture2D nmap,
    SamplerState splr
)
{
    // build the tranform (rotation) into tangent space
    const float3x3 tanToView = float3x3
    (
        normalize(tan),
        normalize(bitan),
        normalize(viewNormal)
    );
    // sample and unpack the normal from texture into tangent space   
    const float3 normalSample = nmap.Sample(splr, tc).xyz;
    const float3 tanNormal = normalSample * 2.0f - 1.0f;
    viewNormal = -1.0f + normalSample * 2.0f;
    // bring normal from tanspace into view space
    return normalize(mul(tanNormal, tanToView));
}


float Attenuate
(
    const float3 viewPos,
    const float3 viewNormal,
    const float3 viewLightPos,
    uniform float attConst,
    uniform float attLin,
    uniform float attQuad
)
{
    const float distFragToL = length(viewLightPos - viewPos);
    return 1.0f / (attConst + attLin * distFragToL + attQuad * (distFragToL * distFragToL));
}

float3 diffuseCalculation
(
    const float3 viewPos,
    const float3 viewNormal,
    const float3 viewLightPos,
    const float attentuation
)
{
    const float3 viewFragToL = viewLightPos - viewPos;
    const float distFragToL = length(viewFragToL);
    const float3 viewDirFragToL = viewFragToL / distFragToL;
    
    //Diffuse stuff(pretty mature)
    return attentuation * max(0.0f, dot(viewDirFragToL, viewNormal));
}

float3 specularMapCalculation
(
    const float3 viewPos,
    const float3 viewNormal,
    const float3 viewLightPos,
    const float3 specularColor,
    uniform float specularIntensity,
    const float specularPower,
    const float attentuation
)
{
    const float3 viewFragToL = viewLightPos - viewPos;
    //Sketchy Specular Stuff(Needs Work)
    const float3 w = viewNormal * dot(viewFragToL, viewNormal);
    const float3 r = normalize(w * 2.0f - viewFragToL);

    //const float4 specularSample = spec.Sample(splr, tc);
    //const float ra = spec.Sample(splr, tc).r;
    //const float3 specularReflectionColor = float3(ra, ra, ra);
    //const float specularPower = pow(2.0f, ra * 13.0f);
    //const float3 specular = att * (diffuseColor * diffuseIntensity) * specularIntensity * pow(max(0.0f, dot(normalize(-r), normalize(worldPos))), specularPower);
    
    return (attentuation * (specularColor * specularIntensity) * pow(max(0.0f, dot(-r, normalize(viewPos))), specularPower));
}