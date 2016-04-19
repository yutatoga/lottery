#include "ofMain.h"

class LotteryImage : public ofImage{
public:
    void setKindId(int id);
    int getKindId();
    int kindId;
};