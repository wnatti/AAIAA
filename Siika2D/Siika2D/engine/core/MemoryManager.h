#pragma once
#include <memory>
#include <stdlib.h>
#include <typeinfo>
#include <string>
#include <iostream>
#include <map>;
#include <assert.h>
#include <memory.h>
#include <sstream>



namespace core
{

	/** MemoryManager class keeps count of references created from Object class
	
	*/
	class MemoryManager
	{
	public:
		static MemoryManager& getInstance()
		{
			static MemoryManager mm;
			return mm;
		}
		void addRef(void * ptr, const char* file, int line, size_t size)
		{
			new_ptr_list list;
			list.file = file;
			list.line = line;
			list.size = size;
			nRefs.insert(std::pair<void*, new_ptr_list>(ptr, list));
		}
		bool removeRef(void * ptr)
		{
			std::map<void *, new_ptr_list>::iterator it = nRefs.find(ptr);
			if(it != nRefs.end())
			{
				free(ptr);
				nRefs.erase(nRefs.find(ptr));
				
				return true;
			}
			return false;
		}

		void getCount()
		{
			unsigned long size = 0;
			char lineToWrite[255];
			std::string ptrStr;
			print("Memory Reserved at: \n");
			for(std::map<void *, new_ptr_list>::iterator it = nRefs.begin(); it != nRefs.end(); it++)
			{
				std::ostringstream ss;
				ss << (void*)it->first;
				print(ss.str() +" size: " + std::to_string(it->second.size) + " file: " + it->second.file + ": " + std::to_string(it->second.line) + "\n");
				size += (unsigned long)it->second.size;
			}
			print("Total size: " + std::to_string(size) + "\n");
		}

		void old_getCount()
		{
			float size = 0;
			std::string lineToWrite;
			for(std::map<std::string, int>::iterator it = refs.begin(); it != refs.end(); it++)
			{
				//std::cout << it->first << " : " << it->second << "\n";
				lineToWrite.append(it->first +" : " +std::to_string(it->second) +"\n");
				std::cout << lineToWrite;
				size += sizeof(it->first.c_str()) * it->second;
			}
			lineToWrite.append(std::to_string(size));
			//std::cout << "\nTotal size: " << size << "\n";
		}

		void addRef(std::string type, int count = 1)
		{
			std::map<std::string, int>::iterator it;
			it = refs.find(type);
			if(it == refs.end())
				refs.insert(std::pair<std::string, int>(type, count));
			else
				it->second++;
		}
		void removeRef(std::string type, int count = 1)
		{
			std::map<std::string, int>::iterator it;
			it = refs.find(type);
			assert(it->second > 0);
			it->second--;
			if(it->second == 0)
				refs.erase(it);
		}
		
	private:
		struct new_ptr_list
		{
			const char*         file;
			int                 line;
			size_t              size;
		};

		MemoryManager(){};
		~MemoryManager()
		{
			if(nRefs.size() > 0)
			{
				print("Memory leak\n");
				getCount();
			}
			else
				print("No leaks\n");
		};

		void print(std::string line)
		{
			std::cout << line;
		}

		std::map<std::string, int> refs;
		std::map <void *, new_ptr_list> nRefs;

	};

	/*
	template <class T>
	class Ref
	{
	public:
		Ref()
		{
			//_ptr = (T*) malloc(sizeof(T)); 
			_ptr = new T();
		}
		Ref(const T& t)
		{
			this->_ptr = new T(t);
		}

		~Ref()
		{
			MemoryManager::getInstance().removeRef(typeid(T).name());
			delete _ptr;
		};
		
		//Ref<T>& operator=(const Ref<T> &t)
		//{
		//MemoryManager::getInstance().addRef(typeid(T).name());
		//return *this;
		//}
		//Ref<T>& operator=(T * t)
		//{
		//MemoryManager::getInstance().addRef(typeid(T).name());
		//return *this;

		//}
		
		void * operator new (size_t size)
		{
			void * mem = malloc(size);
			MemoryManager::getInstance().addRef(typeid(T).name());
			return mem;
		}
		T * get()
		{
			return _ptr;
		}
		T* operator->()
		{
			return _ptr;
		}

	private:
		T * _ptr;
		//shared_ptr<T> _sptr;
	};

	*/
}

void* operator new(size_t size, const char* file, int line)
{
	void * ref = malloc(size);// operator new(size);
	core::MemoryManager::getInstance().addRef(ref, file, line, size);
	return ref;
}
void* operator new(size_t size)
{
	return malloc(size);
	//return operator new(size, "<Unknown>", 0);
}
void* operator new[](size_t size, const char* file, int line)
{
	void * ref = operator new[](size);
	core::MemoryManager::getInstance().addRef(ref, file, line, size);
	return ref;
}
void operator delete(void* ptr)
{
	if(!core::MemoryManager::getInstance().removeRef(ptr))
		free(ptr);// operator delete(ptr, std::nothrow);
	
}
void operator delete[](void* ptr)
{
	if(!core::MemoryManager::getInstance().removeRef(ptr))
		free(ptr);// operator delete(ptr, std::nothrow);
	//free(ptr);
}
//void operator delete(void* ptr, const char* file, int line) _NOEXCEPT;
//void operator delete[](void* ptr, const char* file, int line) _NOEXCEPT;

#define DEBUG_NEW new(__FILE__, __LINE__)
#define new DEBUG_NEW
//#define DEBUG_DELETE core::delete(void* ptr)
//#define delete DEBUG_DELETE