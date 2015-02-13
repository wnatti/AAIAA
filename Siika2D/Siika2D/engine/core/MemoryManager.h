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

	/** MemoryManager class keeps count of objects created by overloaded new will print out list of unfreed memory at ~MemoryManager
	
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
			if(nRefs.size() < 1)
				return false;
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

		std::map <void *, new_ptr_list> nRefs;

	};

}

void* operator new(size_t size, const char* file, int line)
{
	void * ref = malloc(size);
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
		free(ptr);
	
}
void operator delete[](void* ptr)
{
	if(!core::MemoryManager::getInstance().removeRef(ptr))
		free(ptr);
}
//void operator delete(void* ptr, const char* file, int line) _NOEXCEPT;
//void operator delete[](void* ptr, const char* file, int line) _NOEXCEPT;

#define DEBUG_NEW new(__FILE__, __LINE__)
#define new DEBUG_NEW