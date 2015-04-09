#pragma once 

#include <typeinfo>
#include <unordered_map>
#include "System.h"

class SystemManager
{
public:
	SystemManager(){}
	~SystemManager(){}

	/**
	Adds a system to the SystemManager
	*/
	void addSystem(System* system);

	/**
	Returns system of given type if found.
	Otherwise returns nullptr.
	*/
	template<typename T>
	T* getSystem();

	/**
	Removes system of given type.
	*/
	template<typename T>
	void removeSystem();

private:
	std::unordered_map < const std::type_info*, System* > _systems;
};


template<typename T>
T* SystemManager::getSystem()
{
	std::unordered_map < const std::type_info*, System* >::iterator it;
	const std::type_info* type = &typeid(T);

	it = _systems.find(type);
	if (it != _systems.end())
	{
		return dynamic_cast<T*>(it->second);
	}
	return nullptr;
}


template<typename T>
void SystemManager::removeSystem()
{
	std::unordered_map < const std::type_info*, System* >::iterator it;
	const std::type_info* type = &typeid(T);

	it = _systems.find(type);
	if (it != _systems.end())
	{
		delete it->second;
		it = _systems.erase(it);
	}
}