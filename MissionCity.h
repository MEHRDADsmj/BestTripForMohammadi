#pragma once
#include "City.h"

class MissionCity : public City
{
private:
	//Project duration in days
	float ProjectDuration;
	//Project profit in million tomans
	float Profit;

public:
	MissionCity();
	MissionCity(std::string CityName, bool bAirport, bool bRailOrWharf, bool bRoad, float ProjectTime, float Income);

};

