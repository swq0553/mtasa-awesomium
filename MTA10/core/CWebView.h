/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*               (Shared logic for modifications)
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        core/CWebView.h
*  PURPOSE:     Web view class
*
*****************************************************************************/

#ifndef __CWEBVIEW_H
#define __CWEBVIEW_H

#include <core/CWebViewInterface.h>
#include <cef/include/cef_client.h>
#include <cef/include/cef_render_handler.h>
#include <d3d9.h>
#include <SString.h>

class CWebView : public CWebViewInterface, public CefClient, public CefLoadHandler, public CefRenderHandler
{
public:
    CWebView(IDirect3DSurface9* pD3DSurface);

    // Exported methods
    bool LoadURL(const SString& strURL);
    bool IsLoading();
    void GetURL(SString& outURL);
    void GetTitle(SString& outTitle);

    // CefClient methods
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override;
    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override;

    // CefLoadHandler methods
    virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame) override;
    virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override;
    virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) override;

    // CefRenderHandler methods
    virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override;
    virtual void OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType paintType, const CefRenderHandler::RectList& dirtyRects, const void* buffer, int width, int height) override;

private:
    CefRefPtr<CefBrowser> m_pBrowser;
    IDirect3DSurface9* m_pD3DSurface;

public:
    // Implement smartpointer methods (all Cef-classes require that since they are derived from CefBase)
    IMPLEMENT_REFCOUNTING(CWebView);
};

#endif
