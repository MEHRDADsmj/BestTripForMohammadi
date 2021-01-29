#include "City.h"

City::City() : Name("NullCity"), bHasAirport(false), bHasRailOrWharf(false), bHasRoad(false)
{}

City::City(std::string CityName, bool bAirport, bool bRailOrWharf, bool bRoad) : Name(CityName), bHasAirport(bAirport), bHasRailOrWharf(bRailOrWharf), bHasRoad(bRoad)
{}

void City::AddNearbyCity(City& NearbyCity, const int Distance)
{
	NearbyCities.push_back(NearbyCity);
	DistanceFromThisCity.push_back(Distance);
}

std::string City::GetName() const
{
	return Name;
}
