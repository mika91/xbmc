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

#pragma once

<<<<<<< HEAD
#if defined(HAS_GLX) || defined(HAS_EGL) || defined(TARGET_DARWIN)
=======
#if defined(HAS_GLX) || defined(TARGET_DARWIN)
>>>>>>> 867305b97e773186eec599d958bf2d0e2769da64
class IDispResource
{
public:
  virtual ~IDispResource() {};
  virtual void OnLostDevice() {};
  virtual void OnResetDevice() {};
  virtual void OnAppFocusChange(bool focus) {};
};

#endif
