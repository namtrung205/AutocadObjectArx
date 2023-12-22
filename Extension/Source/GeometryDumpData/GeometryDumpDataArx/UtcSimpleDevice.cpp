//#include "stdafx.h"
//#include "acgs.h"
//#include "UtcSimpleDevice.h"
//
//UtcSimpleDevice::UtcSimpleDevice()
//{
//}
//
//UtcSimpleDevice::~UtcSimpleDevice()
//{
//}
//
//AcGsGraphicsKernel& UtcSimpleDevice::graphicsKernel(void)
//{
//	// TODO: insert return statement here
//	return AcGsGraphicsKernel();
//}
//
//void UtcSimpleDevice::invalidate(void)
//{
//}
//
//void UtcSimpleDevice::invalidate(const AcGsDCRect& rect)
//{
//}
//
//bool UtcSimpleDevice::isValid(void) const
//{
//	return false;
//}
//
//void UtcSimpleDevice::update(AcGsDCRect* pUpdatedRect = nullptr)
//{
//}
//
//void UtcSimpleDevice::onSize(int width, int height)
//{
//}
//
//void UtcSimpleDevice::onRealizeForegroundPalette(void)
//{
//}
//
//void UtcSimpleDevice::onRealizeBackgroundPalette(void)
//{
//}
//
//void UtcSimpleDevice::onDisplayChange(int nBitsPerPixel, int nXRes, int nYRes)
//{
//}
//
//bool UtcSimpleDevice::add(AcGsView* view)
//{
//	return false;
//}
//
//bool UtcSimpleDevice::erase(AcGsView* view)
//{
//	return false;
//}
//
//void UtcSimpleDevice::eraseAll(void)
//{
//}
//
//bool UtcSimpleDevice::setBackgroundColor(AcGsColor color)
//{
//	return false;
//}
//
//AcGsColor UtcSimpleDevice::getBackgroundColor(void)
//{
//	return AcGsColor();
//}
//
//void UtcSimpleDevice::setLogicalPalette(const AcGsColor* palette, int nCount)
//{
//}
//
//void UtcSimpleDevice::setPhysicalPalette(const AcGsColor* palette, int nCount)
//{
//}
//
//void UtcSimpleDevice::getSnapShot(Atil::Image* pOutput, AcGsDCPoint const& offset)
//{
//}
//
//void UtcSimpleDevice::setDeviceRenderer(RendererType type)
//{
//}
//
//AcGsDevice::RendererType UtcSimpleDevice::getDeviceRenderer(void)
//{
//	return RendererType();
//}
//
//void UtcSimpleDevice::setRenderInterrupter(AcGsRenderInterrupter* pInterrupter)
//{
//}
//
//AcGsRenderInterrupter* UtcSimpleDevice::getRenderInterrupter(void) const
//{
//	return nullptr;
//}
//
//void UtcSimpleDevice::setDisplayUpdateSuppressed(bool bSuppressed)
//{
//}
//
//void UtcSimpleDevice::invalidate(AcGsModel::RenderType pane)
//{
//}
//
//void UtcSimpleDevice::invalidate(const AcGsDCRect& rect, AcGsModel::RenderType pane)
//{
//}
//
//void UtcSimpleDevice::update(AcGsDCRect* pUpdatedRect, GS::SyncBehavior sync)
//{
//}
//
//Atil::Image* UtcSimpleDevice::createSnapshot(const AcGsDCPoint& offset, const AcGsDCRect& imageDim, GS::ImageDataFormat format, GS::ImageOrientation orientation)
//{
//	return nullptr;
//}
//
//int UtcSimpleDevice::getMaxDeviceWidth(void)
//{
//	return 0;
//}
//
//int UtcSimpleDevice::getMaxDeviceHeight(void)
//{
//	return 0;
//}
//
//void UtcSimpleDevice::setDesiredFrameRate(float frameRate)
//{
//}
//
//void UtcSimpleDevice::pauseInteractiveRender(void)
//{
//}
//
//void UtcSimpleDevice::resumeInteractiveRender(void)
//{
//}
//
//void UtcSimpleDevice::postRenderProgressCheckingReqeust()
//{
//}
//
//AcGsDevice::EnableIRResult UtcSimpleDevice::beginInteractiveRender(AcGsRenderProgressMonitor* pProgressMonitor)
//{
//	return EnableIRResult();
//}
//
//void UtcSimpleDevice::endInteractiveRender(void)
//{
//}
//
//bool UtcSimpleDevice::isRendering(void) const
//{
//	return false;
//}
//
//void UtcSimpleDevice::setFontKerningDisplay(bool bDisplay)
//{
//}
