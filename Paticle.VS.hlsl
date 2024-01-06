#include "Particle.hlsli"


//座標返還を行うVS
struct TransformationMatrix
{
    //32bitのfloatが4x4個
    float32_t4x4 WVP;
    float32_t4x4 World;
};

//CBuffer
//StructuredBuffer...簡単に言えば配列みたいなやつ
StructuredBuffer<TransformationMatrix>gTransformationMatrices:register(t0);

struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
    float32_t3 normal : NORMAL0;
};


VertexShaderOutput main(VertexShaderInput input, uint32_t instanceId : SV_InstanceID)
{
    VertexShaderOutput output;
    //mul...組み込み関数
    output.position = mul(input.position, gTransformationMatrices[instanceId].WVP);
    output.texcoord = input.texcoord;
    //法線の変換にはWorldMatrixの平衡移動は不要。拡縮回転情報が必要
    //左上3x3だけを取り出す
    //法線と言えば正規化をなのでそれを忘れないようにする
    //これを入れると何かだめになる
    output.normal = normalize(mul(input.normal, (float32_t3x3)gTransformationMatrices[instanceId].World));
    return output;
}}
