#include "City.h"

int City::CityIndex = 0;

City::City() : Name("NullCity"), bHasAirport(false), bHasRailOrWharf(false), bHasRoad(false), bIsVisited(false), ThisCityIndex(-1)
{}

City::City(std::string CityName, bool bAirport, bool bRailOrWharf, bool bRoad) : Name(CityName), bHasAirport(bAirport), bHasRailOrWharf(bRailOrWharf),
bHasRoad(bRoad), bIsVisited(false), ThisCityIndex(CityIndex)
{
	CityIndex++;
}

void City::AddNearbyCity(City& NearbyCity, const int Distance)
{
	NearbyCities.push_back(&NearbyCity);
	DistanceFromThisCity.push_back(Distance);
}

City* City::GetNeabyCity(unsigned int Index)
{
	return NearbyCities[Index];
}

std::vector<City*> City::GetNearbyCities() const
{
	return NearbyCities;
}

bool City::HasInNearbyCities(City& CityToCheck)
{
	for (unsigned int Num = 0; Num < NearbyCities.size(); Num++)
	{
		if (&CityToCheck == NearbyCities[Num])
		{
			return true;
		}
	}

	return false;
}

int City::GetIndex() const
{
	return ThisCityIndex;
}

bool City::GetIsVisited() const
{
	return bIsVisited;
}

std::string City::GetName() const
{
	return Name;
}

int City::GetDistanceFrom(unsigned int DestinationCityIndex)
{
	if (DestinationCityIndex == ThisCityIndex)
	{
		return 0;
	}
	if (DestinationCityIndex >= NearbyCities.size())
	{
		return 0;
	}
	return DistanceFromThisCity[DestinationCityIndex];
}
