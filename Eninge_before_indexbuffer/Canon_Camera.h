#pragma once

#include "xStd.h"

class Canon_Camera
{
public:

	D3DXMATRIX			 m_matView;
	D3DXMATRIX			 m_matProj;

	D3DXVECTOR3			camera_position;   D3DXVECTOR3 camera_look;
	D3DXVECTOR3			fake_up;				 D3DXVECTOR3 camera_up;
	D3DXVECTOR3			Target_at;        	 D3DXVECTOR3 camera__Right;

	float Vertical_Fov_Angle;
	float Aspect_Ratio;//가로세로비
	float Near_Plane_Distance;
	float Far_Plane_Distance;

	void Set_View_Matrix(
		D3DXVECTOR3 camera_position_in = D3DXVECTOR3(10.0f, 10.0f, -10.0f),
		D3DXVECTOR3 fake_up_in = D3DXVECTOR3(0.0f, 1.0f, 0.0f),
		D3DXVECTOR3 Target_at_in = D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		camera_position = camera_position_in;
		fake_up = fake_up_in;
		Target_at = Target_at_in;

		D3DXMatrixLookAtLH(&m_matView,
			&camera_position,
			&Target_at,
			&fake_up); // 뷰 행렬 반환
	}

	void Set_Projection_Matrix(float Vertical_Fov_Angle_in, float Aspect_Ratio_in, float Near_Plane_Distance_in, float Far_Plane_Distance_in)
	{
		Vertical_Fov_Angle = Vertical_Fov_Angle_in;
		Aspect_Ratio = Aspect_Ratio_in;
		Near_Plane_Distance = Near_Plane_Distance_in;
		Far_Plane_Distance = Far_Plane_Distance_in;

		D3DXMatrixPerspectiveFovLH(&m_matProj,
			(float)D3DX_PI * Vertical_Fov_Angle,
			Aspect_Ratio,
			Near_Plane_Distance,
			Far_Plane_Distance);
	}

	void camera_Coordinates_System_update()
	{
		camera__Right.x = m_matView._11;	camera_up.x = m_matView._12;	  camera_look.x = m_matView._13;
		camera__Right.y = m_matView._21;	camera_up.y = m_matView._22;	  camera_look.y = m_matView._23;
		camera__Right.z = m_matView._31;	camera_up.z = m_matView._32;	  camera_look.z = m_matView._33;
	}

};