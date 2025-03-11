#include "ursRdgUtil.h"

#include <RenderGraph.h>
#include <RenderTargetPool.h>
#include <Engine/TextureRenderTarget2D.h>

#if 0
#pragma mark --- ursRdgUtil-Impl ---
#endif // 0
#if 1

FRDGBufferRef 
ursRdgUtil::createStructuredBufferWithSrv(FRDGBufferSRV** outSrv, FRDGBuilder& rdgBuilder, const TCHAR* name, uint32 elementByteSize, uint32 elementCount, ERDGInitialDataFlags InitialDataFlags)
{
	FRDGBufferDesc desc = FRDGBufferDesc::CreateStructuredDesc(elementByteSize, elementCount);
	//*outBuf = rdgBuilder.CreateBuffer(desc, name);

	FRDGBufferRef buf = rdgBuilder.CreateBuffer(desc, name);
	*outSrv = rdgBuilder.CreateSRV(buf);
	return buf;
}

FRDGBufferRef 
ursRdgUtil::createStructuredBufferWithUav(FRDGBufferUAV** outUav, FRDGBuilder& rdgBuilder, const TCHAR* name, uint32 elementByteSize, uint32 elementCount, ERDGInitialDataFlags InitialDataFlags)
{
	FRDGBufferDesc desc = FRDGBufferDesc::CreateStructuredDesc(elementByteSize, elementCount);
	//*outBuf = rdgBuilder.CreateBuffer(desc, name);

	FRDGBufferRef buf = rdgBuilder.CreateBuffer(desc, name);
	*outUav = rdgBuilder.CreateUAV(buf);
	return buf;
}

FRDGBufferRef 
ursRdgUtil::registerExternalBufferWithUav(FRDGBufferUAV** outUav, FRDGBuilder& rdgBuilder, TRefCountPtr<FRDGPooledBuffer>& pooledBuf)
{
	auto* buf = rdgBuilder.RegisterExternalBuffer(pooledBuf);
	*outUav = rdgBuilder.CreateUAV(buf);
	return buf;
}

FRDGBufferRef 
ursRdgUtil::registerExternalBufferWithSrv(FRDGBufferSRV** outSrv, FRDGBuilder& rdgBuilder, TRefCountPtr<FRDGPooledBuffer>& pooledBuf)
{
	auto* buf = rdgBuilder.RegisterExternalBuffer(pooledBuf);
	*outSrv = rdgBuilder.CreateSRV(buf);
	return buf;
}

FRDGTextureRef 
ursRdgUtil::createTexture2DWithUav(FRDGTextureUAV*& outUav, FRDGBuilder& rdgBuilder, const TCHAR* name, FIntPoint extent, EPixelFormat format, FClearValueBinding clearValue, ETextureCreateFlags flags)
{
	auto desc = FRDGTextureDesc::Create2D(extent, format, clearValue, flags);

	FRDGTextureRef tex = rdgBuilder.CreateTexture(desc, name);
	outUav = rdgBuilder.CreateUAV(tex);
	return tex;
}

FRDGTextureUAV* 
ursRdgUtil::createUavWithTexture2D(FRDGTextureRef& outTex, FRDGBuilder& rdgBuilder, const TCHAR* name, FIntPoint extent, EPixelFormat format, FClearValueBinding clearValue, ETextureCreateFlags flags)
{
	FRDGTextureUAV* uav = nullptr;
	outTex = createTexture2DWithUav(uav, rdgBuilder, name, extent, format, clearValue, flags);
	return uav;
}


#endif