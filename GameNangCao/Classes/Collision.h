#pragma once
#include "Box.h"
#include <Windows.h>
#include <limits>

static class CollisionClass {
public:
	static void GetSweptBroadphaseBox(Box* b, float dt, Box* returnBox)
	{
		returnBox->x = b->vx > 0 ? b->x : b->x + b->vx * dt;
		returnBox->y = b->vy > 0 ? b->y : b->y + b->vy * dt;
		returnBox->width = b->vx > 0 ? b->vx * dt + b->width : b->width - b->vx * dt;
		returnBox->height = b->vy > 0 ? b->vy * dt + b->height : b->height - b->vy * dt;
	}

	static bool AABBCheck(Box* a, Box* b)
	{
		if (a->width == 0 || a->height == 0 || b->width == 0 || b->height == 0)
			return false;
		return !(a->x + a->width < b->x || a->x > b->x + b->width || a->y + a->height < b->y || a->y > b->y + b->height);
	}

	static float SweptAABB(Box* b1, Box* b2, float& normalx, float& normaly, float dt)
	{
		float xInvEntry, yInvEntry;
		float xInvExit, yInvExit;
		float vx = b1->vx - b2->vx;
		float vy = b1->vy - b2->vy;

		if (vx > 0)
		{
			xInvEntry = b2->x - (b1->x + b1->width);
			xInvExit = (b2->x + b2->width) - b1->x;
		}
		else
		{
			xInvEntry = (b2->x + b2->width) - b1->x;
			xInvExit = b2->x - (b1->x + b1->width);
		}

		if (vy > 0)
		{
			yInvEntry = b2->y - (b1->y + b1->height);
			yInvExit = b2->y + b2->height - b1->y;
		}
		else
		{
			yInvEntry = b2->y + b2->height - b1->y;
			yInvExit = b2->y - (b1->y + b1->height);
		}

		float xEntry, yEntry;
		float xExit, yExit;

		if (vx == 0)
		{
			xEntry = -std::numeric_limits<float>::infinity();
			xExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			xEntry = xInvEntry / (vx * dt);
			xExit = xInvExit / (vx * dt);
		}

		if (vy == 0)
		{
			yEntry = -std::numeric_limits<float>::infinity();
			yExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			yEntry = yInvEntry / (vy * dt);
			yExit = yInvExit / (vy * dt);
		}

		float entryTime = max(xEntry, yEntry);
		float exitTime = min(xExit, yExit);

		if (entryTime > exitTime || (xEntry < 0 && yEntry < 0) || xEntry > 1 || yEntry > 1)
		{
			normalx = 0;
			normaly = 0;

			return 1;
		}
		else
		{
			if (xEntry > yEntry)
			{
				if (xInvEntry < 0)
				{
					normalx = 1;
					normaly = 0;
				}
				else
				{
					normalx = -1;
					normaly = 0;
				}
			}
			else
			{
				if (yInvEntry < 0)
				{
					normalx = 0;
					normaly = 1;
				}
				else
				{
					normalx = 0;
					normaly = -1;
				}
			}

			return entryTime;
		}
	}
};