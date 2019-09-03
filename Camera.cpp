#include "Camera.h"

void Camera::UpdateView()
{
	look = DirectX::XMVector3Normalize(look);
	up = DirectX::XMVector3Cross(look, right);
	up = DirectX::XMVector3Normalize(up);

	right = DirectX::XMVector3Cross(up, look);
	right = DirectX::XMVector3Normalize(right);

	float x = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(right, pos));
	float y = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(up, pos));
	float z = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(look, pos));

	float m[16] = { DirectX::XMVectorGetX(right), DirectX::XMVectorGetX(up), DirectX::XMVectorGetX(look), 0.0f,
					DirectX::XMVectorGetY(right), DirectX::XMVectorGetY(up), DirectX::XMVectorGetY(look), 0.0f,
					DirectX::XMVectorGetZ(right), DirectX::XMVectorGetZ(up), DirectX::XMVectorGetZ(look), 0.0f,
					                           x,                         y,                           z, 1.0f
	};

	view = DirectX::XMMATRIX(m);
	
}