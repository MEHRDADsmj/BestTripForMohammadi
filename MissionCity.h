#pragma once
#include "City.h"

class MissionCity : public City
{
private:
	//Project duration in days
	float ProjectDuration;
	//Project profit in million tomans
	float Profit;

	float DeadLine;

	float Priority;

public:
	MissionCity();
	MissionCity(std::string CityName, bool bAirport, bool bRailOrWharf, bool bRoad, float ProjectTime, float Income, float MaxTime);

	float GetProfit() const;
	float GetDuration() const;
	float GetDeadline() const;
	float GetPriority() const;

};

