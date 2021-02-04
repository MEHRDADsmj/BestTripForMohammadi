#pragma once
#include <iostream>
#include <vector>
#include <string>
#define SoBigNumber 60000000000.0f

class City
{
private:
	std::string Name;

protected:
	//Means of travel
	bool bIsVisited;
	//Connected Cities
	std::vector<City*> NearbyCities;
	//Distance of nearby city from this city
	std::vector<float> DistanceFromThisCity;

	int ThisCityIndex;

	static int CityIndex;

public:
	City();
	City(std::string CityName, bool bAirport, bool bRailOrWharf, bool bRoad);

	void AddNearbyCity(City& NearbyCity, const float Distance);
	City* GetNearbyCity(unsigned int Index);
	std::vector<City*> GetNearbyCities() const;
	int HasInNearbyCities(City& CityToCheck);
	int GetIndex() const;
	bool GetIsVisited() const;
	std::string GetName() const;
	float GetDistanceFrom(unsigned int DestinationCityIndex, std::vector<City*> AllCities = {});
	float GetDistanceInNearbies(unsigned int DestinationCityIndex, std::vector<City*> AllCities = {});
	void SetIsVisited(bool IsVisited);

	bool bHasAirport, bHasRailOrWharf, bHasRoad;

};

