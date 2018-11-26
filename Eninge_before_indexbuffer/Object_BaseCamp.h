#include "PipeLineSetup.h"
#include "Canon_Camera.h"

class Object_BaseCamp
{
public:
	PipeLineSetup  PipeLineSetup;
	D3DVECTOR      m_vCenter;
public:
	vector<SimpleVertex> m_VertexList;
	UINT				 m_icount_Vertexs;
public:
	T_CB_DATA		m_Constant_Data;
public:
	D3DXMATRIX		m_matWorld;
	void			transposition(D3DXVECTOR3 position_move_in);
	void			transposition_real_time(D3DXVECTOR3 position_move_in);

public:
	Canon_Camera	Basic_Camera;
	void world_setted_and_camera_apply_to_constant_buffer();
	void camera_Coordinates_System_update();
public:
	virtual bool	Init() { return true;}
	virtual bool	Frame(float fGameTimer, float fFps)	{return true;}
	virtual bool	PreRender(ID3D11DeviceContext* pContext)	{ PipeLineSetup.PreRender(pContext);	return true;}
	virtual bool	Render(ID3D11DeviceContext* pContext) { PipeLineSetup.Render(pContext, m_icount_Vertexs); return true;}
	virtual bool	PostRender(ID3D11DeviceContext* pContext) { PipeLineSetup.PostRender(pContext, m_icount_Vertexs); return true;}
	virtual bool	Release() { return true;}
public:
	Object_BaseCamp() { D3DXMatrixIdentity(&m_matWorld); }
	virtual ~Object_BaseCamp() {}
};


void	Object_BaseCamp::transposition_real_time(D3DXVECTOR3 position_move_in)
{

	m_matWorld._41 += position_move_in.x*g_fSecPerFrame;
	m_matWorld._42 += position_move_in.y*g_fSecPerFrame;
	m_matWorld._43 += position_move_in.z*g_fSecPerFrame;

	D3DXMatrixTranspose(&m_Constant_Data.matWorld, &m_matWorld);

}

void Object_BaseCamp::transposition(D3DXVECTOR3 position_move_in)
{
	m_matWorld._41 = position_move_in.x;
	m_matWorld._42 = position_move_in.y;
	m_matWorld._43 = position_move_in.z;

}


void Object_BaseCamp::world_setted_and_camera_apply_to_constant_buffer()
{
	
	D3DXMatrixTranspose(&m_Constant_Data.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_Constant_Data.matView, &Basic_Camera.m_matView);
	D3DXMatrixTranspose(&m_Constant_Data.matProj, &Basic_Camera.m_matProj);
}

void Object_BaseCamp::camera_Coordinates_System_update()
{
	Basic_Camera.camera__Right.x = Basic_Camera.m_matView._11;	Basic_Camera.camera_up.x = Basic_Camera.m_matView._12;	  Basic_Camera.camera_up.x = Basic_Camera.m_matView._13;
	Basic_Camera.camera__Right.y = Basic_Camera.m_matView._21;	Basic_Camera.camera_up.y = Basic_Camera.m_matView._22;	  Basic_Camera.camera_up.y = Basic_Camera.m_matView._23;
	Basic_Camera.camera__Right.z = Basic_Camera.m_matView._31;	Basic_Camera.camera_up.z = Basic_Camera.m_matView._32;	  Basic_Camera.camera_up.z = Basic_Camera.m_matView._33;
}