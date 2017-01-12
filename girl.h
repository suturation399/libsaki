#ifndef GIRL_H
#define GIRL_H

#include "mount.h"
#include "skillpop.h"
#include "who.h"

#include <bitset>



#define GIRL_CTORS(Name) \
    Name(Who who, Id id) : Girl(who, id) { }; \
    Name(const Name &copy) = default; \
    Name *clone() const override { return new Name(*this); }

#define GIRL_CTORS_CLONE_ONLY(Name) \
    Name(const Name &copy) = default; \
    Name *clone() const override { return new Name(*this); }



namespace saki
{



class Princess;
class Hand;
class Table;
class TicketFolder;

struct IrsCheckRow
{
    const bool mono;
    const bool indent;
    const char *name;
    bool able;
    bool on;
};

class Girl
{
public:
    enum class Id
    {
        DOGE = 0,

        // IH71 A-Block
        MIYANAGA_TERU = 710111, HIROSE_SUMIRE = 710112, SHIBUYA_TAKAMI = 710113,
            MATANO_SEIKO = 710114, OOHOSHI_AWAI = 710115,
        MATSUMI_KURO = 712411, MATSUMI_YUU = 712412,
        ONJOUJI_TOKI = 712611,

        // IH71 B-Block
        USUZUMI_HATSUMI = 712714, IWATO_KASUMI = 712715,
        ANETAI_TOYONE = 712915,
        KATAOKA_YUUKI = 713311, SOMEYA_MAKO = 713312, TAKEI_HISA = 713313,
            HARAMURA_NODOKA = 713314, MIYANAGA_SAKI = 713315,
        UESHIGE_SUZU = 713811, SUEHARA_KYOUKO = 713815,
        SHISHIHARA_SAWAYA = 714915,

        // Others
        NANPO_KAZUE = 713301,
        INAMURA_KYOUKA = 990001, SHIRATSUKI_SHINO = 990002
    };

    enum NmSkill
    {
        WHITE_CLOUD, ZIM_M, ZIM_P, ZIM_S,
        NUM_NM_SKILL
    };

    static Girl *create(Who who, int id);
    virtual Girl *clone() const;
    virtual ~Girl() = default;
    Girl &operator=(const Girl &assign) = delete;

    Id getId() const;

    virtual void onDice(const Table &table, TicketFolder &tickets);
    virtual void onMonkey(std::array<Exist, 4> &exists, const Princess &princess);
    virtual bool checkInit(Who who, const Hand &init, const Princess &princess, int iter);
    virtual void onActivate(const Table &table, TicketFolder &tickets);
    virtual void onInbox(Who who, const Action &action);
    virtual void onDraw(const Table &table, Mount &mount, Who who, bool rinshan);
    virtual void onChooseFirstDealer(Who tempDealer, int &die1, int &die2);
    virtual void onDiscarded(const Table &table, Who who);
    virtual void onRiichiEstablished(const Table &table, Who who);

    virtual const std::array<bool, 4> &irsRivalMask() const;
    virtual const IrsCheckRow &irsCheckRow(int index) const;
    virtual int irsCheckCount() const;

    virtual TicketFolder forwardAction(const Table &table, Mount &mount, const Action &action);

    virtual void nonMonkey(TileCount &init, Mount &mount, std::bitset<NUM_NM_SKILL> &presence,
                           const Princess &princess);


    virtual std::string stringOf(const SkillExpr &expr) const;

protected:
    Girl(Who who, Id id);
    Girl(const Girl &copy);

    static void eraseRivered(std::vector<T34> &ts, const std::vector<T37> &river);
    void accelerate(Mount &mount, const Hand &hand, const std::vector<T37> &river, int delta);

protected:
    const Who mSelf;
    const Id mId;
};



} // namespace saki



#endif // GIRL_H

