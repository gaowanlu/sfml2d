#pragma once
namespace crustgames {
	class Utils {
	public:
		static inline bool CollisionAABB(int x,int y,int width,int height,int otherX,int otherY,int otherWidth,int otherHeight) {
            // �������AABB�Ƿ��ཻ
            if (x < otherX + otherWidth &&
                x + width > otherX &&
                y < otherY + otherHeight &&
                y + height > otherY) {
                return true;  // �ཻ
            }
            return false;     // ���ཻ
		}
	};
};
