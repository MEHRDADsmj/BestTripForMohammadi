#include "City.h"

City::City() : Name("NullCity"), bHasAirport(false), bHasRailOrWharf(false), bHasRoad(false), bIsVisited(false)
{}

City::City(std::string CityName, bool bAirport, bool bRailOrWharf, bool bRoad) : Name(CityName), bHasAirport(bAirport), bHasRailOrWharf(bRailOrWharf), bHasRoad(bRoad), bIsVisited(false)
{}

void City::AddNearbyCity(City& NearbyCity, const int Distance)
{
	NearbyCities.push_back(&NearbyCity);
	DistanceFromThisCity.push_back(Distance);
}

bool City::GetIsVisited() const
{
	return bIsVisited;
}

std::string City::GetName() const
{
	return Name;
}
