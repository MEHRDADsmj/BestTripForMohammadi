#include "MissionCity.h"

MissionCity::MissionCity() : City(), ProjectDuration(0.0f), Profit(0.0f), DeadLine(0)
{}

MissionCity::MissionCity(std::string CityName, bool bAirport, bool bRailOrWharf, bool bRoad, float ProjectTime, float Income, int MaxTime)
	: City(CityName, bAirport, bRailOrWharf, bRoad), ProjectDuration(ProjectTime), Profit(Income), DeadLine(MaxTime)
{}

float MissionCity::GetProfit() const
{
	return Profit;
}

float MissionCity::GetDuration() const
{
	return ProjectDuration;
}

int MissionCity::GetDeadline() const
{
	return DeadLine;
}
