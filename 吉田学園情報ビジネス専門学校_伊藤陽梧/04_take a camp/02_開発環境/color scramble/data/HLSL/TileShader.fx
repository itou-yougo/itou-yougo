float4x4 WorldViewProj : WORLDVIEWPROJ;
float4x4 World :WORLD;
float3   LightDirection;
float4   DiffuseColor;
float3   Eye;
float4   SpecularColor;

struct VS_OUTPUT {
	float4 Position :POSITION;      // 座標
	float4 Color    :COLOR;         // ディフューズ
	float4 Specular :COLOR1;        // スペキュラ
};

//////////////////////////////////
/* 頂点シェーダ */
//////////////////////////////////
VS_OUTPUT VS(float3 Position : POSITION, float3 Normal : NORMAL ,float4 Diffuse : COLOR0)
{
	VS_OUTPUT Out;

	// ワールド座標
	Out.Position = mul(float4(Position, 1), WorldViewProj);

	// 法線
	float3 N = mul(-Normal, (float3x3)World);
	N = normalize(N);

	// スペキュラ
	float3 H = normalize(normalize(LightDirection) + normalize(Eye - mul(World, Position).xyz));
	Out.Specular = SpecularColor * dot(mul(Normal, (float3x3)World), H);
	Out.Specular = pow(Out.Specular, 8);

	// ライティング処理
	float LightPower = dot(N, LightDirection);
	LightPower = max(0, LightPower);
	
	// カラーの設定
	Out.Color = DiffuseColor * LightPower;
	Out.Color.a = 1.0f;

	return Out;
}

//////////////////////////////////
/* ピクセルシェーダ */
//////////////////////////////////
float4 PS(VS_OUTPUT In) :COLOR
{
	float4 outCol = In.Color;
	outCol.a = DiffuseColor.a;

	return outCol;
}

technique Shader
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}