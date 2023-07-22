#pragma once
namespace crustgames {
	class Utils {
	public:
		static inline bool CollisionAABB(int x,int y,int width,int height,int otherX,int otherY,int otherWidth,int otherHeight) {
            // 检查两个AABB是否相交
            if (x < otherX + otherWidth &&
                x + width > otherX &&
                y < otherY + otherHeight &&
                y + height > otherY) {
                return true;  // 相交
            }
            return false;     // 不相交
		}
	};
};
