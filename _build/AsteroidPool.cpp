#include "AsteroidPool.h"

std::list<std::reference_wrapper<Asteroid>> AsteroidPool::GetActiveElements()
{
    std::list<std::reference_wrapper<Asteroid>> activeElements = {};

    if (!elements.empty())
    {
        for (std::list<Asteroid>::iterator it = elements.begin(); it != elements.end(); it++)
        {
            if (it->IsActive()) activeElements.push_back(*it);
        }
    }

    return activeElements;
}

void AsteroidPool::AddElements(int quantity, int screenWidth, int screenHeight)
{
    if (!elements.empty())
    {
        for (std::list<Asteroid>::iterator it = elements.begin(); it != elements.end() && quantity > 0; it++)
        {
            if (!it->IsActive())
            {
                it->Reset(screenWidth, screenHeight);
                quantity--;
            }
        }
    }

    while (quantity > 0)
    {
        elements.push_back(Asteroid());
        quantity--;
    }
}

void AsteroidPool::Clear()
{
    if (!elements.empty())
    {
        for (std::list<Asteroid>::iterator it = elements.begin(); it != elements.end(); it++)
        {
            it->SetActive(false);
        }
    }
}
