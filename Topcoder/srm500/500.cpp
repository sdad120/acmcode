#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

class FractalPicture{
public:
    double get(int x1, int y1, int x2, int y2, int dep){
        if (x1 < -27) x1 = -27; if (x2 > 27) x2 = 27; if (y1 < 0) y1 = 0; if (y2 > 81) y2 = 81;
        if (x1 > x2 || y1 > y2 || x2 < -27 || x1 > 27 || y1 > 81 || y2 < 0) return 0;
        if (x1 <= -27 && x2 >= 27 && y1 <= 0 && y2 >= 81){
            return 54 * dep + 27;
        }
        if (dep == 1){
            if (x1 > 0 || x2 < 0) return 0;
            return max(0, min(54, y2) - max(0, y1));
        }
        double ret = 0;
        ret += get(x1 * 3, (y1 - 54) * 3, x2 * 3, (y2 - 54) * 3, dep - 1);
        ret += get((y1 - 54) * 3, x1 * 3, (y2 - 54) * 3, x2 * 3, dep - 1);
        ret += get((y1 - 54) * 3, -x2 * 3, (y2 - 54) * 3, -x1 * 3, dep - 1);
        ret /= 3;
        if (x1 <= 0 && x2 >= 0)
        ret += max(0, min(54, y2) - max(0, y1));
        return ret;
    }

    double getLength(int x1, int y1, int x2, int y2){
        return get(x1, y1, x2, y2, 500);
        
    }
};
