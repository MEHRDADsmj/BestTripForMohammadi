#include <iostream>
#include "City.h"
#include "MissionCity.h"
#include <array>
#define CityCount 32

#pragma region Declarations

float TimeSpent = 0.0f;

float CurrentProfit = 0.0f;

enum MeanOfTravel {
	Car,
	TrainOrShip,
	Airplane
};

void Dijkstra(std::array<int, CityCount>& Distance, std::array<City*, CityCount>& ParentCities, std::vector<City*> AllCities, int StartCityIndex, std::array<std::array<int, CityCount>, CityCount> Graph);

int GetMin(std::array<int, CityCount> Distance, int& MinDistance, std::array<bool, CityCount> IsProcessed = { false });

City* GetParent(City& CityToProcess, std::array<City*, CityCount>& Parents);

void PrintDijkstra(std::array<City*, CityCount>& Parents, std::vector<City*> AllCities);

void ApplyMultipliers(std::array<std::array<int, CityCount>, CityCount> Graph, std::array<std::array<MeanOfTravel, CityCount>, CityCount>& TripVehicle);

int GetNextCity(std::array<int, CityCount> Distance, std::vector<City*> AllCities, std::vector<MissionCity*> MissionCities);

void DoMission(MissionCity& DoneCity);

MissionCity* GetMissionCityByIndex(int Index, std::vector<MissionCity*> MissionCities);

#pragma endregion Declarations

int main()
{
	//Initializes cities and their relations
#pragma region Initialization

	City LosAngeles("Los Angeles", true, false, true); //Check
	City Montreal("Montreal", false, true, true); //Check
	City NewYork("New York", true, false, true); //Check
	City SanJuan("San Juan", true, true, false); //Check
	City Caracus("Caracus", true, false, true); //Check
	City Santiago("Santiago", false, true, true); //Check
	City Rio("Rio De Janeiro", true, false, true); //Check
	City Casablanca("Casablanca", false, true, true); //Check
	City Accra("Accra", true, false, true); //Check
	City Nairobi("Nairobi", true, false, true); //Check
	City Khartoum("Khartoum", false, false, true); //Check
	City Cairo("Cairo", true, false, true); //Check
	City London("London", true, true, true); //Check
	City Istanbul("Istanbul", true, true, true); //Check
	City Moskva("Moskva", false, true, true); //Check
	City Dubai("Dubai", true, true, true); //Check
	City Khuree("Khuree", false, false, true); //Check
	City Katmandu("Katmandu", false, false, true); //Check
	City Madras("Madras", false, true, true); //Check
	City HongKong("HongKong", true, false, true); //Check
	City Singapore("Singapore", true, false, true); //Check
	City Batavia("Batavia", false, true, true); //Check
	MissionCity Dakar("Dakar", true, true, true, 0.5f, 5.0f, 19); //Check
	MissionCity Sydney("Sydney", true, true, true, 2.0f, 6.8f, 10); //Check
	MissionCity Anchorage("Anchorage", true, true, true, 1.0f, 4.5f, 21); //Check
	MissionCity Tokyo("Tokyo", false, true, false, 2.5f, 6.3f, 27); //Check
	MissionCity Reykjavik("Reykjavik", true, false, false, 3.0f, 3.4f, 21); //Check
	MissionCity CapeTown("Cape Town", false, true, true, 3.5f, 5.6f, 21); //Check
	MissionCity Tehran("Tehran", true, true, true, 1.5f, 2.0f, 15); //Check
	MissionCity BuenosAires("Buenos Aires", false, false, true, 4.5f, 8.0f, 21); //Check
	MissionCity Panama("Panama", true, true, true, 2.5f, 4.7f, 13); //Check
	MissionCity Vladivostok("Vladivostok", true, true, true, 2.0f, 6.1f, 28); //Check

	LosAngeles.AddNearbyCity(NewYork, 2700);
	LosAngeles.AddNearbyCity(SanJuan, 2200);
	LosAngeles.AddNearbyCity(Montreal, 2800);
	LosAngeles.AddNearbyCity(Anchorage, 1500);
	LosAngeles.AddNearbyCity(Panama, 3000);

	Montreal.AddNearbyCity(Anchorage, 2400);
	Montreal.AddNearbyCity(NewYork, 800);
	Montreal.AddNearbyCity(LosAngeles, 2800);
	Montreal.AddNearbyCity(Reykjavik, 2400);

	NewYork.AddNearbyCity(Montreal, 800);
	NewYork.AddNearbyCity(LosAngeles, 2700);
	NewYork.AddNearbyCity(SanJuan, 1500);

	SanJuan.AddNearbyCity(LosAngeles, 2200);
	SanJuan.AddNearbyCity(NewYork, 1500);
	SanJuan.AddNearbyCity(Panama, 1100);
	SanJuan.AddNearbyCity(Caracus, 1600);
	SanJuan.AddNearbyCity(Dakar, 3800);
	SanJuan.AddNearbyCity(Casablanca, 3200);

	Caracus.AddNearbyCity(SanJuan, 1600);
	Caracus.AddNearbyCity(Panama, 1300);
	Caracus.AddNearbyCity(Rio, 2400);

	Santiago.AddNearbyCity(Rio, 2550);
	Santiago.AddNearbyCity(BuenosAires, 800);
	Santiago.AddNearbyCity(Panama, 4750);
	Santiago.AddNearbyCity(Sydney, 3600);

	Rio.AddNearbyCity(Santiago, 2550);
	Rio.AddNearbyCity(Panama, 3200);
	Rio.AddNearbyCity(BuenosAires, 1600);
	Rio.AddNearbyCity(Caracus, 2400);
	Rio.AddNearbyCity(CapeTown, 3300);
	Rio.AddNearbyCity(Dakar, 2400);

	Casablanca.AddNearbyCity(SanJuan, 3200);
	Casablanca.AddNearbyCity(Dakar, 1600);
	Casablanca.AddNearbyCity(Reykjavik, 4500);
	Casablanca.AddNearbyCity(London, 1950);
	Casablanca.AddNearbyCity(Accra, 2550);
	Casablanca.AddNearbyCity(Cairo, 2250);

	Accra.AddNearbyCity(Casablanca, 2550);
	Accra.AddNearbyCity(Dakar, 800);
	Accra.AddNearbyCity(Cairo, 2200);
	Accra.AddNearbyCity(Nairobi, 2400);
	Accra.AddNearbyCity(CapeTown, 3500);

	Nairobi.AddNearbyCity(Accra, 2400);
	Nairobi.AddNearbyCity(Khartoum, 1400);
	Nairobi.AddNearbyCity(Dubai, 3000);
	Nairobi.AddNearbyCity(Batavia, 3900);
	Nairobi.AddNearbyCity(CapeTown, 3400);

	Khartoum.AddNearbyCity(Nairobi, 1400);
	Khartoum.AddNearbyCity(Dubai, 1100);
	Khartoum.AddNearbyCity(Cairo, 1800);

	Cairo.AddNearbyCity(Casablanca, 2250);
	Cairo.AddNearbyCity(Accra, 2200);
	Cairo.AddNearbyCity(Dubai, 1200);
	Cairo.AddNearbyCity(Khartoum, 1800);
	Cairo.AddNearbyCity(Istanbul, 800);

	London.AddNearbyCity(Reykjavik, 1600);
	London.AddNearbyCity(Casablanca, 1950);
	London.AddNearbyCity(Istanbul, 2400);
	London.AddNearbyCity(Moskva, 3800);

	Istanbul.AddNearbyCity(London, 2400);
	Istanbul.AddNearbyCity(Cairo, 800);
	Istanbul.AddNearbyCity(Tehran, 1700);
	Istanbul.AddNearbyCity(Moskva, 1100);

	Moskva.AddNearbyCity(London, 3800);
	Moskva.AddNearbyCity(Istanbul, 1100);
	Moskva.AddNearbyCity(Khuree, 3750);
	Moskva.AddNearbyCity(Tehran, 1800);
	Moskva.AddNearbyCity(Vladivostok, 6400);

	Dubai.AddNearbyCity(Tehran, 800);
	Dubai.AddNearbyCity(Khartoum, 1100);
	Dubai.AddNearbyCity(Nairobi, 3000);
	Dubai.AddNearbyCity(Cairo, 1200);
	Dubai.AddNearbyCity(Madras, 2100);

	Khuree.AddNearbyCity(Moskva, 3750);
	Khuree.AddNearbyCity(Tehran, 3200);
	Khuree.AddNearbyCity(Katmandu, 2400);
	Khuree.AddNearbyCity(Vladivostok, 1400);
	Khuree.AddNearbyCity(HongKong, 2400);

	Katmandu.AddNearbyCity(Khuree, 2400);
	Katmandu.AddNearbyCity(Tehran, 1300);
	Katmandu.AddNearbyCity(Madras, 1100);
	Katmandu.AddNearbyCity(Singapore, 3600);

	Madras.AddNearbyCity(Dubai, 2100);
	Madras.AddNearbyCity(Katmandu, 1100);
	Madras.AddNearbyCity(Singapore, 2400);

	HongKong.AddNearbyCity(Khuree, 2400);
	HongKong.AddNearbyCity(Singapore, 2850);
	HongKong.AddNearbyCity(Tokyo, 1600);
	HongKong.AddNearbyCity(Vladivostok, 2400);

	Singapore.AddNearbyCity(HongKong, 2850);
	Singapore.AddNearbyCity(Madras, 2400);
	Singapore.AddNearbyCity(Batavia, 800);
	Singapore.AddNearbyCity(Katmandu, 3600);
	Singapore.AddNearbyCity(Tokyo, 4250);
	Singapore.AddNearbyCity(Sydney, 2800);

	Batavia.AddNearbyCity(Singapore, 800);
	Batavia.AddNearbyCity(Nairobi, 3900);
	Batavia.AddNearbyCity(CapeTown, 6400);
	Batavia.AddNearbyCity(Sydney, 1600);

	Dakar.AddNearbyCity(Rio, 2400);
	Dakar.AddNearbyCity(Accra, 800);
	Dakar.AddNearbyCity(Casablanca, 1600);
	Dakar.AddNearbyCity(SanJuan, 3800);

	Sydney.AddNearbyCity(Batavia, 1600);
	Sydney.AddNearbyCity(Singapore, 2800);
	Sydney.AddNearbyCity(Panama, 4500);
	Sydney.AddNearbyCity(Santiago, 3600);

	Anchorage.AddNearbyCity(Montreal, 2400);
	Anchorage.AddNearbyCity(LosAngeles, 1500);
	Anchorage.AddNearbyCity(Reykjavik, 5100);
	Anchorage.AddNearbyCity(Vladivostok, 2750);

	Tokyo.AddNearbyCity(Panama, 3500);
	Tokyo.AddNearbyCity(Vladivostok, 1200);
	Tokyo.AddNearbyCity(HongKong, 1600);
	Tokyo.AddNearbyCity(Singapore, 4250);

	Reykjavik.AddNearbyCity(Anchorage, 5100);
	Reykjavik.AddNearbyCity(London, 1600);
	Reykjavik.AddNearbyCity(Montreal, 2400);
	Reykjavik.AddNearbyCity(Casablanca, 4500);

	CapeTown.AddNearbyCity(Rio, 3300);
	CapeTown.AddNearbyCity(Accra, 3500);
	CapeTown.AddNearbyCity(Nairobi, 3400);
	CapeTown.AddNearbyCity(Batavia, 6400);

	Tehran.AddNearbyCity(Istanbul, 1700);
	Tehran.AddNearbyCity(Dubai, 800);
	Tehran.AddNearbyCity(Katmandu, 1300);
	Tehran.AddNearbyCity(Khuree, 3200);
	Tehran.AddNearbyCity(Moskva, 1800);

	BuenosAires.AddNearbyCity(Santiago, 800);
	BuenosAires.AddNearbyCity(Rio, 1600);

	Panama.AddNearbyCity(Tokyo, 3500);
	Panama.AddNearbyCity(Caracus, 1300);
	Panama.AddNearbyCity(SanJuan, 1100);
	Panama.AddNearbyCity(Santiago, 4750);
	Panama.AddNearbyCity(Rio, 3200);
	Panama.AddNearbyCity(LosAngeles, 3000);
	Panama.AddNearbyCity(Sydney, 4500);

	Vladivostok.AddNearbyCity(Moskva, 6400);
	Vladivostok.AddNearbyCity(Khuree, 1400);
	Vladivostok.AddNearbyCity(HongKong, 2400);
	Vladivostok.AddNearbyCity(Tokyo, 1200);
	Vladivostok.AddNearbyCity(Anchorage, 2750);

	std::vector<City*> AllCities;
	AllCities.push_back(&LosAngeles); //0
	AllCities.push_back(&Montreal); //1
	AllCities.push_back(&NewYork); //2
	AllCities.push_back(&SanJuan); //3
	AllCities.push_back(&Caracus); //4
	AllCities.push_back(&Santiago); //5
	AllCities.push_back(&Rio); //6
	AllCities.push_back(&Casablanca); //7
	AllCities.push_back(&Accra); //8
	AllCities.push_back(&Nairobi); //9
	AllCities.push_back(&Khartoum); //10
	AllCities.push_back(&Cairo); //11
	AllCities.push_back(&London); //12
	AllCities.push_back(&Istanbul); //13
	AllCities.push_back(&Moskva); //14
	AllCities.push_back(&Dubai); //15
	AllCities.push_back(&Khuree); //16
	AllCities.push_back(&Katmandu); //17
	AllCities.push_back(&Madras); //18
	AllCities.push_back(&HongKong); //19
	AllCities.push_back(&Singapore); //20
	AllCities.push_back(&Batavia); //21
	AllCities.push_back(&Dakar); //22
	AllCities.push_back(&Sydney); //23
	AllCities.push_back(&Anchorage); //24
	AllCities.push_back(&Tokyo); //25
	AllCities.push_back(&Reykjavik); //26
	AllCities.push_back(&CapeTown); //27
	AllCities.push_back(&Tehran); //28
	AllCities.push_back(&BuenosAires); //29
	AllCities.push_back(&Panama); //30
	AllCities.push_back(&Vladivostok); //31

	std::vector<MissionCity*> MissionCities;
	MissionCities.push_back(&Dakar); //0
	MissionCities.push_back(&Sydney); //1
	MissionCities.push_back(&Anchorage); //2
	MissionCities.push_back(&Tokyo); //3
	MissionCities.push_back(&Reykjavik); //4
	MissionCities.push_back(&CapeTown); //5
	MissionCities.push_back(&Tehran); //6
	MissionCities.push_back(&BuenosAires); //7
	MissionCities.push_back(&Panama); //8
	MissionCities.push_back(&Vladivostok); //9


#pragma endregion Initialization

#pragma region Arrays Initialization

	//Init distance graph
	std::array<std::array<int, CityCount>, CityCount> Graph = { 0 };

	for (int Row = 0; Row < CityCount; Row++)
	{
		for (int Col = 0; Col < CityCount; Col++)
		{
			Graph[Row][Col] = AllCities[Row]->GetDistanceFrom(Col, AllCities);
		}
	}

	std::array<std::array<MeanOfTravel, CityCount>, CityCount> TripVehicle = { MeanOfTravel::Car };

	std::array<int, CityCount> Distance;
	Distance.fill(SoMuchKilometers);

	std::array<City*, CityCount> ParentCities;
	ParentCities.fill(nullptr);

#pragma endregion Arrays Initialization
	
	int CurrentCityIndex = Tehran.GetIndex();

	for (; CurrentCityIndex != -1;)
	{
		Dijkstra(Distance, ParentCities, AllCities, CurrentCityIndex, Graph);
		MissionCity* Temp = GetMissionCityByIndex(CurrentCityIndex, MissionCities);
		DoMission(*Temp);
		std::cout << CurrentCityIndex << std::endl;
		CurrentCityIndex = GetNextCity(Distance, AllCities, MissionCities);
	}

	system("pause");
	return 0;
}

#pragma region Implementations

void Dijkstra(std::array<int, CityCount>& Distance, std::array<City*, CityCount>& ParentCities, std::vector<City*> AllCities, int StartCityIndex, std::array<std::array<int, CityCount>, CityCount> Graph)
{
	Distance.fill(SoMuchKilometers);
	ParentCities.fill(nullptr);
	std::array<bool, CityCount> IsProcessed;
	IsProcessed.fill(false);

	int NextNodeIndex, CountsAlgoDone, MinDistance;

	for (int Iterator = 0; Iterator < CityCount; Iterator++)
	{
		Distance[Iterator] = Graph[StartCityIndex][Iterator];
	}
	Distance[StartCityIndex] = 0;
	IsProcessed[StartCityIndex] = true;
	CountsAlgoDone = 1;
	while (CountsAlgoDone < CityCount - 1)
	{
		NextNodeIndex = GetMin(Distance, MinDistance, IsProcessed);
		IsProcessed[NextNodeIndex] = true;
		for (int Iterator = 0; Iterator < CityCount; Iterator++)
		{
			if (!IsProcessed[Iterator])
			{
				if (MinDistance + Graph[NextNodeIndex][Iterator] < Distance[Iterator])
				{
					Distance[Iterator] = MinDistance + Graph[NextNodeIndex][Iterator];
					ParentCities[Iterator] = AllCities[NextNodeIndex];
				}
			}
		}
		CountsAlgoDone++;
	}
}

int GetMin(std::array<int, CityCount> Distance, int& MinDistance, std::array<bool, CityCount> IsProcessed)
{
	MinDistance = SoMuchKilometers;
	int MinIndex = -1;
	for (int Iterator = 0; Iterator < CityCount; Iterator++)
	{
		if (!IsProcessed[Iterator] && Distance[Iterator] < MinDistance)
		{
			MinDistance = Distance[Iterator];
			MinIndex = Iterator;
		}
	}
	return MinIndex;
}

City* GetParent(City& CityToProcess, std::array<City*, CityCount>& Parents)
{
	return Parents[CityToProcess.GetIndex()];
}

void PrintDijkstra(std::array<City*, CityCount>& Parents, std::vector<City*> AllCities)
{
	for (int i = 0; i < CityCount; i++)
	{
		std::cout << AllCities[i]->GetName() << " : ";
		for (City* Parent = GetParent(*AllCities[i], Parents); Parent != nullptr; Parent = GetParent(*Parent, Parents))
		{
			std::cout << Parent->GetName() << " <- ";
		}
		std::cout << std::endl;
	}
}

void ApplyMultipliers(std::array<std::array<int, CityCount>, CityCount>& Graph, std::array<std::array<MeanOfTravel, CityCount>, CityCount>& TripVehicle)
{

}

int GetNextCity(std::array<int, CityCount> Distance, std::vector<City*> AllCities, std::vector<MissionCity*> MissionCities)
{
	int MinDistance = SoMuchKilometers;
	int MinIndex = -1;
	for (auto CurrentCity : MissionCities)
	{
		if (!CurrentCity->GetIsVisited() && Distance[CurrentCity->GetIndex()] < MinDistance)
		{
			MinDistance = Distance[CurrentCity->GetIndex()];
			MinIndex = CurrentCity->GetIndex();
		}
	}
	return MinIndex;
}

void DoMission(MissionCity& DoneCity)
{
	if (TimeSpent <= DoneCity.GetDeadline())
	{
		CurrentProfit += DoneCity.GetProfit();
	}
	else
	{
		CurrentProfit += (DoneCity.GetProfit() * ((TimeSpent - DoneCity.GetDeadline() * 0.4f)));
	}
	TimeSpent += DoneCity.GetDuration();
	DoneCity.SetIsVisited(true);
}

MissionCity* GetMissionCityByIndex(int Index, std::vector<MissionCity*> MissionCities)
{
	for (auto CurrentCity : MissionCities)
	{
		if (Index == CurrentCity->GetIndex())
		{
			return CurrentCity;
		}
	}
	return nullptr;
}

#pragma endregion Implementations
