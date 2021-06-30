cbuffer LightCbuf
{
    float3 lightPos;
    float3 ambient;
    float3 diffuseColor;
    float diffuseIntensity;
    float attConst;
    float attLin;
    float attQuad;
};

cbuffer ObjectCbuf
{
    float specularIntensity;
    float specularPower;
    bool normalMapEnabled;
    float padding[1];
};

cbuffer Cbuf
{
    matrix modelView;
    matrix modelViewProj;
};

Texture2D tex : register(t0);
Texture2D spec : register(t1);
Texture2D nmap : register(t2);

SamplerState splr;

float4 main(float3 worldPos : Position, float3 viewNormal : Normal, float3 tan : Tangent, float3 bitan : BiTangent, float2 tc : Texcoord) : SV_Target
{
    //Tangent Normals(crtl+c/v)
    const float3x3 tanToView = float3x3(
        normalize(tan),
        normalize(bitan),
        normalize(viewNormal)
    );
    // unpack normal data
    const float3 normalSample = nmap.Sample(splr, tc).xyz;
    viewNormal = -1.0f + normalSample * 2.0f;
    viewNormal.y = -viewNormal.y;
    // bring normal from tanspace into view space
    viewNormal = mul(viewNormal, tanToView);
    
    
    //Diffuse stuff(pretty mature)
    const float3 vTol = lightPos - worldPos;
    const float distTol = length(vTol);
    const float3 dirTol = vTol / distTol;
    const float att = 1.0f / (attConst + attLin * distTol + attQuad * (distTol * distTol));
    const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirTol, viewNormal));
    
    
    //Sketchy Specular Stuff(Needs Work)
    const float3 w = viewNormal * dot(vTol, viewNormal);
    const float3 r = w * 2.0f - vTol;

    const float4 specularSample = spec.Sample(splr, tc);
    const float ra = spec.Sample(splr, tc).r;
    const float3 specularReflectionColor = float3(ra, ra, ra);
    const float specularPower = pow(2.0f, ra*13.0f);
    //const float3 specular = att * (diffuseColor * diffuseIntensity) * specularIntensity * pow(max(0.0f, dot(normalize(-r), normalize(worldPos))), specularPower);
    
    const float3 specular = (att * (diffuseColor * diffuseIntensity) * pow(max(0.0f, dot(normalize(-r), normalize(worldPos))), specularPower)) * specularReflectionColor;
    //const float a = spec.Sample(splr, tc).r;
    return float4(saturate((diffuse + ambient) * tex.Sample(splr, tc).rgb + specular), 1.0f);
}