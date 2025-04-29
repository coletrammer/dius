#pragma once

#include "di/container/concepts/prelude.h"
#include "di/container/meta/prelude.h"
#include "di/container/view/view_interface.h"
#include "di/types/prelude.h"

namespace dius::unicode {
class GraphemeClusterer {
public:
    /// @brief Determine if there is a grapheme boundary between the previous character.
    ///
    /// @param code_point The next code point in the Unicode string
    ///
    /// @return true if there is a grapheme boundary between the previous character and code_point
    ///
    /// This includes the first time the cluster is called, as there is always a break between
    /// the start of text and end of text "virtual" tokens.
    auto is_boundary(c32 code_point) -> bool;

private:
    // Opaque internal state.
    u8 m_state { 0 };
};

/// @brief View adaptor to segment a Unicode string into grapheme clusters
template<di::concepts::InputContainer View>
requires(di::concepts::View<View> && di::concepts::ContainerOf<View, c32>)
class GraphemeClusterView {
private:
    friend struct Sentinel;
    friend struct Iterator;

    using Value = di::meta::Reconstructed<View, di::meta::ContainerIterator<View>, di::meta::ContainerIterator<View>>;

    struct Iterator
        : public di::container::IteratorBase<Iterator, di::ForwardIteratorTag, Value,
                                             di::meta::ContainerSSizeType<View>> {
    public:
        Iterator() = default;

        constexpr Iterator(GraphemeClusterView& parent, di::meta::ContainerIterator<View> base, Value next)
            : m_parent(di::addressof(parent)), m_base(di::move(base)), m_next(di::move(next)) {}

        constexpr auto base() const { return m_base; }

        constexpr auto operator*() const -> Value {
            return di::reconstruct(di::in_place_type<View>, m_base, di::end(m_next));
        }

        constexpr void advance_one() {
            m_base = di::begin(m_next);
            if (m_base != di::end(m_parent->m_base)) {
                m_base = di::end(m_next);
                if (m_base == di::end(m_parent->m_base)) {
                    m_next = di::reconstruct(di::in_place_type<View>, m_base, m_base);
                } else {
                    m_next = m_parent->find_next(m_base);
                }
            }
        }

    private:
        friend struct Sentinel;

        constexpr friend auto operator==(Iterator const& a, Iterator const& b) -> bool { return a.m_base == b.m_base; }

        GraphemeClusterView* m_parent { nullptr };
        di::meta::ContainerIterator<View> m_base;
        Value m_next;
    };

    struct Sentinel {
    public:
        Sentinel() = default;

        constexpr explicit Sentinel(GraphemeClusterView& parent) : m_base(di::end(parent.m_base)) {}

    private:
        constexpr friend auto operator==(Iterator const& a, Sentinel const& b) -> bool { return a.m_base == b.m_base; }

        di::meta::ContainerSentinel<View> m_base;
    };

public:
    GraphemeClusterView()
    requires(di::concepts::DefaultInitializable<View>)
    = default;

    constexpr GraphemeClusterView(View base) : m_base(di::move(base)) {}

    constexpr auto base() const& -> View
    requires(di::concepts::CopyConstructible<View>)
    {
        return m_base;
    }
    constexpr auto base() && -> View { return di::move(m_base); }

    constexpr auto begin() -> Iterator {
        // We need a cache to ensure begin() is O(1). Grapheme clusters
        // can be arbitrarily long.
        if (!m_cached_begin) {
            m_cached_begin = this->find_next(di::begin(m_base));
        }
        return { *this, di::begin(m_base), *m_cached_begin };
    }

    constexpr auto end() {
        if constexpr (di::concepts::CommonContainer<View>) {
            return Iterator { *this, di::end(m_base),
                              di::reconstruct(di::in_place_type<View>, di::end(m_base), di::end(m_base)) };
        } else {
            return Sentinel { *this };
        }
    }

private:
    constexpr auto find_next(di::meta::ContainerIterator<View> it) -> Value {
        auto start = it;
        auto last = it;
        auto base_end = di::end(m_base);
        if (last != base_end) {
            // Prime the grapheme clusterer with the first code point, which
            // should always be a boundary.
            auto clusterer = GraphemeClusterer {};
            clusterer.is_boundary(*last);
            ++last;
            while (last != base_end && !clusterer.is_boundary(*last)) {
                ++last;
            }
        }
        return di::reconstruct(di::in_place_type<View>, di::move(start), di::move(last));
    }

    View m_base;
    di::Optional<Value> m_cached_begin;
};

template<typename Con>
GraphemeClusterView(Con&&) -> GraphemeClusterView<di::meta::AsView<Con>>;

namespace detail {
    struct GraphemeClusterViewFunction : di::function::pipeline::EnablePipeline {
        template<typename Con>
        requires(requires(Con&& con) { GraphemeClusterView(di::forward<Con>(con)); })
        constexpr static auto operator()(Con&& con) {
            return GraphemeClusterView(di::forward<Con>(con));
            ;
        }
    };
}

constexpr inline auto grapheme_clusters = detail::GraphemeClusterViewFunction {};
}
