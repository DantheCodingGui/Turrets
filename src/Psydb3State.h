#pragma once
class Psydb3State
{
public:
	Psydb3State();
	~Psydb3State();
	virtual void SetupBackgroundBuffer() = 0;
	virtual bool ShouldAct() = 0;

};

