#pragma once
#include "Vector3.h"
#include "FPSCamera.h"
#include "GroundEntity.h"

class CPlayerInfo
{
protected:
	static CPlayerInfo *s_instance;
	CPlayerInfo(void);

public:
	static CPlayerInfo *GetInstance()
	{
		if (!s_instance)
			s_instance = new CPlayerInfo;
		return s_instance;
	}
	static bool DropInstance()
	{
		if (s_instance)
		{
			delete s_instance;
			s_instance = NULL;
			return true;
		}
		return false;
	}
	~CPlayerInfo(void);

	void Init(void);
	void Update(double dt);
	void Reset(void);

	void SetPos(const Vector3& pos);
	void SetTarget(const Vector3& target);
	void SetUp(const Vector3& up);

	Vector3 GetPos(void) const;
	Vector3 GetTarget(void) const;
	Vector3 GetUp(void) const;

	void SetBoundary(Vector3 max, Vector3 min);
	void SetTerrain(GroundEntity* m_pTerrain);


	// Jump Stuff
	bool isOnGround(void);
	bool isJumpUpwards(void);
	bool isFreeFall(void);
	void SetOnFreeFall(bool isOnFreeFall);
	void SetToJumpUpwards(bool isOnJumpUpwards);
	void StopVerticalMovement(void);

	void SetJumpSpeed(const double m_dJumpSpeed);
	void SetJumpAcceleration(const double m_dJumpAcceleration);
	void SetFallSpeed(const double m_dFallSpeed);
	void SetFallAcceleration(const double m_dFallAcceleration);

	double GetJumpSpeed(void) const;
	double GetJumpAcceleration(void) const;
	double GetFallSpeed(void) const;
	double GetFallAcceleration(void) const;
	GroundEntity* GetTerrain(void);

	void UpdateJumpUpwards(double dt);
	void UpdateFreeFall(double dt);

	// Constrain the position within the borders
	void Constrain(double dt);

	// Handling Camera
	void AttachCamera(FPSCamera* _cameraPtr);
	void DetachCamera(void);

private:
	Vector3 defaultPosition, defaultTarget, defaultUp;
	Vector3 position, target, up;
	Vector3 maxBoundary, minBoundary;
	GroundEntity* m_pTerrain;

	double camera_Speed;
	double player_Speed;
	double m_dAcceleration;

	bool m_bJumpUpwards;
	double m_dJumpSpeed;
	double m_dJumpAcceleration;

	double m_dFallSpeed;
	bool m_bFallDownwards;
	double m_dFallAcceleration;

	FPSCamera* attachedCamera;
};
