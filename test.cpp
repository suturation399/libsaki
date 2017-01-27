#include "test.h"
#include "tilecount.h"
#include "hand.h"
#include "form.h"
#include "table.h"
#include "ai.h"
#include "util.h"

#include <iostream>
#include <cstring>
#include <cassert>



namespace saki
{



TestScope::TestScope(const char *str, bool nl)
{
    int len = 16 - strlen(str);
    len = len > 0 ? len : 1;
    std::cout << str << std::string(len, ' ') << std::flush;
    if (nl)
        std::cout << std::endl;
    mStart = std::chrono::steady_clock::now();

}

TestScope::~TestScope()
{
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    auto t = std::chrono::duration_cast<std::chrono::milliseconds>(end - mStart).count();
    std::cout << " PASS " << t << "ms" << std::endl;
}



void testAll()
{
    testUtil();
    testTileCount();
    testHand();
    testForm();
    testTable();
}

void testUtil()
{
    TestScope test("util");

    std::vector<int> v { 1, 2, 3 };
    assert(!util::all(v, [](int i) { return i > 2; }));
    std::array<int, 4> a { 1, 2, 3 };
    assert(util::all(a, [](const int &i) { return i < 7; }));
}

void testTileCount()
{
    TestScope test("tile-count");

    using namespace tiles37;
    TileCount tc { 1_m, 1_m, 1_m, 2_p, 2_p, 2_p, 3_s, 3_s, 3_s, 4_f, 4_f, 4_f, 1_y, 1_y };
    assert(tc.step4(0) == -1);
    assert(tc.step(0) == -1);
}

void testHand()
{
    TestScope test("hand");

    using namespace tiles37;
    TileCount tc { 1_m, 1_m, 1_m, 2_p, 2_p, 2_p, 3_s, 3_s, 3_s, 4_f, 4_f, 4_f, 1_y };
    Hand hand(tc);
    assert(hand.step() == 0);

    hand.draw(1_y);
    assert(hand.step() == -1);
}

void testForm()
{
    TestScope test("form");

    using namespace tiles37;
    TileCount close { 1_m, 2_m, 3_m, 2_p, 3_p, 4_p, 3_s, 4_s, 5_s, 4_s, 5_s,   7_s, 7_s };
    Hand hand(close);

    RuleInfo rule;
    PointInfo info;
    info.selfWind = 1;
    info.roundWind = 1;

    Form form(hand, 6_s, info, rule);
    assert(form.hasYaku());
    assert(form.han() == 1);
    assert(form.spell() == "PnfNmi");
}

void testTable()
{
    TestScope test("table", true);

    std::array<int, 4> points { 25000, 25000, 25000, 25000 };
    std::array<int, 4> girlIds { 0, 0, 0, 0 };
    std::array<std::unique_ptr<Ai>, 4> ais;
    std::array<TableOperator*, 4> ops;
    std::vector<TableObserver*> obs;
    RuleInfo rule;
    for (int iter = 0; iter < 5; iter++) {
        for (int w = 0; w < 4; w++) {
            ais[w].reset(Ai::create(Who(w), Girl::Id(girlIds[w])));
            ops[w] = ais[w].get();
        }

        Table table(points, girlIds, ops, obs, rule, Who(0));
        table.start();
    }
}



} // namespace saki


