#include "di/test/prelude.h"
#include "dius/print.h"
#include "dius/unicode/grapheme_cluster.h"

namespace unicode_grapheme_cluster {
using namespace dius::unicode;

static void clusterer() {
    auto clusterer = GraphemeClusterer {};

    ASSERT(clusterer.is_boundary('\0'));
    ASSERT(clusterer.is_boundary('\r'));
    ASSERT(!clusterer.is_boundary('\n'));
    ASSERT(clusterer.is_boundary('\r'));
    ASSERT(clusterer.is_boundary(0x600));
}

static void grapheme_clusters_view() {
    auto s = u8"abc👩🏿‍🔧🇦🇴d\u0600"_sv;
    auto r = grapheme_clusters(s) | di::to<di::Vector>();
    auto e = di::Vector {
        "a"_sv, "b"_sv, "c"_sv, u8"👩🏿‍🔧"_sv, u8"🇦🇴"_sv, "d"_sv, "\u0600"_sv,
    };
    ASSERT_EQ(r, e);
}

TEST(unicode_grapheme_cluster, clusterer)
TEST(unicode_grapheme_cluster, grapheme_clusters_view)
}
