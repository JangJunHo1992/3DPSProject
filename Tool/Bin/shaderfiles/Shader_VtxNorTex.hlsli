
matrix			g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
				//임시 점광원
vector			g_vLightPos = vector(50.f, 10.f, 50.f, 1.f);
float			g_fLightRange = 30.f;
				//방향성광원
vector			g_vLightDir = vector(1.f, -1.f, 1.f, 0.f);
vector			g_vLightDiffuse = vector(1.f, 1.f, 1.f, 1.f);
vector			g_vLightAmbient = vector(1.f, 1.f, 1.f, 1.f);
vector			g_vLightSpecular = vector(1.f, 1.f, 1.f, 1.f);
				//엠비언트, 스펙큘러
vector			g_vMtrlAmbient = vector(0.3f, 0.3f, 0.3f, 1.f);
vector			g_vMtrlSpecular = vector(1.f, 1.f, 1.f, 1.f);
				//텍스쳐
texture2D		g_DiffuseTexture[2];
texture2D		g_MaskTexture;
				//카메라 위치
vector			g_vCamPosition;


sampler DefaultSampler = sampler_state
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = wrap;
	AddressV = wrap;

};

struct VS_IN
{
	float3		vPosition : POSITION;
	float3		vNormal : NORMAL;
	float2		vTexcoord : TEXCOORD0;
};


struct VS_OUT
{
	float4		vPosition : SV_POSITION;
	float3		vNormal : NORMAL;
	float2		vTexcoord : TEXCOORD0;
	float4		vWorldPos : TEXCOORD1;

};



VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT		Out = (VS_OUT)0;

	/* In.vPosition * 월드 * 뷰 * 투영 */
	matrix		matWV, matWVP;

	matWV = mul(g_WorldMatrix, g_ViewMatrix);
	matWVP = mul(matWV, g_ProjMatrix);

	Out.vPosition = mul(float4(In.vPosition, 1.f), matWVP);
	Out.vNormal = mul(float4(In.vNormal, 0.f), g_WorldMatrix);
	Out.vTexcoord = In.vTexcoord;
	Out.vWorldPos = mul(float4(In.vPosition, 1.f), g_WorldMatrix);

	return Out;
}

/* 통과된 정점을 대기 .*/

/* 투영변환 : /w */ /* -> -1, 1 ~ 1, -1 */
/* 뷰포트변환-> 0, 0 ~ WINSX, WINSY */
/* 래스터라이즈 : 정점정보에 기반하여 픽셀의 정보를 만든다. */


struct PS_IN
{
	float4		vPosition : SV_POSITION;
	float3		vNormal : NORMAL;
	float2		vTexcoord : TEXCOORD0;
	float4		vWorldPos : TEXCOORD1;
};

struct PS_OUT
{
	float4		vColor : SV_TARGET0;
};

/* 픽셀셰이더 : 픽셀의 색!!!! 을 결정한다. */
PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	/* 첫번째 인자의 방식으로 두번째 인자의 위치에 있는 픽셀의 색을 얻어온다. */
	vector		vSourDiffuse = g_DiffuseTexture[0].Sample(DefaultSampler, In.vTexcoord * 100.0f);
	vector		vDestDiffuse = g_DiffuseTexture[1].Sample(DefaultSampler, In.vTexcoord * 100.0f);

	vector		vMask = g_MaskTexture.Sample(DefaultSampler, In.vTexcoord);
	//두가지중 어떤것의 색을 나타낼건지 알기 위해서 식을 이렇게 만들어둠
	vector vMtrlDiffuse = vMask * vDestDiffuse + (1.f - vMask) * vSourDiffuse;

	float		fShade = max(dot(normalize(g_vLightDir) * -1.f, normalize(In.vNormal)), 0.f);

	/* 스펙큘러가 보여져야하는 영역에서는 1로, 아닌 영역에서는 0으로 정의되는 스펙큘러의 세기가 필요하다. */
	vector		vLook = In.vWorldPos - g_vCamPosition;
	vector		vReflect = reflect(normalize(g_vLightDir), normalize(In.vNormal));//이 함수를 사용하므로서 반사벡터를 한번에 처리해준다

	float		fSpecular = pow(max(dot(normalize(vLook) * -1.f, normalize(vReflect)), 0.f), 40.f);//pow는 제곱근을 하는거임

	Out.vColor = g_vLightDiffuse * vMtrlDiffuse * min((fShade + (g_vLightAmbient * g_vMtrlAmbient)), 1.f)
		+ (g_vLightSpecular * g_vMtrlSpecular) * fSpecular;

	return Out;
}

PS_OUT PS_MAIN_POINT(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	/* 첫번째 인자의 방식으로 두번째 인자의 위치에 있는 픽셀의 색을 얻어온다. */
	vector		vMtrlDiffuse = g_DiffuseTexture[0].Sample(DefaultSampler, In.vTexcoord * 100.0f);

	vector		vLightDir = In.vWorldPos - g_vLightPos;


	float		fAtt = max(g_fLightRange - length(vLightDir), 0.f) / g_fLightRange;

	float		fShade = max(dot(normalize(vLightDir) * -1.f, normalize(In.vNormal)), 0.f);

	/* 스펙큘러가 보여져야하는 영역에서는 1로, 아닌 영역에서는 0으로 정의되는 스펙큘러의 세기가 필요하다. */
	vector		vLook = In.vWorldPos - g_vCamPosition;
	vector		vReflect = reflect(normalize(vLightDir), normalize(In.vNormal));

	float		fSpecular = pow(max(dot(normalize(vLook) * -1.f, normalize(vReflect)), 0.f), 30.f);

	Out.vColor = (g_vLightDiffuse * vMtrlDiffuse * min((fShade + (g_vLightAmbient * g_vMtrlAmbient)), 1.f)
		+ (g_vLightSpecular * g_vMtrlSpecular) * fSpecular) * fAtt;

	return Out;
}

technique11 DefaultTechnique
{
	/* 내가 원하는 특정 셰이더들을 그리는 모델에 적용한다. */
	pass Terrain
	{
		/* 렌더스테이츠 */
		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}
	//임시.. 점광원 테스트용// 이름만 보아도 곧 지울것같다
	pass Delete
	{
		/* 렌더스테이츠 */
		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		HullShader = NULL;
		DomainShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_POINT();
	}
}
