
#include "Shader_Defines.hlsli"

matrix			g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;

texture2D		g_DiffuseTexture[2];
texture2D		g_MaskTexture;
texture2D		g_BrushTexture;

vector			g_vBrushPos = vector(50.f, 0.f, 20.f, 1.f);
float			g_fBrushRange = 10.f;



struct VS_IN
{
	float3		vPosition : POSITION;
	float3		vNormal : NORMAL;
	float2		vTexcoord : TEXCOORD0;
};


struct VS_OUT
{
	float4		vPosition : SV_POSITION;
	float4		vNormal : NORMAL;
	float2		vTexcoord : TEXCOORD0;	
	float4		vWorldPos : TEXCOORD1;
	float4		vProjPos : TEXCOORD2;
};



VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT		Out = (VS_OUT)0;

	/* In.vPosition * 월드 * 뷰 * 투영 */
	matrix		matWV, matWVP;

	matWV = mul(g_WorldMatrix, g_ViewMatrix);
	matWVP = mul(matWV, g_ProjMatrix);

	Out.vPosition = mul(float4(In.vPosition, 1.f), matWVP);
	Out.vNormal = normalize(mul(float4(In.vNormal, 0.f), g_WorldMatrix));
	Out.vTexcoord = In.vTexcoord;
	Out.vWorldPos = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	Out.vProjPos = Out.vPosition;

	return Out;
}

/* 통과된 정점을 대기 .*/

/* 투영변환 : /w */ /* -> -1, 1 ~ 1, -1 */ 
/* 뷰포트변환-> 0, 0 ~ WINSX, WINSY */ 
/* 래스터라이즈 : 정점정보에 기반하여 픽셀의 정보를 만든다. */


struct PS_IN
{
	float4		vPosition : SV_POSITION;
	float4		vNormal : NORMAL;
	float2		vTexcoord : TEXCOORD0;
	float4		vWorldPos : TEXCOORD1;
	float4		vProjPos : TEXCOORD2;
};

struct PS_OUT 
{
	float4		vDiffuse : SV_TARGET0;
	float4		vNormal : SV_TARGET1;
	float4		vDepth : SV_TARGET2;
};

/* 픽셀셰이더 : 픽셀의 색!!!! 을 결정한다. */
PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	/* 첫번째 인자의 방식으로 두번째 인자의 위치에 있는 픽셀의 색을 얻어온다. */
	vector		vSourDiffuse = g_DiffuseTexture[0].Sample(LinearSampler, In.vTexcoord * 100.0f);		
	vector		vDestDiffuse = g_DiffuseTexture[1].Sample(LinearSampler, In.vTexcoord * 100.0f);
	vector		vBrush = vector(0.f, 0.f, 0.f, 0.f);
	// vector		vBrush = g_BrushTexture.Sample(LinearSampler, In.vTexcoord);

	if (g_vBrushPos.x - g_fBrushRange < In.vWorldPos.x && In.vWorldPos.x <= g_vBrushPos.x + g_fBrushRange && 
		g_vBrushPos.z - g_fBrushRange < In.vWorldPos.z && In.vWorldPos.z <= g_vBrushPos.z + g_fBrushRange)
	{
		float2		vUV;

		vUV.x = (In.vWorldPos.x - (g_vBrushPos.x - g_fBrushRange)) / (2.f * g_fBrushRange);
		vUV.y = ((g_vBrushPos.z + g_fBrushRange) - In.vWorldPos.z) / (2.f * g_fBrushRange);

		vBrush = g_BrushTexture.Sample(LinearSampler, vUV);
	}

	vector		vMask = g_MaskTexture.Sample(LinearSampler, In.vTexcoord);

	vector		vMtrlDiffuse = vMask * vDestDiffuse + (1.f - vMask) * vSourDiffuse + vBrush;

	Out.vDiffuse = vector(vMtrlDiffuse.rgb, 1.f);
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);	
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 1000.0f, 0.0f, 0.0f);

	return Out;
}


technique11 DefaultTechnique
{
	/* 내가 원하는 특정 셰이더들을 그리는 모델에 적용한다. */
	pass Terrain
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_Default, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);

		/* 렌더스테이츠 */
		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}	
}
