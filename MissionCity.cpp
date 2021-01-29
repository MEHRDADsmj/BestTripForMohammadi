#include "MissionCity.h"

MissionCity::MissionCity() : City("NullCity", false, false, false), ProjectDuration(0.0f), Profit(0.0f)
{}

MissionCity::MissionCity(std::string CityName, bool bAirport, bool bRailOrWharf, bool bRoad, float ProjectTime, float Income)
	: City(CityName, bAirport, bRailOrWharf, bRoad), ProjectDuration(ProjectTime), Profit(Income)
{}
