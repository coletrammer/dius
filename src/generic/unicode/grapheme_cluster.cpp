#include "dius/unicode/grapheme_cluster.h"

#include "di/util/unreachable.h"
#include "dius/unicode/grapheme_cluster_break.h"
#include "dius/unicode/name.h"

namespace dius::unicode {
// This defines are states for the grapheme clusterer. Each state has a function
// which maps from the grapheme cluster property to a new state. Transitions
// back to ground indicate the current cluster is finished.
enum class GraphemeClusterState : u8 {
    // crlf | Control | precore* core postcore*

    // Initial state. When transitioning back to Ground, no code point is consumed.
    Ground,

    // crlf := CR LF | CR | LF
    PendingCRLF, // Start for matching LF after CR

    // precore := Prepend
    PendingPrecore, // State after matching anything at least 1 item from precore

    // postcore := [Extend ZWJ SpacingMark]
    PendingPostcore, // State after matching anything at least 1 item from postcore

    // core := hangul-syllable | RI-Sequence | xpicto-sequence | conjunctCluster | [ ^Control CR LF ]
    // We don't any states, mathcing the last case takes us straight to PendingPostcore.

    // RI-Sequence := RI RI
    PendingRegionalIndiciator, // State after matching one RI

    // hangul-syllable := L* (V+ | LV V* | LVT) T* | L+ | T+
    PendingHangulL, // State after matching an initial "L"
    PendingHangulT, // State after matching an initial "T"
    PendingHangulV, // State after matching a "V"

    // xpicto-sequence := \p{Extended_Pictographic} (Extend* ZWJ \p{Extended_Pictographic})*
    PendingZWJPictographic, // State before getting a ZWJ
    PendingPictographic,    // State before getting a ZWJ

    // conjunctCluster := \p{InCB=Consonant} ([\p{InCB=Extend} \p{InCB=Linker}]* \p{InCB=Linker} [\p{InCB=Extend}
    // \p{InCB=Linker}]* \p{InCB=Consonant})+
    PendingIndicLinker,    // State before matching the first InCB=Linker
    PendingIndicConsonant, // State after matching the first InCb=Linker

    // Count of states
    StateCount,

    // When transitioning to this state,
    // we emit any pending grapheme but don't consume the current code point, and
    // then move back to the ground state. This is after StateCount as its not
    // a real state.
    GroundConsume,
};

constexpr static auto pending_postcore(GraphemeClusterBreak b) -> GraphemeClusterState {
    using enum GraphemeClusterBreak;
    // postcore := [Extend ZWJ SpacingMark]
    switch (b) {
        case Extend:
        case Extend_IndicConjunctBreak_Extend:
        case Extend_IndicConjunctBreak_Linker:
        case ZWJ:
        case SpacingMark:
            return GraphemeClusterState::PendingPostcore;
        default:
            return GraphemeClusterState::Ground;
    }
}

constexpr static auto pending_indic_linker(GraphemeClusterBreak b) -> GraphemeClusterState {
    using enum GraphemeClusterBreak;
    // This state means we're expected InCB=Linker before we can get a consonant.
    // conjunctCluster := \p{InCB=Consonant} ([\p{InCB=Extend} \p{InCB=Linker}]* \p{InCB=Linker} [\p{InCB=Extend}
    // \p{InCB=Linker}]* \p{InCB=Consonant})+
    switch (b) {
        case GraphemeClusterBreak::Extend_IndicConjunctBreak_Linker:
            // Now we expect a InCB=Consonant.
            return GraphemeClusterState::PendingIndicConsonant;
        case Extend_IndicConjunctBreak_Extend:
        case ZWJ:
            // Keep matching until we get InCB=Linker
            return GraphemeClusterState::PendingIndicLinker;
        default:
            // All non consonants are either Extend or ZWJ, meaning they would've matched postcore. When
            // we fail to match here we're now effectively just in postcore.
            return pending_postcore(b);
    }
    di::unreachable();
}

constexpr static auto pending_indic_consonant(GraphemeClusterBreak b) -> GraphemeClusterState {
    using enum GraphemeClusterBreak;
    // This state means we're expected a InCB=Consonant
    // conjunctCluster := \p{InCB=Consonant} ([\p{InCB=Extend} \p{InCB=Linker}]* \p{InCB=Linker} [\p{InCB=Extend}
    // \p{InCB=Linker}]* \p{InCB=Consonant})+
    switch (b) {
        case Other_IndicConjunctBreak_Consonant:
            // Keep matching more blocks (+ case)
            return GraphemeClusterState::PendingIndicLinker;
        case Extend_IndicConjunctBreak_Linker:
        case Extend_IndicConjunctBreak_Extend:
        case ZWJ:
            // Keep trying to find an InCB=Consonant
            return GraphemeClusterState::PendingIndicConsonant;
        default:
            // All non consonants are either Extend or ZWJ, meaning they would've matched postcore. When
            // we fail to match here we're now effectively just in postcore.
            return pending_postcore(b);
    }
    di::unreachable();
}

constexpr static auto pending_hangul_v(GraphemeClusterBreak b) -> GraphemeClusterState {
    using enum GraphemeClusterBreak;
    // This state matches the part of the sequence once a V has occurred.
    // L* (V+ | LV V* | LVT) T*
    switch (b) {
        case V:
            // Keep matching more.
            return GraphemeClusterState::PendingHangulV;
        case T:
            // Now we just match any trailing T.
            return GraphemeClusterState::PendingHangulT;
        default:
            // Since we got something other than V or T, we have to move to postcore.
            // This is expected as T* fully is optional.
            return pending_postcore(b);
    }
    di::unreachable();
}

constexpr static auto pending_hangul_t(GraphemeClusterBreak b) -> GraphemeClusterState {
    using enum GraphemeClusterBreak;
    // This state matches the part of the sequence once a T has occurred.
    // L* (V+ | LV V* | LVT) T*
    switch (b) {
        case T:
            // Keep matching more.
            return GraphemeClusterState::PendingHangulT;
        default:
            // Since we got something other than T, we have to move to postcore.
            return pending_postcore(b);
    }
    di::unreachable();
}

constexpr static auto pending_hangul_l(GraphemeClusterBreak b) -> GraphemeClusterState {
    using enum GraphemeClusterBreak;
    // This state matches the part of the sequence once an L has occurred
    // L* (V+ | LV V* | LVT) T* | L+
    switch (b) {
        case L:
            // Keep matching more.
            return GraphemeClusterState::PendingHangulL;
        case V:
        case LV:
            // Now match V
            return GraphemeClusterState::PendingHangulV;
        case LVT:
            // Now match T
            return GraphemeClusterState::PendingHangulT;
        default:
            // We've matched L+, so continue to post core
            return pending_postcore(b);
    }
    di::unreachable();
}

constexpr static auto pending_pictographic(GraphemeClusterBreak b) -> GraphemeClusterState {
    using enum GraphemeClusterBreak;
    // This state matches the end of this sequence.
    // (Extend* ZWJ \p{Extended_Pictographic})*
    switch (b) {
        case Other_ExtendedPictographic:
            // Keep matching more.
            return GraphemeClusterState::PendingZWJPictographic;
        default:
            // Since we got something other than what we expected, we have to move to postcore.
            // We may have already gotten Extend or ZWJ characters in this state, but that's fine
            // as they overlap with postcore anyway.
            return pending_postcore(b);
    }
    di::unreachable();
}

constexpr static auto pending_zwj_pictographic(GraphemeClusterBreak b) -> GraphemeClusterState {
    using enum GraphemeClusterBreak;
    // This state matches the beginning of this sequence.
    // (Extend* ZWJ \p{Extended_Pictographic})*
    switch (b) {
        case Extend:
        case Extend_IndicConjunctBreak_Extend:
        case Extend_IndicConjunctBreak_Linker:
            // Stay in this state.
            return GraphemeClusterState::PendingZWJPictographic;
        case ZWJ:
            return GraphemeClusterState::PendingPictographic;
        default:
            // Since we got something other than what we expected, we have to move to postcore.
            // We may have already gotten Extend characters in this state, but that's fine
            // as they overlap with postcore anyway.
            return pending_postcore(b);
    }
    di::unreachable();
}

constexpr static auto pending_regional_indicator(GraphemeClusterBreak b) -> GraphemeClusterState {
    using enum GraphemeClusterBreak;
    // RI-Sequence := RI RI
    switch (b) {
        case RegionalIndicator:
            return GraphemeClusterState::PendingPostcore;
        default:
            // Since we failed to get our second RI, we transition to
            // postcore, as if we had gotten any "normal" character.
            return pending_postcore(b);
    }
    di::unreachable();
}

constexpr static auto pending_precore(GraphemeClusterBreak b) -> GraphemeClusterState {
    // precore := Prepend
    using enum GraphemeClusterBreak;
    switch (b) {
        // Prepend
        case Prepend:
            return GraphemeClusterState::PendingPrecore;

        // hangul-syllable := L* (V+ | LV V* | LVT) T* | L+ | T+
        case L:
            return GraphemeClusterState::PendingHangulL;
        case V:
        case LV:
            return GraphemeClusterState::PendingHangulV;
        case LVT:
        case T:
            return GraphemeClusterState::PendingHangulT;

        // RI-Sequence := RI RI
        case RegionalIndicator:
            return GraphemeClusterState::PendingRegionalIndiciator;

        // xpicto-sequence := \p{Extended_Pictographic} (Extend* ZWJ \p{Extended_Pictographic})*
        case Other_ExtendedPictographic:
            return GraphemeClusterState::PendingZWJPictographic;

        // conjunctCluster := \p{InCB=Consonant} ([\p{InCB=Extend} \p{InCB=Linker}]* \p{InCB=Linker} [\p{InCB=Extend}
        // \p{InCB=Linker}]* \p{InCB=Consonant})+
        case Other_IndicConjunctBreak_Consonant:
            return GraphemeClusterState::PendingIndicLinker;

        // [^Control CR LF]
        case Control:
        case LF:
        case CR:
            // This is an error case, which we mask by just resetting.
            return GraphemeClusterState::Ground;
        default:
            return GraphemeClusterState::PendingPostcore;
    }
    di::unreachable();
}

constexpr static auto pending_crlf(GraphemeClusterBreak b) -> GraphemeClusterState {
    using enum GraphemeClusterBreak;
    // CR LF
    switch (b) {
        case LF:
            return GraphemeClusterState::GroundConsume;
        default:
            return GraphemeClusterState::Ground;
    }
    di::unreachable();
}

// crlf | Control | precore* core postcore*
constexpr static auto ground(GraphemeClusterBreak b) -> GraphemeClusterState {
    using enum GraphemeClusterBreak;
    switch (b) {
        // Control
        case Control:
        // crlf
        case LF:
            return GraphemeClusterState::GroundConsume;
        case CR:
            return GraphemeClusterState::PendingCRLF;
        default:
            // Now we have to match precore* core postcore*
            return pending_precore(b);
    }
    di::unreachable();
}

constexpr static auto invoke_state(GraphemeClusterState current, GraphemeClusterBreak b) -> GraphemeClusterState {
    using enum GraphemeClusterState;
    switch (current) {
        case Ground:
        case GroundConsume:
            return ground(b);
        case PendingCRLF:
            return pending_crlf(b);
        case PendingPrecore:
            return pending_precore(b);
        case PendingPostcore:
            return pending_postcore(b);
        case PendingRegionalIndiciator:
            return pending_regional_indicator(b);
        case PendingHangulT:
            return pending_hangul_t(b);
        case PendingHangulV:
            return pending_hangul_v(b);
        case PendingHangulL:
            return pending_hangul_l(b);
        case PendingZWJPictographic:
            return pending_zwj_pictographic(b);
        case PendingPictographic:
            return pending_pictographic(b);
        case PendingIndicLinker:
            return pending_indic_linker(b);
        case PendingIndicConsonant:
            return pending_indic_consonant(b);
        case StateCount:
            break;
    }
    di::unreachable();
}

constexpr static auto state_count = usize(GraphemeClusterState::StateCount);
constexpr static auto cluster_break_count = usize(di::meta::TupleSize<di::Reflect<GraphemeClusterBreak>>);

constexpr static auto construct_state_lookup_table() {
    auto result = di::Array<di::Array<GraphemeClusterState, cluster_break_count>, state_count> {};
    for (auto [s, b] : di::cartesian_product(di::range(state_count), di::range(cluster_break_count))) {
        result[s][b] = invoke_state(GraphemeClusterState(s), GraphemeClusterBreak(b));
    }
    return result;
}

constexpr static auto lookup_table = construct_state_lookup_table();

constexpr static auto lookup_break(c32 code_point) -> GraphemeClusterBreak {
    // Fast path for single code points and ascii.
    using enum GraphemeClusterBreak;
    switch (code_point) {
        case '\r':
            return CR;
        case '\n':
            return LF;
        case ZeroWidthJoiner:
            return ZWJ;
        default:
            if (code_point >= 0x20 && code_point < 0x7f) {
                return Other;
            }
            return grapheme_cluster_break(code_point);
    }
}

auto GraphemeClusterer::is_boundary(c32 code_point) -> bool {
    auto was_ground = m_state == u8(GraphemeClusterState::Ground);
    auto b = lookup_break(code_point);
    auto next_state = lookup_table[m_state][u8(b)];
    if (next_state == GraphemeClusterState::Ground) {
        // When exiting directly to the ground state, we need to perform another lookup.
        next_state = lookup_table[u8(next_state)][u8(b)];
        was_ground = true;
    }
    if (next_state == GraphemeClusterState::GroundConsume) {
        next_state = GraphemeClusterState::Ground;
    }

    m_state = u8(next_state);
    return was_ground;
};
}
