#pragma once
#include <iostream>
#include <vector>
#include <string>

class City
{
private:
	std::string Name;

protected:
	//Means of travel
	bool bHasAirport, bHasRailOrWharf, bHasRoad, bIsVisited;
	//Connected Cities

	std::vector<City*> NearbyCities;
	//Distance of nearby city from this city
	std::vector<int> DistanceFromThisCity;

public:
	City();
	City(std::string CityName, bool bAirport, bool bRailOrWharf, bool bRoad);

	void AddNearbyCity(City& NearbyCity, const int Distance);
	bool GetIsVisited() const;
	std::string GetName() const;

};

