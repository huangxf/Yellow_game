#include "Camera.h"

void Camera::UpdateView()
{
	front = DirectX::XMVector3Normalize(front);
	up = DirectX::XMVector3Cross(front, right);
	up = DirectX::XMVector3Normalize(up);

	right = DirectX::XMVector3Cross(up, front);
	right = DirectX::XMVector3Normalize(right);

	float x = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(right, pos));
	float y = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(up, pos));
	float z = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(front, pos));

	float m[16] = { DirectX::XMVectorGetX(right), DirectX::XMVectorGetX(up), DirectX::XMVectorGetX(front), 0.0f,
					DirectX::XMVectorGetY(right), DirectX::XMVectorGetY(up), DirectX::XMVectorGetY(front), 0.0f,
					DirectX::XMVectorGetZ(right), DirectX::XMVectorGetZ(up), DirectX::XMVectorGetZ(front), 0.0f,
					                           x,                         y,                           z,  1.0f
	};

	view = DirectX::XMMATRIX(m);
	
}


