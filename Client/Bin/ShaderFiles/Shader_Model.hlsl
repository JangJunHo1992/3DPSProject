
#include "Shader_Defines.hlsli"

matrix			g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
texture2D		g_DiffuseTexture;
texture2D		g_NormalTexture;

texture2D		g_DissolveTexture;

float			g_fLightFar;
float			g_fDissolveWeight;
struct VS_IN
{
	float3		vPosition : POSITION;
	float3		vNormal : NORMAL;
	float2		vTexcoord : TEXCOORD0;
	float3		vTangent : TANGENT;
};


struct VS_OUT
{
	float4		vPosition : SV_POSITION;
	float4		vNormal : NORMAL;
	float2		vTexcoord : TEXCOORD0;	
	float4		vWorldPos : TEXCOORD1;
	float4		vProjPos : TEXCOORD2;
	float4		vTangent : TANGENT;
	float4		vBinormal : BINORMAL;
};



VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT		Out = (VS_OUT)0;


	matrix		matWV, matWVP;

	matWV = mul(g_WorldMatrix, g_ViewMatrix);
	matWVP = mul(matWV, g_ProjMatrix);

	Out.vPosition = mul(float4(In.vPosition, 1.f), matWVP);
	Out.vNormal = normalize(mul(float4(In.vNormal, 0.f), g_WorldMatrix));
	Out.vTexcoord = In.vTexcoord;
	Out.vWorldPos = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	Out.vProjPos = Out.vPosition;
	Out.vTangent = normalize(mul(float4(In.vTangent, 0.f), g_WorldMatrix));
	Out.vBinormal = normalize(vector(cross(Out.vNormal.xyz, Out.vTangent.xyz), 0.f));

	return Out;
}

struct PS_IN
{
	float4		vPosition : SV_POSITION;
	float4		vNormal : NORMAL;
	float2		vTexcoord : TEXCOORD0;
	float4		vWorldPos : TEXCOORD1;
	float4		vProjPos : TEXCOORD2;
	float4		vTangent : TANGENT;
	float4		vBinormal : BINORMAL;
};

struct PS_OUT 
{
	float4		vDiffuse : SV_TARGET0;
	float4		vNormal : SV_TARGET1;
	float4		vDepth : SV_TARGET2;
};

/* «»ºøºŒ¿Ã¥ı : «»ºø¿« ªˆ!!!! ¿ª ∞·¡§«—¥Ÿ. */
PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	vector vMtrlDiffuse = g_DiffuseTexture.Sample(LinearSampler, In.vTexcoord);
	vector vNormalDesc = g_NormalTexture.Sample(LinearSampler, In.vTexcoord);

	float3 vNormal = vNormalDesc.xyz * 2.f - 1.f;

	float3x3 WorldMatrix = float3x3(In.vTangent.xyz, In.vBinormal.xyz, In.vNormal.xyz);

	vNormal = mul(vNormal, WorldMatrix);


	if (vMtrlDiffuse.a < 0.3f)
		discard;
	
	Out.vDiffuse = vMtrlDiffuse;	
	Out.vNormal = vector(vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 1000.0f, 0.0f, 0.0f);

	return Out;
}

struct PS_OUT_SHADOW
{
	vector		vLightDepth : SV_TARGET0;
};

PS_OUT_SHADOW PS_MAIN_SHADOW(PS_IN In)
{
	PS_OUT_SHADOW		Out = (PS_OUT_SHADOW)0;

	Out.vLightDepth = In.vProjPos.w / g_fLightFar;

	return Out;
}

PS_OUT PS_DISSOLVE_MAIN(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	float4 vColor = g_DiffuseTexture.Sample(ClampSampler, In.vTexcoord);
	float4 vDissolve = g_DissolveTexture.Sample(ClampSampler, In.vTexcoord);

	float sinTime = sin(g_fDissolveWeight);

	if (vColor.a == 0.f)
		clip(-1);

	if (vDissolve.r >= sinTime)
		vColor.a = 1;
	else
		vColor.a = 0;

	if (vDissolve.r >= sinTime - 0.05 && vDissolve.r <= sinTime + 0.05)
		vColor = float4(1, 0, 0, 1); // ª°
	else;

	if (vDissolve.r >= sinTime - 0.03 && vDissolve.r <= sinTime + 0.03)
		vColor = float4(1, 1, 0, 1); // ≥Î
	else;

	if (vDissolve.r >= sinTime - 0.025 && vDissolve.r <= sinTime + 0.025)
		vColor = float4(1, 1, 1, 1); // »Ú
	else;

	Out.vDiffuse = vColor;

	if (0 == Out.vDiffuse.a)
		discard;

	return Out;
};

technique11 DefaultTechnique
{	
	pass Model
	{		
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_Default, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}

	pass Shadow
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_Default, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SHADOW();
	}

	pass Dissolve
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_Default, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_DISSOLVE_MAIN();
	}
}
