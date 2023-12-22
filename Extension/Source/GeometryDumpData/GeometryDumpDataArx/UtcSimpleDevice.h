//#pragma once
//#include "gs.h"
//
//class UtcSimpleDevice :AcGsDevice
//{
//public:
//	UtcSimpleDevice();
//	~UtcSimpleDevice();
//
//private:
//
//
//	// Inherited via AcGsDevice
//	virtual AcGsGraphicsKernel& graphicsKernel(void) override;
//
//	virtual void invalidate(void) override;
//
//	virtual void invalidate(const AcGsDCRect& rect) override;
//
//	virtual bool isValid(void) const override;
//
//	virtual void update(AcGsDCRect* pUpdatedRect) override;
//
//	virtual void onSize(int width, int height) override;
//
//	virtual void onRealizeForegroundPalette(void) override;
//
//	virtual void onRealizeBackgroundPalette(void) override;
//
//	virtual void onDisplayChange(int nBitsPerPixel, int nXRes, int nYRes) override;
//
//	virtual bool add(AcGsView* view) override;
//
//	virtual bool erase(AcGsView* view) override;
//
//	virtual void eraseAll(void) override;
//
//	virtual bool setBackgroundColor(AcGsColor color) override;
//
//	virtual AcGsColor getBackgroundColor(void) override;
//
//	virtual void setLogicalPalette(const AcGsColor* palette, int nCount) override;
//
//	virtual void setPhysicalPalette(const AcGsColor* palette, int nCount) override;
//
//	virtual void getSnapShot(Atil::Image* pOutput, AcGsDCPoint const& offset) override;
//
//	virtual void setDeviceRenderer(RendererType type) override;
//
//	virtual RendererType getDeviceRenderer(void) override;
//
//	virtual void setRenderInterrupter(AcGsRenderInterrupter* pInterrupter) override;
//
//	virtual AcGsRenderInterrupter* getRenderInterrupter(void) const override;
//
//	virtual void setDisplayUpdateSuppressed(bool bSuppressed) override;
//
//	virtual void invalidate(AcGsModel::RenderType pane) override;
//
//	virtual void invalidate(const AcGsDCRect& rect, AcGsModel::RenderType pane) override;
//
//	virtual void update(AcGsDCRect* pUpdatedRect, GS::SyncBehavior sync) override;
//
//	virtual Atil::Image* createSnapshot(const AcGsDCPoint& offset, const AcGsDCRect& imageDim, GS::ImageDataFormat format, GS::ImageOrientation orientation) override;
//
//	virtual int getMaxDeviceWidth(void) override;
//
//	virtual int getMaxDeviceHeight(void) override;
//
//	virtual void setDesiredFrameRate(float frameRate) override;
//
//	virtual void pauseInteractiveRender(void) override;
//
//	virtual void resumeInteractiveRender(void) override;
//
//	virtual void postRenderProgressCheckingReqeust() override;
//
//	virtual EnableIRResult beginInteractiveRender(AcGsRenderProgressMonitor* pProgressMonitor) override;
//
//	virtual void endInteractiveRender(void) override;
//
//	virtual bool isRendering(void) const override;
//
//	virtual void setFontKerningDisplay(bool bDisplay) override;
//
//};
