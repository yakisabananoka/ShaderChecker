#include "../Common/CommonShader3DHeader.hlsli"
#include "../Common/VertexToPixelHeader.hlsli"

#if !defined(PS_INPUT)
#define PS_INPUT VertexToPixel
#endif

#if !defined(PS_OUTPUT)
#define PS_OUTPUT float4
#endif

#define DX_D3D11_PS_CONST_FILTER_SIZE	(1280)	    // フィルター用定数バッファのサイズ

// シャドウマップパラメータ
struct ShadowMap
{
    float adjustDepth;      // 閾値深度補正値
    float gradationParam;   // グラデーション範囲
    float enable_Light0;    // ライト０への適用情報
    float enable_Light1;    // ライト１への適用情報

    float enable_Light2;    // ライト２への適用情報
    float3 padding;         // パディング
};

// 定数バッファピクセルシェーダー基本パラメータ
struct PsBase
{
    float4 factorColor;             // アルファ値等

    float mulAlphaColor;            // カラーにアルファ値を乗算するかどうか( 0.0f:乗算しない  1.0f:乗算する )
    float alphaTestRef;             // アルファテストで使用する比較値
    float2 padding1;

    int alphaTestCmpMode;           // アルファテスト比較モード( DX_CMP_NEVER など )
    int noLightAngleAttenuation;    // ライトの角度減衰を行わないか( 0:減衰を行う   1:減衰を行わない )
    int2 padding2;

    float4 ignoreTextureColor;      // テクスチャカラー無視処理用カラー

    float4 drawAddColor;            // 加算する色
};

// 定数バッファシャドウマップパラメータ
struct PsShadowMap
{
    ShadowMap data[3];
};

// 頂点シェーダー・ピクセルシェーダー共通パラメータ
cbuffer cbD3D11_CONST_BUFFER_COMMON : register(b0)
{
    Common common;
};
// 基本パラメータ
cbuffer cbD3D11_CONST_BUFFER_PS_BASE : register(b1)
{
    PsBase base;
};
// シャドウマップパラメータ
cbuffer cbD3D11_CONST_BUFFER_PS_SHADOWMAP : register(b2)
{
    PsShadowMap shadowMap;
};
