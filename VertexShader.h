#ifndef _VERTEXSHADER
#define _VERTEXSHADER

#include "d3d11.h"
#include "wrl/client.h"
#include <d3dcompiler.h>
#include <string>
#include "LOG.h"


class VertexShader
{
public:
	bool Create(std::wstring path, D3D11_INPUT_ELEMENT_DESC * layoutDesc, UINT numElements);
	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetShader() {return  shader;}
	Microsoft::WRL::ComPtr<ID3D10Blob> GetBuffer() { return shader_buffer; }
	Microsoft::WRL::ComPtr<ID3D11InputLayout> GetInputLayout() { return inputLayout; }
	
	VertexShader(Microsoft::WRL::ComPtr<ID3D11Device> &device, LOG *logger): logger(logger),device(device) {}

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> shader;
	Microsoft::WRL::ComPtr<ID3D10Blob> shader_buffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	LOG* logger;
	Microsoft::WRL::ComPtr<ID3D11Device> &device;
};

#endif

