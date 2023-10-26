#include "ProjectilePool.h"

std::list<std::reference_wrapper<Projectile>> ProjectilePool::GetActiveElements()
{
    std::list<std::reference_wrapper<Projectile>> activeElements = {};

    if (!elements.empty())
    {
        for (std::list<Projectile>::iterator it = elements.begin(); it != elements.end(); it++)
        {
            if (it->IsActive()) activeElements.push_back(*it);
        }
    }

    return activeElements;
}

void ProjectilePool::AddElement(Vector2 startingPosition, float directionAngleInDegrees)
{
    if (!elements.empty())
    {
        for (std::list<Projectile>::iterator it = elements.begin(); it != elements.end(); it++)
        {
            if (!it->IsActive())
            {
                it->Reset(startingPosition, directionAngleInDegrees);
                return;
            }
        }
    }

    elements.push_back(Projectile(startingPosition, directionAngleInDegrees));
}

void ProjectilePool::Clear()
{
    if (!elements.empty())
    {
        for (std::list<Projectile>::iterator it = elements.begin(); it != elements.end(); it++)
        {
            it->SetActive(false);
        }
    }
}
