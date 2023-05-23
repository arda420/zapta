#pragma once

class Movement {
public:
	float  m_speed;
	float  m_ideal;
	float  m_ideal2;
	vec3_t m_mins;
	vec3_t m_maxs;
	vec3_t m_origin;
	vec3_t quickpeekstartpos;
	float  m_switch_value = 1.f;
	int    m_strafe_index;
	float  m_old_yaw;
	float  m_circle_yaw;
	bool   m_invert;
	bool   hasShot;
	vec3_t start_position = vec3_t(0.0f, 0.0f, 0.0f);
	bool fired_shot;

public:
	void JumpRelated();
	void Strafe();
	void DoPrespeed();
	bool GetClosestPlane(vec3_t& plane);
	bool WillCollide(float time, float step);
	void MoonWalk(CUserCmd* cmd);
	void FixMove(CUserCmd* cmd, const ang_t& old_angles);
	void gotoStart();
	void AutoPeek(CUserCmd* cmd, float wish_yaw);
	void AutoPeek();
	void QuickStop();
	void FakeWalk();
	void cripwalk();
	void RotateMovement(CUserCmd* pCmd, ang_t& angOldViewPoint);
	void ClampMovementSpeed(float speed);
};

extern Movement g_movement;