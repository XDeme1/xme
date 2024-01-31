#pragma once
#include <functional>
#include <memory>
#include <array>
#include <concepts>

namespace xme {
template<typename T>
class Delegate;

template<typename R, typename... Args>
class Delegate<R(Args...)> {
public:
    class Unknown;
    union AnyCallable {
        void* object;              // Functors
        const void* const_object;  // Const Functors
        void (*ptr)();
        void (Unknown::*member_ptr)();
    };

    struct AnyData {
        [[nodiscard]]
        inline constexpr auto access() noexcept -> void* {
            return data.data();
        }

        [[nodiscard]]
        inline constexpr auto access() const noexcept -> const void* {
            return data.data();
        }

        template<typename T>
        [[nodiscard]]
        inline constexpr auto access() noexcept -> T& {
            return *static_cast<T*>(access());
        }

        template<typename T>
        [[nodiscard]]
        inline constexpr auto access() const noexcept -> const T& {
            return *static_cast<const T*>(access());
        }

        std::array<std::byte, sizeof(AnyCallable)> data;
    };

    enum class EOperation {
        copy,
        destroy,
    };

    template<typename Functor>
    struct FunctorManager {
        static constexpr std::size_t max_size  = sizeof(AnyCallable);
        static constexpr std::size_t max_align = alignof(AnyCallable);
        static constexpr bool is_local_storage =
          sizeof(Functor) <= max_size && alignof(Functor) <= max_align;

        static constexpr auto invoke(const AnyData& functor, Args... args) -> R {
            return std::invoke(*handle(functor), std::forward<Args>(args)...);
        }

        static constexpr auto handle(const AnyData& functor) -> Functor* {
            if constexpr(is_local_storage) {
                const Functor& f = *static_cast<const Functor*>(functor.access());
                return const_cast<Functor*>(std::addressof(f));
            }
            return functor.template access<Functor*>();
        }

        template<bool local = is_local_storage, typename Fn>
        static constexpr void create_functor(AnyData& f, Fn&& fn) {
            if constexpr(local) {
                ::new(f.access()) Functor{std::forward<Fn>(fn)};
            }
            else {
                f.template access<Functor*>() = new Functor(std::forward<Fn>(fn));
            }
        }

        template<bool local = is_local_storage>
        static constexpr void destroy_functor(AnyData& f) noexcept {
            if constexpr(local) {
                static_cast<Functor*>(f.access())->~Functor();
            }
            else {
                delete f.template access<Functor*>();
            }
        }

        static constexpr void destroy(AnyData& f) noexcept { destroy_functor<is_local_storage>(f); }

        static constexpr void manager(AnyData& dest, AnyData& source, EOperation op) {
            switch(op) {
            case EOperation::copy:    create_functor(dest, *handle(source)); break;
            case EOperation::destroy: destroy(dest); break;
            }
        }
    };

public:
    constexpr Delegate() = default;

    constexpr Delegate(const Delegate& other) {
        if(static_cast<bool>(other)) {
            other.m_manager(m_storage, other.m_storage, EOperation::copy);
            m_callable = other.m_callable;
            m_manager  = other.m_manager;
        }
    }

    constexpr Delegate(Delegate&& other) noexcept : m_callable(other.m_callable) {
        if(static_cast<bool>(other)) {
            m_manager       = other.m_manager;
            m_storage       = other.m_storage;
            other.m_manager = nullptr;
        }
    }

    template<typename Fn>
        requires(!std::same_as<Delegate, std::decay_t<Fn>>)
    constexpr Delegate(Fn&& fn) {
        using Manager = FunctorManager<Fn>;
        if(!is_empty_function(fn)) {
            Manager::create_functor(m_storage, std::forward<Fn>(fn));
            m_callable = &FunctorManager<Fn>::invoke;
            m_manager  = &FunctorManager<Fn>::manager;
        }
    }

    constexpr ~Delegate() noexcept {
        if(m_manager) m_manager(m_storage, m_storage, EOperation::destroy);
    }

    explicit constexpr operator bool() const noexcept { return !!m_manager; }

    constexpr auto operator=(const Delegate& other) noexcept -> Delegate& {
        Delegate(other).swap(*this);
        return *this;
    }

    constexpr auto operator=(Delegate&& other) noexcept -> Delegate& {
        Delegate(std::move(other)).swap(*this);
        return *this;
    }

    constexpr auto operator=(std::nullptr_t) noexcept -> Delegate& {
        if(m_manager) {
            m_manager(m_storage, m_storage, EOperation::destroy);
            m_manager  = nullptr;
            m_callable = nullptr;
        }
        return *this;
    }

    template<typename Fn>
        requires(!std::same_as<Delegate, std::decay_t<Fn>>)
    constexpr auto operator=(Fn&& other) noexcept -> Delegate& {
        Delegate(std::forward<Fn>(other)).swap(*this);
        return *this;
    }

    constexpr auto operator()(Args... args) const -> R {
        if(!m_manager) {
            throw std::bad_function_call();
        }
        return m_callable(m_storage, std::forward<Args>(args)...);
    }

    constexpr void swap(Delegate& other) noexcept {
        std::ranges::swap(m_storage, other.m_storage);
        std::ranges::swap(m_callable, other.m_callable);
        std::ranges::swap(m_manager, other.m_manager);
    }

    template<typename Functor>
    constexpr auto handle() const noexcept -> const Functor* {
        if(m_manager == &FunctorManager<Functor>::manager) {
            return static_cast<const Functor*>(m_storage.access());
        }
        return nullptr;
    }

    //! Pointer to function
    constexpr static bool is_empty_function(auto* fn) { return fn == nullptr; }

    //! Pointer to member function
    template<typename C, typename T>
    constexpr static bool is_empty_function(T C::*ptr) {
        return ptr == nullptr;
    }

    //! Functors.
    //! Lambdas are never null and functors need to handle nullptr themselves
    constexpr static bool is_empty_function(const auto&) { return false; }

private:
    AnyData m_storage{};
    R (*m_callable)(const AnyData&, Args...)          = nullptr;
    void (*m_manager)(AnyData&, AnyData&, EOperation) = nullptr;
};
}  // namespace xme
