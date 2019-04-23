#include "stdafx.h"
#include "Star.h"


CStar::CStar()
	:m_bCreate_Action(true), m_fCreate_Y(0.f), m_bBlock_Coll(false)
{
}


CStar::~CStar()
{
}

void CStar::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 40.f;
	m_fSpeed = 5.f;
	m_bIsJumping = true;
	m_tInfo.fX = 350.f;///일단 임의NUM ->블럭 위치
	m_tInfo.fY = 400.f;///일단 임의NUM ->블럭 위치

	m_fCreate_Y = m_tInfo.fY;
}

int CStar::Update()
{
	if (m_bIsDead)
	{
		//죽었을때 
		m_Vel_Y = 0.f;
		return OBJ_DEAD;
	}

	///생성 액션 체크
	if (m_bIsJumping && m_bCreate_Action && !m_bBlock_Coll)
	{
		m_tInfo.fY -= (m_fSpeed - 3.f);
		if (m_tInfo.fY <= m_fCreate_Y - ITEM_MOVE_SIZE)
		{
			m_bCreate_Action = false;
		}
	}
	if (m_bIsJumping && !m_bCreate_Action && !m_bBlock_Coll)
	{
		m_tInfo.fX += m_fSpeed;
	}
	///////////////////////////////////////////////////////////
	//자유낙하
	if (m_bIsJumping && !m_bCreate_Action && !m_bBlock_Coll)
	{
		m_Vel_Y += 0.4f;
		m_tInfo.fY += m_Vel_Y;
		if (m_tInfo.fX >= 425.f)
		{
			m_bIsJumping = false;
		}
	}
	//블럭충돌 체크
	if (!m_bCreate_Action && !m_bIsJumping && !m_bBlock_Coll)
	{
		m_tInfo.fX += m_fSpeed;
		if (m_tInfo.fX >= WINCX)///임시
		{
			m_bBlock_Coll = true;
		}
	}
	if (!m_bCreate_Action && !m_bIsJumping && m_bBlock_Coll)
	{
		m_tInfo.fX -= m_fSpeed;
	}
	////////////////////////////////////////

	return OBJ_ALIVE;
}

void CStar::LateUpdate()
{
}

void CStar::Render(HDC hDC)
{
	CObj::UpdateRect();

	HBRUSH myBrush = NULL;
	HBRUSH oldBrush;
	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void CStar::Release()
{
}
