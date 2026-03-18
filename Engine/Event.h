#pragma once
#include "Engine.h"
#include <functional>
#include <map>

using event = std::function<void()>;

class Event
{
private:
	static std::map<int, int> lstId;
	static std::map<int, event> lstEvent;



public:
	static void ClearAllEvents();
	static void CreateEvent(int id, event evt);
	static void ProcessEvent();
	static void SetEventTrue(int id);



};

