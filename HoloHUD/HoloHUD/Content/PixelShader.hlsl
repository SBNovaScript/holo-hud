// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
    min16float4 pos   : SV_POSITION;
    min16float3 color : COLOR0;
};

// The pixel shader passes through the color data. The color data from 
// is interpolated and assigned to a pixel at the rasterization step.
min16float4 main(PixelShaderInput input) : SV_TARGET
{

    min16float colorToUse = smoothstep(0, 1.0, input.color);

    min16float3 finalColor = min16float3(0.7, colorToUse, colorToUse);

    min16float sinCurrentPosX = sin(input.pos.x);
    min16float sinCurrentPosY = sin(input.pos.y);
    min16float sinCurrentPosZ = sin(input.pos.z);

    min16float3 testColor = min16float3(sinCurrentPosX, sinCurrentPosY, sinCurrentPosZ);

    return min16float4(testColor, 1.0);
}
