#pragma once

#include "../Common/DeviceResources.h"
#include "../Common/StepTimer.h"
#include "ShaderStructures.h"

namespace HoloHUD
{
    // This sample renderer instantiates a basic rendering pipeline.
    class SpinningCubeRenderer
    {
    public:

        // devices resources is a smart pointer which holds a DeviceResources object.
        SpinningCubeRenderer(std::shared_ptr<DX::DeviceResources> const& deviceResources);

        // future can get the result of an async call.
        std::future<void> CreateDeviceDependentResources();

        // Resets all device dependant resources, including shaders and buffers.
        void ReleaseDeviceDependentResources();

        // Update, using a StepTimer. StepTimer is a simplified way of managing a timed game loop.
        void Update(DX::StepTimer const& timer);

        // Render one frame using vertex and pixel shaders.
        void Render();

        // Repositions the sample hologram.
        void PositionHologram(winrt::Windows::UI::Input::Spatial::SpatialPointerPose const& pointerPose);

        // Tests positioning of the hologram.
        void TestPositionHologram();

        // Property accessors.
        void SetPosition(winrt::Windows::Foundation::Numerics::float3 const& pos)   { m_position = pos;  }
        winrt::Windows::Foundation::Numerics::float3 const& GetPosition()           { return m_position; }

    private:
        // Cached pointer to device resources.
        std::shared_ptr<DX::DeviceResources>            m_deviceResources;

        // Direct3D resources for cube geometry.
        Microsoft::WRL::ComPtr<ID3D11InputLayout>       m_inputLayout;
        Microsoft::WRL::ComPtr<ID3D11Buffer>            m_vertexBuffer;
        Microsoft::WRL::ComPtr<ID3D11Buffer>            m_indexBuffer;
        Microsoft::WRL::ComPtr<ID3D11VertexShader>      m_vertexShader;
        Microsoft::WRL::ComPtr<ID3D11GeometryShader>    m_geometryShader;
        Microsoft::WRL::ComPtr<ID3D11PixelShader>       m_pixelShader;
        Microsoft::WRL::ComPtr<ID3D11Buffer>            m_modelConstantBuffer;

        // System resources for cube geometry.
        ModelConstantBuffer                             m_modelConstantBufferData;
        uint32_t                                        m_indexCount = 0;

        // Variables used with the rendering loop.
        bool                                            m_loadingComplete = false;
        float                                           m_degreesPerSecond = 45.f;
        winrt::Windows::Foundation::Numerics::float3    m_position = { 0.f, 0.f, -2.f };

        // If the current D3D Device supports VPRT, we can avoid using a geometry
        // shader just to set the render target array index.
        bool                                            m_usingVprtShaders = false;
    };
}
