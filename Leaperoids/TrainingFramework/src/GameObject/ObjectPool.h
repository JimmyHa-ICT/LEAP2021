#pragma once
#include <vector>
#include "BaseObject.h"

template <class T>

class ObjectPool
{
private:
	std::vector<std::shared_ptr<T>> objects;
	int POOL_SIZE = 100;
	
public:
	ObjectPool()
	{
		Init();
	}

	void Init()
	{
		for (int i = 0; i < POOL_SIZE; i++)
		{
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			auto texture = ResourceManagers::GetInstance()->GetTexture("button_play");
			auto obj = std::make_shared<T>(model, shader, nullptr);
			objects.push_back(obj);
		}
	}

	std::shared_ptr<T> GetObjectT()
	{
		for (auto obj : objects)
		{
			if (!obj->isActive)
			{
				obj->isActive = true;
				return obj;
			}
		}

		Init();

		POOL_SIZE *= 2;
		return GetObjectT();
	}

	void ReturnObject(std::shared_ptr<T> obj)
	{
		obj->Reset();
	}

	void Update(GLfloat deltaTime)
	{
		for (auto obj : objects)
		{
			if (obj->isActive)
				obj->Update(deltaTime);
		}
	}

	void Draw()
	{
		for (auto obj : objects)
		{
			if (obj->isActive)
				obj->Draw();
		}
	}

	std::vector<std::shared_ptr<T>> GetAllActive()
	{
		std::vector<std::shared_ptr<T>> allActives;
		for (auto obj : objects)
		{
			if (obj->isActive)
				allActives.push_back(obj);
		}

		return allActives;
	}
};