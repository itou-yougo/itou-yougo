float MAP_WIDTH;
float MAP_HEIGHT;
float weight[8];
int OFFSET = 2.0f;

// 頂点シェーダアウトプット
struct VS_OUTPUT {
	float4 pos :POSITION;      // 座標
	float2 tex :TEXCOORD;      // テクスチャ座標
	float4 col :COLOR0;         // カラー
};

// テクスチャの設定
texture Tex;
sampler Sampler = sampler_state {
	texture = Tex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;

	AddressU = Clamp;
	AddressV = Clamp;
};


//******************************
// 頂点シェーダ
//******************************
VS_OUTPUT VS(float3 pos : POSITION, float2 tex : TEXCOORD,float4 col : COLOR0, float3 nor : NORMAL)
{
	VS_OUTPUT Out;
	Out.pos = float4(pos, 1.0f);
	Out.col = col;
	Out.tex = tex;

	return Out;
}


//******************************
// ピクセルシェーダ
//******************************
float4 BlurPS1(VS_OUTPUT In) :COLOR
{
	float4 Color = tex2D(Sampler, In.tex);
	
	Color *= weight[0];

	for (int nCnt = 1; nCnt < 8; nCnt++)
	{
		Color += weight[nCnt]
			* (tex2D(Sampler, In.tex + float2(+OFFSET*nCnt / MAP_WIDTH, 0))
				+ tex2D(Sampler, In.tex + float2(-OFFSET*nCnt / MAP_WIDTH, 0)));
	}


	return Color;
}
//******************************
// ピクセルシェーダ
//******************************
float4 BlurPS2(VS_OUTPUT In) :COLOR
{
	float4 Color = tex2D(Sampler, In.tex );

	Color *= weight[0];
	for (int nCnt = 1; nCnt < 8; nCnt++)
	{
		Color += weight[nCnt]
			* (tex2D(Sampler, In.tex + float2(0, +OFFSET*nCnt / MAP_HEIGHT))
				+ tex2D(Sampler, In.tex + float2(0, -OFFSET*nCnt / MAP_HEIGHT)));

	}

	return Color;
}

//******************************
// テクニック＊テクスチャあり
//******************************
technique texShader
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader  = compile ps_3_0 BlurPS1();
	}
	pass P1
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 BlurPS2();
	}
}