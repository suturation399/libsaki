#ifndef GIRLS_ACHIGA_H
#define GIRLS_ACHIGA_H

#include "girl.h"



namespace saki
{



class Kuro : public Girl
{
public:
    GIRL_CTORS(Kuro)
    void onMonkey(std::array<Exist, 4> &exists, const Princess &princess) override;
    void onDraw(const Table &table, Mount &mount, Who who, bool rinshan) override;
    void onDiscarded(const Table &table, Who who) override;

private:
    static const int INIT_DRAG_MK = 30;
    static const int DRAG_MK = 200;
    static const int EJECT_MK = 5000;
    bool mCd = false;
};

class Yuu : public Girl
{
public:
    GIRL_CTORS(Yuu)
    void onMonkey(std::array<Exist, 4> &exists, const Princess &princess) override;
    void onDraw(const Table &table, Mount &mount, Who who, bool rinshan) override;

private:
    static const int LV5_VAL = 90;
    static const int LV4_VAL = 60;
    static const int LV3_VAL = 30;

    static const std::vector<T34> LV5_TARS;
    static const std::vector<T34> LV4_TARS;
    static const std::vector<T34> LV3_TARS;
};



} // namespace saki



#endif // GIRLS_ACHIGA_H

