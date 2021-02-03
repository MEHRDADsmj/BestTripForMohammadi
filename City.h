#pragma once
#include <iostream>
#include <vector>
#include <string>
#define SoMuchKilometers 60000

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

	int ThisCityIndex;

	static int CityIndex;

public:
	City();
	City(std::string CityName, bool bAirport, bool bRailOrWharf, bool bRoad);

	void AddNearbyCity(City& NearbyCity, const int Distance);
	City* GetNearbyCity(unsigned int Index);
	std::vector<City*> GetNearbyCities() const;
	int HasInNearbyCities(City& CityToCheck);
	int GetIndex() const;
	bool GetIsVisited() const;
	std::string GetName() const;
	float GetDistanceFrom(unsigned int DestinationCityIndex, std::vector<City*> AllCities = {});
	float GetDistanceInNearbies(unsigned int DestinationCityIndex, std::vector<City*> AllCities = {});
	void SetIsVisited(bool IsVisited);

};

