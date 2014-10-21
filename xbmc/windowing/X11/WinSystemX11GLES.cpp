/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */
#include "system.h"

#if defined(HAS_EGL) && defined(HAVE_X11)

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "WinSystemX11GLES.h"
#include "utils/log.h"
#include "utils/StringUtils.h"
#include "Application.h"
#include "windowing/egl/EGLWrapper.h"

CWinSystemX11GLES::CWinSystemX11GLES()
{
}

CWinSystemX11GLES::~CWinSystemX11GLES()
{
}

bool CWinSystemX11GLES::PresentRenderImpl(const CDirtyRegionList& dirty)
{
<<<<<<< HEAD
  if ((m_eglDisplay == EGL_NO_DISPLAY) || (m_eglSurface == EGL_NO_SURFACE))
    return false;
=======
  if(!SetFullScreen(fullScreen, res, false))
	return false;

  CTexture iconTexture;
  iconTexture.LoadFromFile("special://xbmc/media/icon256x256.png");

  SDL_WM_SetIcon(SDL_CreateRGBSurfaceFrom(iconTexture.GetPixels(), iconTexture.GetWidth(), iconTexture.GetHeight(), BPP, iconTexture.GetPitch(), 0xff0000, 0x00ff00, 0x0000ff, 0xff000000L), NULL);
  SDL_WM_SetCaption("XBMC Media Center", NULL);

  m_bWindowCreated = true;

  m_eglext  = " ";
  m_eglext += eglQueryString(m_eglDisplay, EGL_EXTENSIONS);
  m_eglext += " ";

  CLog::Log(LOGDEBUG, "EGL_EXTENSIONS:%s", m_eglext.c_str());

  return true;
}

bool CWinSystemX11GLES::DestroyWindow()
{
  return true;
}

bool CWinSystemX11GLES::ResizeWindow(int newWidth, int newHeight, int newLeft, int newTop)
{
  if (m_nWidth != newWidth || m_nHeight != newHeight)
  {
    m_nWidth  = newWidth;
    m_nHeight = newHeight;

#if (HAS_GLES == 2)
    int options = 0;
#else
    int options = SDL_OPENGL;
#endif
    if (m_bFullScreen)
      options |= SDL_FULLSCREEN;
    else
      options |= SDL_RESIZABLE;

    if ((m_SDLSurface = SDL_SetVideoMode(m_nWidth, m_nHeight, 0, options)))
    {
      RefreshEGLContext();
    }
  }

  CRenderSystemGLES::ResetRenderSystem(newWidth, newHeight, false, 0);

  return true;
}

bool CWinSystemX11GLES::SetFullScreen(bool fullScreen, RESOLUTION_INFO& res, bool blankOtherDisplays)
{
  m_nWidth      = res.iWidth;
  m_nHeight     = res.iHeight;
  m_bFullScreen = fullScreen;

#if defined(HAS_XRANDR)

  if(m_bFullScreen)
  {
	XOutput out;
	XMode mode;
	out.name = res.strOutput;
	mode.w   = res.iWidth;
	mode.h   = res.iHeight;
	mode.hz  = res.fRefreshRate;
	mode.id  = res.strId;
	g_xrandr.SetMode(out, mode);
  }
  else
	g_xrandr.RestoreState();

#endif

#if (HAS_GLES == 2)
    int options = 0;
#else
    int options = SDL_OPENGL;
#endif
  if (m_bFullScreen)
    options |= SDL_FULLSCREEN;
  else
    options |= SDL_RESIZABLE;
>>>>>>> 867305b97e773186eec599d958bf2d0e2769da64

  eglSwapBuffers(m_eglDisplay, m_eglSurface);

  return true;
}

void CWinSystemX11GLES::SetVSyncImpl(bool enable)
{
  eglSwapInterval(m_eglDisplay, enable ? 1 : 0);
}

bool CWinSystemX11GLES::IsExtSupported(const char* extension)
{
  if(strncmp(extension, "EGL_", 4) != 0)
    return CRenderSystemGLES::IsExtSupported(extension);

  CStdString name;

  name  = " ";
  name += extension;
  name += " ";

  return m_eglext.find(name) != std::string::npos;
}

bool CWinSystemX11GLES::CreateNewWindow(const CStdString& name, bool fullScreen, RESOLUTION_INFO& res, PHANDLE_EVENT_FUNC userFunction)
{
  if(!CWinSystemX11::CreateNewWindow(name, fullScreen, res, userFunction))
    return false;

  std::string extensions = eglQueryString(m_eglDisplay, EGL_EXTENSIONS);
  m_eglext = std::string(" ") + extensions + " ";

  CLog::Log(LOGDEBUG, "EGL_EXTENSIONS:%s", m_eglext.c_str());

  return true;
}

bool CWinSystemX11GLES::ResizeWindow(int newWidth, int newHeight, int newLeft, int newTop)
{
  m_newGlContext = false;
  CWinSystemX11::ResizeWindow(newWidth, newHeight, newLeft, newTop);
  CRenderSystemGLES::ResetRenderSystem(newWidth, newHeight, false, 0);

  if (m_newGlContext)
    g_application.ReloadSkin();

  return true;
}

bool CWinSystemX11GLES::SetFullScreen(bool fullScreen, RESOLUTION_INFO& res, bool blankOtherDisplays)
{
  m_newGlContext = false;
  CWinSystemX11::SetFullScreen(fullScreen, res, blankOtherDisplays);
  CRenderSystemGLES::ResetRenderSystem(res.iWidth, res.iHeight, fullScreen, res.fRefreshRate);

  if (m_newGlContext)
    g_application.ReloadSkin();

  return true;
}

#endif
