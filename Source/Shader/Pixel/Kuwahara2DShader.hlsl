#include "PixelShader2DHeader.hlsli"

//油絵っぽくしてくれる2Dシェーダー(桑原フィルター)
//最適化とかしてないから遅いかも

//エントリーポイント
float4 main(PS_INPUT input) : SV_TARGET
{
    //画像サイズの取得
	uint2 size;
    tex.GetDimensions(size.x, size.y);

    //1ピクセル辺りのUVを算出
	const float2 duv = 1 / float2(size);

    //自分のピクセルを含めた半径で、大きくすればするほどボケるが重くなる。1で元画像と同じで2～4程度を推奨(配列の宣言に使用されるため定数バッファの置き換え不可)
    const uint radius = 4;

    const uint sideLen = 2 * radius - 1;        //全範囲の一辺の長さ
    const uint scrap = radius - 1;              //半径の内、真ん中のピクセルを抜いた分

    float4 color[sideLen][sideLen];             //自分のピクセルを中心としたsideLen * sideLen個分のピクセルの色を格納

    //自分とその周囲のピクセルを保持
    for (uint y = 0; y < sideLen; y++)
    {
        for (uint x = 0; x < sideLen; x++)
        {
            color[y][x] = tex.Sample(texSampler, input.uv + (float2(x, y) - float2(scrap, scrap)) * duv);
        }
    }

    const uint regionNum = 4;                                   //領域数(4で固定)
    const float regionPixelNum = float(radius * radius);        //1領域辺りのピクセル数

    float regionVarianceSum[regionNum];     //各領域の色の分散のRGBAの合計値
    uint regionVarianceSumMinIndex = 0;     //各領域の色の分散のRGBAの合計値のうち最小値を指し示すインデックス
    float4 colorAve[regionNum];             //各領域の色の平均

    //領域ごとにループ
    for (uint region = 0; region < regionNum; region++)
    {
        //領域の起点・終点を計算
        const uint2 regionStart = uint2(region % 2, region / 2) * scrap;
    	const uint2 regionEnd = regionStart + uint2(radius, radius);

        //各領域の色の平均を算出
        colorAve[region] = float4(0, 0, 0, 0);
        for (uint yAveIndex = regionStart.y; yAveIndex < regionEnd.y; yAveIndex++)
        {
            for (uint xAveIndex = regionStart.x; xAveIndex < regionEnd.x; xAveIndex++)
            {
                colorAve[region] += color[yAveIndex][xAveIndex];
            }
        }
        colorAve[region] /= regionPixelNum;

        //各領域の分散を算出
        float4 regionColor = float4(0, 0, 0, 0);
        for (uint yVarIndex = regionStart.y; yVarIndex < regionEnd.y; yVarIndex++)
        {
            for (uint xVarIndex = regionStart.x; xVarIndex < regionEnd.x; xVarIndex++)
            {
                regionColor += pow(color[yVarIndex][xVarIndex] - colorAve[region], 2);
            }
        }
        regionColor /= regionPixelNum;

        //分散で出た色のRGBAを合算
        regionVarianceSum[region] = dot(regionColor, float4(1, 1, 1, 1));

        //合算した値の最小値のインデックスを保持
    	if (regionVarianceSum[regionVarianceSumMinIndex] > regionVarianceSum[region])
        {
            regionVarianceSumMinIndex = region;
        }
    }

    //分散の合算値が最小になる領域の平均色を返す
    return colorAve[regionVarianceSumMinIndex];
}
