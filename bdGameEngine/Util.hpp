#pragma once 
#include "Include.hpp"

namespace Util
{
	//Used for hitboxes
	bool bIsRectColliding( const Rect &rect1, const Rect &rect2 )
	{
		if ( rect1.x + rect1.width < rect2.x || rect2.x + rect2.width < rect1.x )
		{
			return false;
		}

		if ( rect1.y + rect1.height < rect2.y || rect2.y + rect2.height < rect1.y )
		{
			return false;
		}
		return true;
	}

	//Used for zones / trigger-zones / etc
	bool bIsRectInside( const Rect &outer, const Rect &inner )
	{
		return inner.x >= outer.x &&
			inner.y >= outer.y &&
			inner.x + inner.width <= outer.x + outer.width &&
			inner.y + inner.height <= outer.y + outer.height;
	}
}