#pragma once
#include "templates.h"
#include <cmath>

class Psydb3RotationPosition
{
public:
	Psydb3RotationPosition() 
	: m_nextDirection(0)
	, m_targetDirection(0)
	, m_posIndex(0)
	, m_iTimeUntilRotate(0.0) {};

	~Psydb3RotationPosition() {};

	inline void SetupRotation(int iStartTime, int iEndTime, int iStartDirection, int iTargetDirection) {
		m_targetDirection = iTargetDirection;
		m_iTimeUntilRotate = (iEndTime - iStartTime) / 3;
		bool isClockwise;
		int i, j, k;
		for (i = iStartDirection, j = 0; i != iTargetDirection; ++i, ++j) {
			if (i > 7)
				i = 0;
		}
		if (j > 4)
			isClockwise = false;
		else
			isClockwise = true;
		for (i = 0, k = iStartDirection; i < 2; ++i) {
			if (isClockwise) {
				++k;
				if (k > 7)
					k = 0;
			}
			else {
				--k;
				if (k < 0)
					k = 7;
			}
			m_positions[i] = k;
		}
		m_nextDirection = m_positions[m_posIndex];
	}
	inline int Update(int iCurrentTime, int iCurrentDirection) {
		if (iCurrentTime == m_iTimeUntilRotate) {
			++m_posIndex;
			int currentDirection = m_nextDirection;
			m_nextDirection = m_positions[m_posIndex];
			return currentDirection;
		}
		else
			return iCurrentDirection;
	}
	inline void Reset() {
		m_posIndex = 0;
	};
private:
	int m_nextDirection;
	int m_targetDirection;
	double m_iTimeUntilRotate;
	int m_positions[2];
	int m_posIndex;
};

