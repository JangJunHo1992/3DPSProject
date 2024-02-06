#include "Shader_Defines.hlsli"


/* float2, float3, float4 == vector */
/* vector.x == vector.r */
/* vector.xy = 1.f;*/
/* float4x4 == matrix */
/* matrix._11_12 = 1.f; */

/* ���̴��� �������� == ������̺�(Constant Table) */
matrix			g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
float4			g_vCamPosition;
float			g_fRatio;

texture2D		g_Texture[2];

texture2D		g_DiffuseTexture;
texture2D		g_DepthTexture;

texture2D		g_MaskTexture;

texture2D		g_OriginTexture;
texture2D		g_DistortionTexture;

/* ������ ��ȯ(���庯ȯ, �亯ȯ, ������ȯ.)�� �����Ѵ�. */
/* ������ ���������� �߰�, �������� ������ �����Ѵ�.*/

/* ���� �װ�. */
/* �ε��� ������ .*/

struct VS_IN
{
	float3		vPosition : POSITION;
	float2		vTexcoord : TEXCOORD0;
};


struct VS_OUT
{
	float4		vPosition : SV_POSITION;
	float2		vTexcoord : TEXCOORD0;	
};



VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT		Out = (VS_OUT)0;

	/* In.vPosition * ���� * �� * ���� */
	matrix		matWV, matWVP;

	matWV = mul(g_WorldMatrix, g_ViewMatrix);
	matWVP = mul(matWV, g_ProjMatrix);

	Out.vPosition = mul(float4(In.vPosition, 1.f), matWVP);
	Out.vTexcoord = In.vTexcoord;

	return Out;
}

/* ����� ������ ��� .*/

/* ������ȯ : /w */ /* -> -1, 1 ~ 1, -1 */ 
/* ����Ʈ��ȯ-> 0, 0 ~ WINSX, WINSY */ 
/* �����Ͷ����� : ���������� ����Ͽ� �ȼ��� ������ �����. */


struct PS_IN
{
	float4		vPosition : SV_POSITION;
	float2		vTexcoord : TEXCOORD0;
};

struct PS_OUT 
{
	float4		vColor : SV_TARGET0;
};

/* �ȼ����̴� : �ȼ��� ��!!!! �� �����Ѵ�. */
PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	/* ù��° ������ ������� �ι�° ������ ��ġ�� �ִ� �ȼ��� ���� ���´�. */
	vector		vSourColor = g_Texture[0].Sample(LinearSampler, In.vTexcoord);	
	vector		vDestColor = g_Texture[1].Sample(LinearSampler, In.vTexcoord);

	Out.vColor = vSourColor + vDestColor;

	return Out;
}

PS_OUT PS_MAIN_ICON(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	/* ù��° ������ ������� �ι�° ������ ��ġ�� �ִ� �ȼ��� ���� ���´�. */
	vector		vSourColor = g_Texture[0].Sample(LinearSampler, In.vTexcoord);
	//vector		vDestColor = g_Texture[1].Sample(LinearSampler, In.vTexcoord);
	if (vSourColor.a < 0.3f)
		discard;

	Out.vColor = vSourColor;

	return Out;
}

PS_OUT PS_MAIN_PLAYER_RATIO(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	/* ù��° ������ ������� �ι�° ������ ��ġ�� �ִ� �ȼ��� ���� ���´�. */
	float2 vTexRatio = In.vTexcoord.x * g_fRatio;
	vector		vSourColor = g_Texture[0].Sample(LinearSampler, In.vTexcoord);

	float fRatio = vTexRatio;

	if (In.vTexcoord.x > g_fRatio)
		discard;
	//vector		vDestColor = g_Texture[1].Sample(LinearSampler, In.vTexcoord);
	
	if (vSourColor.a < 0.3f)
		discard;

	Out.vColor = vSourColor;

	return Out;
}

struct VS_OUT_EFFECT
{
	float4		vPosition : SV_POSITION;
	float2		vTexcoord : TEXCOORD0;
	float4		vProjPos : TEXCOORD1;
};


VS_OUT_EFFECT VS_MAIN_EFFECT(VS_IN In)
{
	VS_OUT_EFFECT		Out = (VS_OUT_EFFECT)0;

	matrix WorldMatrix = g_WorldMatrix;

	float3 vLook = normalize((g_vCamPosition * -1.f).xyz);
	float3 vRight = normalize(cross(float3(0.f, 1.f, 0.f), vLook));
	float3 vUp = normalize(cross(vLook, vRight));

	WorldMatrix[0] = float4(vRight, 0.f) * length(WorldMatrix[0]);
	WorldMatrix[1] = float4(vUp, 0.f) * length(WorldMatrix[1]);
	WorldMatrix[2] = float4(vLook, 0.f) * length(WorldMatrix[2]);


	/* In.vPosition * ���� * �� * ���� */
	matrix		matWV, matWVP;

	matWV = mul(g_WorldMatrix, g_ViewMatrix);
	matWVP = mul(matWV, g_ProjMatrix);

	Out.vPosition = mul(float4(In.vPosition, 1.f), matWVP);
	Out.vTexcoord = In.vTexcoord;
	Out.vProjPos = Out.vPosition;

	return Out;
}

struct PS_IN_EFFECT
{
	float4		vPosition : SV_POSITION;
	float2		vTexcoord : TEXCOORD0;
	float4		vProjPos : TEXCOORD1;
};

/* �ȼ����̴� : �ȼ��� ��!!!! �� �����Ѵ�. */
PS_OUT PS_MAIN_EFFECT(PS_IN_EFFECT In)
{
	PS_OUT			Out = (PS_OUT)0;

	Out.vColor = g_DiffuseTexture.Sample(LinearSampler, In.vTexcoord);

	if (Out.vColor.r < 0.3f &&
		Out.vColor.g < 0.3f &&
		Out.vColor.b < 0.3f )
		discard;

	float2	vDepthTexcoord;
	vDepthTexcoord.x = (In.vProjPos.x / In.vProjPos.w) * 0.5f + 0.5f;
	vDepthTexcoord.y = (In.vProjPos.y / In.vProjPos.w) * -0.5f + 0.5f;

	float4	vDepthDesc = g_DepthTexture.Sample(PointSampler, vDepthTexcoord);
	
	Out.vColor.a = Out.vColor.a * (vDepthDesc.y * 1000.f - In.vProjPos.w) * 2.f;

	return Out;
}

PS_OUT PS_MAIN_TRAIL(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vColor = float4(1.f, 0.2f, 0.1f, 1.f);

	//Out.vColor = g_DiffuseTexture.Sample(LinearSampler, In.vTexcoord);

	float4	vMaskDesc = g_MaskTexture.Sample(LinearSampler, In.vTexcoord);
	Out.vColor.a = max(vMaskDesc.x, 0);

	//Out.vColor.y = min(1 - vMaskDesc.x, 0.25f);
	//Out.vColor.z = min(max(1 - vMaskDesc.x, 0.3f), 0.7f);
	//Out.vColor.x = min(max(1 - vMaskDesc.x, 0.3f), 0.5f);

	return Out;
}

PS_OUT PS_MAIN_TRAIL_GREEN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vColor = float4(51.f/255.f,185.f/255.f,129.f/255.f, 1.0f);

	//Out.vColor = g_DiffuseTexture.Sample(LinearSampler, In.vTexcoord);

	float4	vMaskDesc = g_MaskTexture.Sample(LinearSampler, In.vTexcoord);
	Out.vColor.a = max(vMaskDesc.x, 0);

	//Out.vColor.y = min(1 - vMaskDesc.x, 0.25f);
	//Out.vColor.z = min(max(1 - vMaskDesc.x, 0.3f), 0.7f);
	//Out.vColor.x = min(max(1 - vMaskDesc.x, 0.3f), 0.5f);

	return Out;
}

PS_OUT PS_DISTORTION(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	Out.vColor = float4(51.f / 255.f, 185.f / 255.f, 129.f / 255.f, 1.0f);
	vector vDistortion = g_DistortionTexture.Sample(LinearSampler, In.vTexcoord);
	//vDistortion = vector(0.f, 0.f, 0.f, 1.f);
	//g_MaskTexture
	//if (0.01f < vDistortion.r)
	//{
	//	Out.vColor = vDistortion;//g_MaskTexture.Sample(ClampSampler, In.vTexcoord + (vDistortion.r * 0.1f));
	//	vector vMask = g_DistortionTexture.Sample(LinearSampler, In.vTexcoord);
	//	Out.vColor.a *= vMask.x;
	//}
	//else
	//	Out.vColor = g_MaskTexture.Sample(ClampSampler, In.vTexcoord);
	//Out.vColor.rgb *= vDistortion.rgb;//* 2-1;//g_MaskTexture.Sample(ClampSampler, In.vTexcoord + (vDistortion.r * 0.1f));
	vector vMask = g_MaskTexture.Sample(ClampSampler, In.vTexcoord);
	Out.vColor.a *= (vMask.x);
	
	if (Out.vColor.a < 0.3f)
		discard;
	//float alpha = 1.f;//�ʱ� ����
	//if (0.01f < vDistortion.r)
	//{
	//	// �ؽ��� ��ǥ�� ������� ���Ͽ� ������ ����
	//	float distortedAlpha = g_MaskTexture.Sample(ClampSampler, In.vTexcoord + (vDistortion.r * 0.1f)).r;
	//
	//	// ������ �����ϴ� ���� alpha�� ����
	//	alpha = distortedAlpha;
	//}
	//else
	//{
	//	// ����� ���� ���� ������ ����
	//	float originalAlpha = g_MaskTexture.Sample(ClampSampler, In.vTexcoord).r;
	//
	//	// ������ �����ϴ� ���� alpha�� ����
	//	alpha = originalAlpha;
	//}
	//
	//// ���� ���� ���� (���⼭�� ������ ����)
	//Out.vColor = float4(Out.vColor.r, Out.vColor.g, Out.vColor.b, alpha);

	return Out;
}

PS_OUT PS_VARG(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	vector vDistortion = g_DistortionTexture.Sample(LinearSampler, In.vTexcoord);

	if (0.01f < vDistortion.r)
		Out.vColor = g_OriginTexture.Sample(ClampSampler, In.vTexcoord + (vDistortion.r * 0.01f));
	else
		Out.vColor = g_OriginTexture.Sample(ClampSampler, In.vTexcoord);

	return Out;
}

technique11 DefaultTechnique
{
	/* ���� ���ϴ� Ư�� ���̴����� �׸��� �𵨿� �����Ѵ�. */
	pass UI
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_Default, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);
		/* ������������ */
		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}

	/* ���� �ٸ� ���¿� ���� ���ϴ� Ư�� ���̴����� �׸��� �𵨿� �����Ѵ�. */
	pass Effect
	{
		SetRasterizerState(RS_Cull_None);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend_Add, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_EFFECT();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_EFFECT();
	}	

	pass Trail
	{
		SetRasterizerState(RS_Cull_None);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend_Add, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_TRAIL();
	}

	pass Trail_Blue
	{
		SetRasterizerState(RS_Cull_None);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend_Add, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_TRAIL_GREEN();
	}

	pass Distortion // 4
	{
		SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 1.f), 0xffffffff);
		SetDepthStencilState(DSS_None, 0);
		SetRasterizerState(RS_Default);

		VertexShader = compile vs_5_0 VS_MAIN();
		HullShader = NULL;
		DomainShader = NULL;
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_DISTORTION();
	}

	pass Distortion_Varg // 5
	{
		SetBlendState(BS_Default, float4(0.f, 0.f, 0.f, 1.f), 0xffffffff);
		SetDepthStencilState(DSS_None, 0);
		SetRasterizerState(RS_Default);

		VertexShader = compile vs_5_0 VS_MAIN();
		HullShader = NULL;
		DomainShader = NULL;
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_VARG();
	}

	pass UI_ICON
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_Default, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);
		/* ������������ */
		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_ICON();
	}

	pass UI_PlayerRatio
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_Default, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);
		/* ������������ */
		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_PLAYER_RATIO();
	}
}
