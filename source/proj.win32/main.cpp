#include "pch.h"
#include "main.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("myCrimsonland");

	// FIXME: Looks like cocos bug, black screen on 1024*768 res
	eglView->setFrameSize(1024, 768);

	// FIXME: hack
	eglView->setFrameSize(1024, 769);

    //eglView->setFrameSize(2048, 1536);
    // The resolution of ipad3 is very large. In general, PC's resolution is smaller than it.
    // So we need to invoke 'setFrameZoomFactor'(only valid on desktop(win32, mac, linux)) to make the window smaller.
    eglView->setFrameZoomFactor(1.0f);
    return CCApplication::sharedApplication()->run();
}
