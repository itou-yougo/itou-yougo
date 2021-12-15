float4x4 WorldViewProj : WORLDVIEWPROJ;
float4x4 World :WORLD;
float3   LightDirection;
float4   DiffuseColor;
float3   Eye;
float4   SpecularColor;
float3   RimColor;
float    RimPower;
float4   TexColor;

struct VS_IN
{
	float3 Position : POSITION;
	float3 Normal   : NORMAL;
	float4 Color    :COLOR;         // ディフューズ
	float2 TexCoord :TEXCOORD;      // テクスチャUV
};

struct VS_OUT
{
	float4 Position     : POSITION;
	float4 Color        : COLOR;         // ディフューズ
	float4 Specular     : COLOR1;
	float2 TexCoord     : TEXCOORD;     // テクスチャUV
	float3 viewDir      : TEXCOORD1;
	float3 normalDir    : TEXCOORD2;
	float3 CubeTexCoord : TEXCOORD3; // キューブテクスチャTEX
	float2 ToonTexCoord : TEXCOORD4;
};

texture Tex;
sampler Sampler = sampler_state {
	Texture = Tex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

texture CubeTex;
samplerCUBE SamplerCube = sampler_state {
	Texture = CubeTex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

/* テクスチャのサンプラ― */
texture ToonTex;
sampler ToonSampler = sampler_state {
	Texture = ToonTex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;

	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = clamp;
	AddressV = Wrap;
	AddressW = Wrap;
};

//////////////////////////////////
/* 頂点シェーダ */
//////////////////////////////////
VS_OUT VS(VS_IN In)
{
	VS_OUT Out;

	// ワールド座標
	Out.Position = mul(float4(In.Position, 1), WorldViewProj);

	// 法線
	Out.normalDir = mul(In.Normal, (float3x3)World);
	Out.normalDir = normalize(Out.normalDir);

	// ライティング処理
	float LightPower = dot(Out.normalDir, LightDirection);
	LightPower = max(0, LightPower);
	
	// カラーの設定
	Out.Color = DiffuseColor;
	Out.Color.a = 1.0f;
	
	// スペキュラ
	float3 H = normalize(normalize(LightDirection) + normalize(Eye - mul(World, In.Position)));
	Out.Specular = SpecularColor * dot(Out.normalDir, H);
	Out.Specular = pow(Out.Specular, 8);

	// viewベクトル
	Out.viewDir = normalize(Eye - mul(World, In.Position).xyz);
	
	// UV
	Out.TexCoord = In.TexCoord;

	// キューブテクスチャ
    Out.CubeTexCoord = reflect(mul(World, In.Position).xyz - Eye, Out.normalDir);

	Out.ToonTexCoord.x = LightPower;
	Out.ToonTexCoord.y = 0.5f;

	return Out;
}

//////////////////////////////////
/* ピクセルシェーダ */
//////////////////////////////////
float4 PS(VS_OUT In) :COLOR
{
	float4 col = tex2D(ToonSampler, In.ToonTexCoord) * In.Color + In.Specular;

	// リム
	float rim = 1.0f - abs(dot(In.viewDir, In.normalDir));
	float3 emission = RimColor * pow(rim, RimPower) * RimPower;
	col.rgb += emission;
	col = float4(col.rgb, DiffuseColor.a);

	return col;
}

//////////////////////////////////
/* テクスチャピクセルシェーダ */
//////////////////////////////////
float4 PS_TEX(VS_OUT In) :COLOR
{
	float4 col = (TexColor * tex2D(Sampler, In.TexCoord)) * tex2D(ToonSampler, In.ToonTexCoord) * In.Color + In.Specular;

	// リム
	float rim = 1.0f - abs(dot(In.viewDir, In.normalDir));
	float3 emission = RimColor * pow(rim, RimPower) * RimPower;
	col.rgb+= emission;
	col = float4(col.rgb, DiffuseColor.a);

	return col;
}

technique Shader
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}

	pass P1
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS_TEX();
	}
}