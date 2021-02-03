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

City* City::GetNearbyCity(unsigned int Index)
{
	return NearbyCities[Index];
}

std::vector<City*> City::GetNearbyCities() const
{
	return NearbyCities;
}

int City::HasInNearbyCities(City& CityToCheck)
{
	for (unsigned int Num = 0; Num < NearbyCities.size(); Num++)
	{
		if (&CityToCheck == NearbyCities[Num])
		{
			return Num;
		}
	}

	return -1;
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

int City::GetDistanceFrom(unsigned int DestinationCityIndex, std::vector<City*> AllCities)
{
	if (DestinationCityIndex == ThisCityIndex)
	{
		return SoMuchKilometers;
	}
	if (HasInNearbyCities(*AllCities[DestinationCityIndex]) == -1)
	{
		return SoMuchKilometers;
	}
	return DistanceFromThisCity[HasInNearbyCities(*AllCities[DestinationCityIndex])];
}

int City::GetDistanceInNearbies(unsigned int DestinationCityIndex, std::vector<City*> AllCities)
{
	unsigned int Iterator = 0;
	for (; Iterator < DestinationCityIndex; Iterator++);
	return GetDistanceFrom(NearbyCities[Iterator]->GetIndex(), AllCities);
}

void City::SetIsVisited(bool IsVisited)
{
	bIsVisited = IsVisited;
}
