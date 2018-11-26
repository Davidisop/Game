#include "Plane.h"
#include "Box.h"
#include "Line.h"



int end_decision;

enum TSceneState
{
	GAME_SCENE_LOBBY = 0,
	GAME_SCENE_PLAY = 1,
	GAME_SCENE_END = 2,
};

class TScene
{
public:
	int		m_iSceneID;
	bool	m_bNextSceneStart;

public:
	virtual bool	Init() { return true; }
	virtual bool	Frame() { return true; }
	virtual bool	Render() { return true; }
	virtual bool	Release() { return true; }

public:
	TScene()
	{
		m_bNextSceneStart = false;
	}
	virtual ~TScene() {}
};



class TSceneLobby : public TScene
{
public:
	
	Box			FBOX;
	Plane		FPLANE;

	Line_Axis_s F_Axis_x;
	Line_Axis_s F_Axis_y;
	Line_Axis_s F_Axis_z;

public:
	virtual bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	TSceneLobby();
	virtual ~TSceneLobby();
};

bool	TSceneLobby::Init()
{
	
	FBOX.Set_VertexData();
	FBOX.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/David.jpg");
	FBOX.Basic_Camera.Set_View_Matrix();
	FBOX.Basic_Camera.Set_Projection_Matrix(0.5, 1, 1, 100);
	FBOX.world_setted_and_camera_apply_to_constant_buffer();




	
	FPLANE.Set_VertexData();
	FPLANE.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/David.jpg");
	FPLANE.Basic_Camera.Set_View_Matrix();
	FPLANE.Basic_Camera.Set_Projection_Matrix(0.5, 1, 1, 100);
	//FPLANE.transposition(D3DXVECTOR3(0.0f,0.0f,-1.0f));
	FPLANE.world_setted_and_camera_apply_to_constant_buffer();



	F_Axis_x.Set_VertexData(D3DXVECTOR3(1000.0f,0.0f,0.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
	F_Axis_x.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/David.jpg","PSLine");
	F_Axis_x.Basic_Camera.Set_View_Matrix();
	F_Axis_x.Basic_Camera.Set_Projection_Matrix(0.5, 1, 1, 100);
	F_Axis_x.world_setted_and_camera_apply_to_constant_buffer();

	F_Axis_y.Set_VertexData(D3DXVECTOR3(0.0f, 1000.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
	F_Axis_y.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/David.jpg", "PSLine");
	F_Axis_y.Basic_Camera.Set_View_Matrix();
	F_Axis_y.Basic_Camera.Set_Projection_Matrix(0.5, 1, 1, 100);
	F_Axis_y.world_setted_and_camera_apply_to_constant_buffer();

	F_Axis_z.Set_VertexData(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));
	F_Axis_z.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../data/David.jpg", "PSLine");
	F_Axis_z.Basic_Camera.Set_View_Matrix();
	F_Axis_z.Basic_Camera.Set_Projection_Matrix(0.5, 1, 1, 100);
	F_Axis_z.world_setted_and_camera_apply_to_constant_buffer();


	return true;
};

 
bool	TSceneLobby::Frame()
{
	float t = g_fGameTimer * D3DX_PI;


	D3DXMATRIX mTranslate;
	D3DXMATRIX mOrbit;
	D3DXMATRIX mSpin;
	D3DXMATRIX mScale;
	
	D3DXMatrixScaling(&mScale, 5.0f, 5.0f, 5.0f);// 스케일 행렬
	D3DXMatrixRotationZ(&mSpin, t);// Z축 자전회전행렬
	D3DXMatrixTranslation(&mTranslate, 0.0f, 0.0f, 10.0f); // 트랜스래잇 행렬
	D3DXMatrixRotationY(&mOrbit, t);  // Y축 공전회전행렬    

	FPLANE.m_matWorld = mScale * mSpin *mTranslate *mOrbit;
	D3DXMatrixTranspose(&FPLANE.m_Constant_Data.matWorld, &FPLANE.m_matWorld);
	FPLANE.update_ConstantBuffer();


	//
	//FPLANE.update_ConstantBuffer();
	FBOX.update_ConstantBuffer();
	F_Axis_x.update_ConstantBuffer();
	F_Axis_y.update_ConstantBuffer();
	F_Axis_z.update_ConstantBuffer();

	return true;
};


bool	TSceneLobby::Render()
{

	F_Axis_x.PreRender(g_pContext);
	F_Axis_x.PostRender(g_pContext);
	F_Axis_y.PreRender(g_pContext);
	F_Axis_y.PostRender(g_pContext);
	F_Axis_z.PreRender(g_pContext);
	F_Axis_z.PostRender(g_pContext);
	
	//FBOX.Render(g_pContext);
	FPLANE.Render(g_pContext);
	
	

	return true;
};

bool	TSceneLobby::Release()
{
	
	
	return true;
};
TSceneLobby::TSceneLobby()
{
	m_iSceneID = GAME_SCENE_LOBBY;
	m_bNextSceneStart = false;
}
TSceneLobby::~TSceneLobby()
{

}

















class TSceneGame : public TScene
{
public:
	virtual bool    Init();
	bool    Frame();
	bool    Render();
	bool    Release();

public:

	TSceneGame();
	virtual ~TSceneGame();
};



TSceneGame::TSceneGame()
{
	m_iSceneID = GAME_SCENE_PLAY;
	m_bNextSceneStart = false;
}

bool   TSceneGame::Init()
{

	return true;
};

bool    TSceneGame::Frame()
{

	return true;
}

bool   TSceneGame::Render()
{

	return true;
}

bool    TSceneGame::Release()
{
	return true;
}

TSceneGame::~TSceneGame()
{
}



class TSceneEnd : public TScene
{

public:

public:
	virtual bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:

	TSceneEnd();
	virtual ~TSceneEnd();
};




bool	TSceneEnd::Init()
{



	return true;
};
bool	TSceneEnd::Frame()
{


	return true;
};

bool	TSceneEnd::Render()
{

	return true;
};

bool	TSceneEnd::Release()
{
	return true;
};

TSceneEnd::TSceneEnd()
{
	m_iSceneID = GAME_SCENE_END;
	m_bNextSceneStart = false;
}

TSceneEnd::~TSceneEnd()
{}

