#include "PixelShader2DHeader.hlsli"

//���G���ۂ����Ă����2D�V�F�[�_�[(�K���t�B���^�[)
//�œK���Ƃ����ĂȂ�����x������

//�G���g���[�|�C���g
float4 main(PS_INPUT input) : SV_TARGET
{
    //�摜�T�C�Y�̎擾
	uint2 size;
    tex.GetDimensions(size.x, size.y);

    //1�s�N�Z���ӂ��UV���Z�o
	const float2 duv = 1 / float2(size);

    //�����̃s�N�Z�����܂߂����a�ŁA�傫������΂���قǃ{�P�邪�d���Ȃ�B1�Ō��摜�Ɠ�����2�`4���x�𐄏�(�z��̐錾�Ɏg�p����邽�ߒ萔�o�b�t�@�̒u�������s��)
    const uint radius = 4;

    const uint sideLen = 2 * radius - 1;        //�S�͈͂̈�ӂ̒���
    const uint scrap = radius - 1;              //���a�̓��A�^�񒆂̃s�N�Z���𔲂�����

    float4 color[sideLen][sideLen];             //�����̃s�N�Z���𒆐S�Ƃ���sideLen * sideLen���̃s�N�Z���̐F���i�[

    //�����Ƃ��̎��͂̃s�N�Z����ێ�
    for (uint y = 0; y < sideLen; y++)
    {
        for (uint x = 0; x < sideLen; x++)
        {
            color[y][x] = tex.Sample(texSampler, input.uv + (float2(x, y) - float2(scrap, scrap)) * duv);
        }
    }

    const uint regionNum = 4;                                   //�̈搔(4�ŌŒ�)
    const float regionPixelNum = float(radius * radius);        //1�̈�ӂ�̃s�N�Z����

    float regionVarianceSum[regionNum];     //�e�̈�̐F�̕��U��RGBA�̍��v�l
    uint regionVarianceSumMinIndex = 0;     //�e�̈�̐F�̕��U��RGBA�̍��v�l�̂����ŏ��l���w�������C���f�b�N�X
    float4 colorAve[regionNum];             //�e�̈�̐F�̕���

    //�̈悲�ƂɃ��[�v
    for (uint region = 0; region < regionNum; region++)
    {
        //�̈�̋N�_�E�I�_���v�Z
        const uint2 regionStart = uint2(region % 2, region / 2) * scrap;
    	const uint2 regionEnd = regionStart + uint2(radius, radius);

        //�e�̈�̐F�̕��ς��Z�o
        colorAve[region] = float4(0, 0, 0, 0);
        for (uint yAveIndex = regionStart.y; yAveIndex < regionEnd.y; yAveIndex++)
        {
            for (uint xAveIndex = regionStart.x; xAveIndex < regionEnd.x; xAveIndex++)
            {
                colorAve[region] += color[yAveIndex][xAveIndex];
            }
        }
        colorAve[region] /= regionPixelNum;

        //�e�̈�̕��U���Z�o
        float4 regionColor = float4(0, 0, 0, 0);
        for (uint yVarIndex = regionStart.y; yVarIndex < regionEnd.y; yVarIndex++)
        {
            for (uint xVarIndex = regionStart.x; xVarIndex < regionEnd.x; xVarIndex++)
            {
                regionColor += pow(color[yVarIndex][xVarIndex] - colorAve[region], 2);
            }
        }
        regionColor /= regionPixelNum;

        //���U�ŏo���F��RGBA�����Z
        regionVarianceSum[region] = dot(regionColor, float4(1, 1, 1, 1));

        //���Z�����l�̍ŏ��l�̃C���f�b�N�X��ێ�
    	if (regionVarianceSum[regionVarianceSumMinIndex] > regionVarianceSum[region])
        {
            regionVarianceSumMinIndex = region;
        }
    }

    //���U�̍��Z�l���ŏ��ɂȂ�̈�̕��ϐF��Ԃ�
    return colorAve[regionVarianceSumMinIndex];
}
