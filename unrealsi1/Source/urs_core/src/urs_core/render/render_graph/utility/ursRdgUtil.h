#pragma once

#include "urs_core/render/common/urs_render_common.h"

#if 0
#pragma mark --- ursRdgUtil-Decl ---
#endif // 0
#if 1

struct URS_CORE_API ursRdgUtil
{
public:
	template<class T, class TAlloc>
	static FRDGBufferRef createStructuredBufferWithSrv(FRDGBufferSRV** outSrv, FRDGBuilder& rdgBuilder, const TCHAR* name, const TArray<T, TAlloc>& data, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None);
	static FRDGBufferRef createStructuredBufferWithSrv(FRDGBufferSRV** outSrv, FRDGBuilder& rdgBuilder, const TCHAR* name, uint32 elementByteSize, uint32 elementCount, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None);

	template<class T, class TAlloc>
	static FRDGBufferRef createStructuredBufferWithUav(FRDGBufferUAV** outUav, FRDGBuilder& rdgBuilder, const TCHAR* name, const TArray<T, TAlloc>& data, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None);
	static FRDGBufferRef createStructuredBufferWithUav(FRDGBufferUAV** outUav, FRDGBuilder& rdgBuilder, const TCHAR* name, uint32 elementByteSize, uint32 elementCount, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None);

	static FRDGBufferRef registerExternalBufferWithUav(FRDGBufferUAV** outUav, FRDGBuilder& rdgBuilder, TRefCountPtr<FRDGPooledBuffer>& pooledBuf);
	static FRDGBufferRef registerExternalBufferWithSrv(FRDGBufferSRV** outSrv, FRDGBuilder& rdgBuilder, TRefCountPtr<FRDGPooledBuffer>& pooledBuf);
};

template<class T, class TAlloc> inline
FRDGBufferRef 
ursRdgUtil::createStructuredBufferWithSrv(FRDGBufferSRV** outSrv, FRDGBuilder& rdgBuilder, const TCHAR* name, const TArray<T, TAlloc>& data, ERDGInitialDataFlags InitialDataFlags)
{
	// using ElementType = decltype(data)::ElementType;
	FRDGBufferRef buf = CreateStructuredBuffer(rdgBuilder, name, data, InitialDataFlags);
	FRDGBufferSRVRef bufSrv = rdgBuilder.CreateSRV(buf, PF_R32_UINT);
	*outSrv = bufSrv;
	return buf;
}

template<class T, class TAlloc> inline
FRDGBufferRef 
ursRdgUtil::createStructuredBufferWithUav(FRDGBufferUAV** outUav, FRDGBuilder& rdgBuilder, const TCHAR* name, const TArray<T, TAlloc>& data, ERDGInitialDataFlags InitialDataFlags)
{
	// using ElementType = decltype(data)::ElementType;
	FRDGBufferRef buf = CreateStructuredBuffer(rdgBuilder, name, data, InitialDataFlags);
	FRDGBufferUAVRef bufUav = rdgBuilder.CreateUAV(buf, PF_R32_UINT);
	*outUav = bufUav;
	return buf;
}

#endif