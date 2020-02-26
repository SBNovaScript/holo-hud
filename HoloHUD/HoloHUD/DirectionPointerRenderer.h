#pragma once

#include "pch.h"
#include "Common/DirectXHelper.h"
#include "../Common/DeviceResources.h"
#include "../Common/StepTimer.h"
#include "Content/ShaderStructures.h"

namespace HoloHUD
{
	// This direction pointer component should always point towards a common location.
	class DirectionPointerRenderer
	{
	public:

		// Shared pointer to a DeviceResources object.
		DirectionPointerRenderer(std::shared_ptr<DX::DeviceResources> const& deviceResources);

		// Once device dependent resources have been created, return asynchronously.
		std::future<void> CreateDeviceDependentResources();

		// Resets all device dependant resources, including shaders and buffers.
		void ReleaseDeviceDependentResources();

		// Update once per timer tick.
		void Update(DX::StepTimer const& timer);

		// Render one frame.
		void Render();

		// Sets the position of the direction pointer.
		void PositionDirectionPointer(winrt::Windows::UI::Input::Spatial::ISpatialPointerPose const& pointerPose);

		// Property accessors.
		void SetPosition(winrt::Windows::Foundation::Numerics::float3 const& pos) { m_position = pos; };
		winrt::Windows::Foundation::Numerics::float3 const& GetPosition() { return m_position; };

	private:
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// Direct3D resources for cube geometry.
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_modelConstantBuffer;

		// System resources for cube geometry.
		ModelConstantBuffer m_modelConstantBufferData;
		uint32_t m_indexCount = 0;

		// Variables used with the rendering loop.
		bool m_loadingComplete = false;
		winrt::Windows::Foundation::Numerics::float3 m_position = { 0.f, 0.f, -2.f };

		// Use if the current device supports VPRT.
		bool m_usingVprtShaders = true;
	};
}