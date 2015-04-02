#pragma once

#include "Component.h"
#include <unordered_map>
#include <typeinfo>

class GameObject
{
public:
	GameObject(){}
	~GameObject(){}
	
	
	/**
		Adds component to the GameObject.
		*/
	void addComponent(Component* component);


	/**
		Returns component of given type if found.
		Otherwise returns nullptr.
		*/
	template<typename T>
	T* getComponent();


	/**
		Removes component of given type.
		*/
	template<typename T>
	void removeComponent();

private:

	std::unordered_map < const std::type_info*, Component* > _components;
	
};


void GameObject::addComponent(Component* component)
{
	_components.insert(std::make_pair(&typeid(*component), component));
}


template<typename T>
T* GameObject::getComponent()
{
	std::unordered_map < const std::type_info*, Component* >::iterator it;
	const std::type_info* type = &typeid(T);

	it = _components.find(type);
	if (it != _components.end())
	{
		return static_cast<T*>(it->second);
	}

	return nullptr;
}


template<typename T>
void GameObject::removeComponent()
{
	std::unordered_map < const std::type_info*, Component* >::iterator it;
	const std::type_info* type = &typeid(T);

	it = _components.find(type);
	if (it != _components.end())
	{
		delete it->second;
		it = _components.erase(it);
	}
}