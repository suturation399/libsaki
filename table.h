#ifndef TABLE_H
#define TABLE_H

#include "who.h"
#include "ticketfolder.h"
#include "mount.h"
#include "girl.h"
#include "tableview.h"
#include "tableoperator.h"
#include "tableobserver.h"
#include "tilecount.h"
#include "skillpop.h"

#include <memory>
#include <iostream>



namespace saki
{



class KanContext
{
public:
    KanContext() = default;
    explicit KanContext(const KanContext &copy) = default;
    KanContext &operator=(const KanContext &copy) = default;
    ~KanContext() = default;

    bool during() const;
    bool duringMinkan() const;
    bool duringAnkan() const;
    Who pao() const;

    void enterDaiminkan(Who pao);
    void enterAnkan();
    void enterKakan();

    /// \brief Called when a discard or another kan happens
    void leave();

private:
    bool mDuring = false;
    bool mMinkan;
    Who mPao;
};



struct Furiten
{
    bool sutehai = false;
    bool doujun = false;
    bool riichi = false;
    bool any() const { return sutehai || doujun || riichi; }
    bool none() const { return !any(); }
};



class TablePrivate
{
protected:
    TablePrivate(const std::array<int, 4> &points,
                 RuleInfo rule, Who tempDealer);
    explicit TablePrivate(const TablePrivate &copy) = default;
    TablePrivate &operator=(const TablePrivate &assign) = delete;
    ~TablePrivate() = default;

protected:
    Mount mMount;
    const RuleInfo mRule;
    KanContext mKanContext;
    TableFocus mFocus;

    std::array<int, 4> mPoints;
    std::array<int, 4> mRiichiHans;
    std::array<int, 4> mLayPositions;
    std::array<Furiten, 4> mFuritens;
    std::array<Hand, 4> mHands;
    std::array<std::vector<T37>, 4> mRivers;
    std::array<std::vector<bool>, 4> mPickeds;
    std::array<TicketFolder, 4> mTicketFolders;
    std::array<Action, 4> mActionInbox;

    int mRound = 0;
    int mExtraRound = -1; // work with beforeEast1()
    int mDeposit = 0;
    int mDice;

    Who mDealer;
    Who mInitDealer;

    bool mAllLast = false;
    bool mToChangeDealer = false;
    bool mPrevIsRyuu = false;
    bool mToEstablishRiichi;
    bool mToFlip;

    std::bitset<4> mIppatsuFlags;
    std::array<std::bitset<34>, 4> mGenbutsuFlags;
};



class Table : private TablePrivate
{
public:
    explicit Table(const std::array<int, 4> &points,
                   const std::array<int, 4> &girlIds,
                   const std::array<TableOperator*, 4> &operators,
                   const std::vector<TableObserver*> &observers,
                   RuleInfo rule, Who tempDealer);

    explicit Table(const Table &orig,
                   const std::array<TableOperator*, 4> &operators,
                   const std::vector<TableObserver*> &observers,
                   Who toki, const TicketFolder &clean);

    Table(const Table &copy) = delete;
    Table &operator=(const Table &assign) = delete;

    void start();
    void action(Who who, const Action &act);

    const Hand &getHand(Who who) const;
    const std::vector<T37> &getRiver(Who who) const;
    const Girl &getGirl(Who who) const;
    TableView getView(Who who) const;
    const Furiten &getFuriten(Who who) const;
    const std::array<int, 4> &getPoints() const;
    int getRound() const;
    int getExtraRound() const;
    TileCount visibleRemain(Who who) const;
    int getRank(Who who) const;
    const TableFocus &getFocus() const;
    const T37 &getFocusTile() const;
    bool genbutsu(Who whose, T34 t) const;
    bool lastDiscardLay() const;
    bool riichiEstablished(Who who) const;
    bool duringKan() const;
    bool isAllLast() const;
    bool beforeEast1() const;
    bool inIppatsuCycle() const;

    Who findGirl(Girl::Id id) const;
    Who getDealer() const;
    int getDice() const;
    int getSelfWind(Who who) const;
    int getRoundWind() const;
    const RuleInfo &getRuleInfo() const;
    const TicketFolder &getTicketFolder(Who who) const;
    const Mount &getMount() const;

    void popUp(Who who, const SkillExpr &expr) const;

private:
    void process();
    void singleAction(Who who, const Action &act);

    void nextRound();
    void clean();
    void rollDice();
    void deal();
    void flip();
    void tryDraw(Who who);
    void swapOut(Who who, const T37 &out);
    void spinOut(Who who);
    void onDiscarded();
    void declareRiichi(Who who);
    bool finishRiichi();
    void chii(Who who, ActCode dir, bool showAka5);
    void pon(Who who, int showAka5);
    void daiminkan(Who who);
    void pick();
    void ankan(Who who, T34 tile);
    void kakan(Who who, int barkId);
    void finishKan(Who who);
    void activate();
    bool anyActivated() const;
    bool kanOverflow(Who kanner);
    bool noBarkYet() const;
    bool checkDeathWinds() const;
    void checkRon(bool only13 = false);
    void checkBark();
    void checkSutehaiFuriten();
    bool nagashimangan(Who who) const;
    void exhaustRound(RoundResult result, const std::vector<Who> &openers);
    void finishRound(const std::vector<Who> &openers, Who gunner);
    void endOrNext();
    void endTable();

    PointInfo getPointInfo(Who who);

private:
    std::array<std::unique_ptr<Girl>, 4> mGirls;
    std::array<TableOperator*, 4> mOperators;
    std::vector<TableObserver*> mObservers;
};



} // namespace saki



#endif // TABLE_H

