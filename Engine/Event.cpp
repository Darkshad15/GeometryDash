#include "Event.h"


std::map<int, int> Event::lstId;
std::map<int, event> Event::lstEvent;

void Event::CreateEvent(int id, event evt) //Creer un event pour le jeu 
{
	if (id < 0)
		lstId[id] = 1;
	else
		lstId[id] = 0;
	lstEvent[id] = evt;

}

void Event::ProcessEvent() //test la condition pour le lancement d'event
{
	for (auto& [id, test] : lstId)
	{
		if (test == 1)
		{
			if(id>0)
				lstId[id] = -1;
			lstEvent[id]();
		}
	}
}

void Event::SetEventTrue(int id) // met un event a true
{
	if (lstId[id] == 0)
		lstId[id] = 1;
}

void Event::ClearAllEvents()
{
	lstId.clear();
	lstEvent.clear();
	std::cout << "Tous les events ont ete nettoyes" << std::endl;
}