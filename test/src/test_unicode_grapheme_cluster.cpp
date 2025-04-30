#include "di/test/prelude.h"
#include "dius/print.h"
#include "dius/unicode/grapheme_cluster.h"
#include "dius/unicode/grapheme_cluster_break.h"
#include "grapheme_break_test_data.h"

namespace unicode_grapheme_cluster {
using namespace dius::unicode;

static void clusterer_basic() {
    auto clusterer = GraphemeClusterer {};

    ASSERT(clusterer.is_boundary('\0'));
    ASSERT(clusterer.is_boundary('\r'));
    ASSERT(!clusterer.is_boundary('\n'));
    ASSERT(clusterer.is_boundary('\r'));
    ASSERT(clusterer.is_boundary(0x600));
}

static void clusterer_generated() {
    for (auto [i, test] : grapheme_break_test_data | di::enumerate) {
        auto clusterer = GraphemeClusterer {};
        auto result = di::Vector<GraphemeBreakTestCodePoint> {};
        for (auto [c, b] : test) {
            result.push_back({ c, clusterer.is_boundary(c) });
        }
        auto expected = di::Vector<GraphemeBreakTestCodePoint> {};
        for (auto a : test) {
            expected.push_back(a);
        }

        if (result != expected) {
            dius::println("FAIL: grapheme cluster test #{}"_sv, i);
            dius::println("TOKENS: {}"_sv, test | di::transform([](auto x) {
                                               return grapheme_cluster_break(x.code_point);
                                           }));
            dius::println(u8"RESULT: {}÷"_sv, result | di::transform(di::to_string) | di::join | di::to<di::String>());
            dius::println(u8"EXPECT: {}÷"_sv,
                          expected | di::transform(di::to_string) | di::join | di::to<di::String>());
        }
        ASSERT_EQ(result, expected);
    }
}

static void grapheme_clusters_view() {
    auto s = u8"abc👩🏿‍🔧🇦🇴d\u0600"_sv;
    auto r = grapheme_clusters(s) | di::to<di::Vector>();
    auto e = di::Vector {
        "a"_sv, "b"_sv, "c"_sv, u8"👩🏿‍🔧"_sv, u8"🇦🇴"_sv, "d"_sv, u8"\u0600"_sv,
    };
    ASSERT_EQ(r, e);
}

TEST(unicode_grapheme_cluster, clusterer_basic)
TEST(unicode_grapheme_cluster, clusterer_generated)
TEST(unicode_grapheme_cluster, grapheme_clusters_view)
}
