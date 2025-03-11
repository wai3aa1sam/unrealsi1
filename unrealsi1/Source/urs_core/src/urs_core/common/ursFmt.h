#pragma once

#include "urs_core/marco/urs_core_marco_common.h"

#define FMT_HEADER_ONLY 1

URS_DISABLE_ALL_WARNINGS()
#include <fmt/core.h>

/*
~ reference:
	- https://github.com/SimpleTalkCpp/SimpleTalkCpp_UnrealExamples/blob/main/Unreal_Cpp/MyProject/Source/MyProject/Common/MyFormat.h
*/

template<class T> inline
FName ursEnumToFName(const T& enumValue) 
{
	return StaticEnum<T>()->GetNameByValue(static_cast<int64>(enumValue));
}

class UNREALSI1_API ursFormat_FStringBackInserter 
{
	using This = ursFormat_FStringBackInserter;
public:
	ursFormat_FStringBackInserter() = default;
	explicit ursFormat_FStringBackInserter(FString& s) noexcept : _s(&s) {}

	This& operator=(const char& _Val)		{ _s->AppendChar(_Val); return *this; }
	This& operator=(typename char && _Val)	{ _s->AppendChar(std::move(_Val)); return *this; }
	This& operator=(const wchar_t& _Val)	{ _s->AppendChar(_Val); return *this; }

	This& operator*()		noexcept { return *this; }
	This& operator++()		noexcept { return *this; }
	This  operator++(int)	noexcept { return *this; }

	FString* _s;
};

template <> struct fmt::detail::is_output_iterator<ursFormat_FStringBackInserter, char> : std::true_type {};

template<class CTX, class... ARGS> inline
auto
fmt_format_to(CTX&& ctx, fmt::string_view fmt, const ARGS&... args)
{
	//return fmt::vformat_to(std::move(ctx), fmt, fmt::make_format_args(std::forward<ARGS>(args)...));
	//return fmt::format_to(std::move(ctx), fmt::runtime(fmt), std::forward<ARGS>(args)...);
	return fmt::format_to(std::move(ctx), fmt::runtime(fmt), args...);
}

template<class... ARGS> inline
void 
ursFormatTo(FString& outStr, const char* format_str, ARGS&&... args) 
{
	try 
	{
		fmt_format_to(ursFormat_FStringBackInserter(outStr), format_str, std::forward<ARGS>(args)...);

		//fmt_format_to(ursFormat_FStringBackInserter(outStr), format_str, args...);
		//fmt::format_to(ursFormat_FStringBackInserter(outStr), format_str, args...);
		//fmt::format_to(ursFormat_FStringBackInserter(outStr), fmt::runtime(format_str), fmt::make_format_args(args...));
		//fmt::vformat_to(ursFormat_FStringBackInserter(outStr), format_str, fmt::make_format_args(args...));
	} 
	catch (...) 
	{
		UE_LOG(LogTemp, Error, TEXT("Exception in ursFormat"));
	}
}

template<class... ARGS> inline
FString ursFormat(const char* format_str, ARGS&& ... args) {
	FString tmp;
	ursFormatTo(tmp, format_str, std::forward<ARGS>(args)...);
	return tmp;
}

template<class... ARGS> inline
FText ursFormatText(const char* format_str, ARGS&& ... args) {
	FString tmp;
	ursFormatTo(tmp, format_str, std::forward<ARGS>(args)...);
	return FText::FromString(tmp);
}

template<class... ARGS> inline
FName ursFormatName(const char* format_str, ARGS&& ... args) {
	FString tmp;
	ursFormatTo(tmp, format_str, std::forward<ARGS>(args)...);
	return FName(tmp);
}

struct ursFormatterBase {
	auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
};

template<>
struct fmt::formatter<wchar_t> : public ursFormatterBase {
	auto format(const wchar_t& v, fmt::format_context& ctx) const {
		return ctx.out();
	}
};

template<>
struct fmt::formatter<FString> : public ursFormatterBase {
	auto format(const FString& v, fmt::format_context& ctx) const {
		//		const auto& arr = v.GetCharArray();
		//		fmt::string_view view(arr.GetData(), arr.Num());
		auto it = *ctx.out();
		for (const auto& c :v.GetCharArray()) {
			it = static_cast<char>(c);
			it++;
		}
		return ctx.out();
	}
};


template <typename T>
struct fmt::formatter<T, char, std::enable_if_t<std::is_enum_v<T> > > : fmt::formatter<FString> {
	auto format(const T& v, fmt::format_context& ctx) const 
	{
		return fmt::formatter<FString>::format(ursEnumToFName(v).ToString(), ctx);
	}
};

template<>
struct fmt::formatter<FName> : fmt::formatter<FString> {
	auto format(const FName& v, fmt::format_context& ctx) const {
		return fmt::formatter<FString>::format(v.ToString(), ctx);
	}
};

template<>
struct fmt::formatter<FSmartName> : fmt::formatter<FString> {
	auto format(const FSmartName& v, fmt::format_context& ctx) const {
		return fmt::formatter<FString>::format(v.DisplayName.ToString(), ctx);
	}
};

template<>
struct fmt::formatter<FText> : fmt::formatter<FString> {
	auto format(const FText& v, fmt::format_context& ctx) const {
		return fmt::formatter<FString>::format(v.ToString(), ctx);
	}
};

template<class T>
struct fmt::formatter<UE::Math::TVector2<T> > : public ursFormatterBase {
	auto format(const UE::Math::TVector2<T>& v, fmt::format_context& ctx) const {
		return fmt::format_to(ctx.out(), "[{}, {}]", v.X, v.Y);
	}
};

template<class T>
struct fmt::formatter<UE::Math::TVector<T> > : public ursFormatterBase {
	auto format(const UE::Math::TVector<T>& v, fmt::format_context& ctx) const {
		return fmt::format_to(ctx.out(), "[{}, {}, {}]", v.X, v.Y, v.Z);
	}
};

template<class T>
struct fmt::formatter<UE::Math::TVector4<T> > : public ursFormatterBase {
	auto format(const UE::Math::TVector4<T>& v, fmt::format_context& ctx) const {
		return fmt::format_to(ctx.out(), "[{}, {}, {}, {}]", v.X, v.Y, v.Z, v.W);
	}
};

template<>
struct fmt::formatter<FVector_NetQuantize> : public fmt::formatter<FVector> {
	auto format(const FVector_NetQuantize& v, fmt::format_context& ctx) const {
		return fmt::formatter<FVector>::format(v, ctx);
	}
};

template<>
struct fmt::formatter<FRotator> : public ursFormatterBase {
	auto format(const FRotator& v, fmt::format_context& ctx) const {
		return fmt::format_to(ctx.out(), "[{}, {}, {}]", v.Pitch, v.Yaw, v.Roll);
	}
};

template<class T>
struct fmt::formatter<UE::Math::TIntPoint<T> > : public ursFormatterBase {
	auto format(const UE::Math::TIntPoint<T>& v, fmt::format_context& ctx) const {
		return fmt::format_to(ctx.out(), "[{}, {}]", v.X, v.Y);
	}
};

template<>
struct fmt::formatter<FKey> : public fmt::formatter<FString> {
	auto format(const FKey& v, fmt::format_context& ctx) const {
		return fmt::formatter<FString>::format(v.ToString(), ctx);
	}
};

template<>
struct fmt::formatter<AActor> : public ursFormatterBase 
{
	auto format(const AActor& v, fmt::format_context& ctx) const 
	{
		auto actorName = &v ? v.GetName() : "";
		return fmt_format_to(ctx.out(), "Actor: {}", actorName);
	}
};

template<class T, class ALLOC>
struct fmt::formatter<TArray<T, ALLOC> > : public ursFormatterBase {
	auto format(const TArray<T, ALLOC>& v, fmt::format_context& ctx) const {

		if (!v.IsEmpty())
			fmt_format_to(ctx.out(), "{}", v[0]);

		if (v.Num() == 1)
			return ctx.out();

		for (size_t i = 1; i < v.Num(); i++)
		{
			auto& e = v[i];
			fmt_format_to(ctx.out(), ", {}", e);
		}
		return ctx.out();
	}
};

URS_RESTORE_ALL_WARNINGS()
