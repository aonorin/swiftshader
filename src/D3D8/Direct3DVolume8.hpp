// Copyright 2016 The SwiftShader Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef D3D8_Direct3DVolume8_hpp
#define D3D8_Direct3DVolume8_hpp

#include "Unknown.hpp"

#include "Surface.hpp"

#include <d3d8.h>

namespace D3D8
{
	class Direct3DDevice8;
	class Direct3DResource8;
	class Direct3DVolumeTexture8;

	class Direct3DVolume8 : public IDirect3DVolume8, public Unknown, public sw::Surface
	{
	public:
		Direct3DVolume8(Direct3DDevice8 *device, Direct3DVolumeTexture8 *container, int width, int height, int depth, D3DFORMAT format, D3DPOOL pool, bool locakble, unsigned long usage);

		~Direct3DVolume8() override;

		// Surface methods
		void *lockInternal(int x, int y, int z, sw::Lock lock, sw::Accessor client) override;
		void unlockInternal() override;

		// IUnknown methods
		long __stdcall QueryInterface(const IID &iid, void **object) override;
		unsigned long __stdcall AddRef() override;
		unsigned long __stdcall Release() override;

		// IDirect3DVolume8 methods
		long __stdcall FreePrivateData(const GUID &guid) override;
		long __stdcall GetContainer(const IID &iid, void **container) override;
		long __stdcall GetDesc(D3DVOLUME_DESC *description) override;
		long __stdcall GetDevice(IDirect3DDevice8 **device) override;
		long __stdcall GetPrivateData(const GUID &guid, void *data, unsigned long *size) override;
		long __stdcall LockBox(D3DLOCKED_BOX *lockedVolume, const D3DBOX *box, unsigned long flags) override;
		long __stdcall SetPrivateData(const GUID &guid, const void *data, unsigned long size, unsigned long flags) override;
		long __stdcall UnlockBox() override;

	private:
		static sw::Format translateFormat(D3DFORMAT format);
		static unsigned int memoryUsage(int width, int height, int depth, D3DFORMAT format);

		// Creation parameters
		Direct3DVolumeTexture8 *const container;
		const int width;
		const int height;
		const int depth;
		const D3DFORMAT format;
		const D3DPOOL pool;
		const bool lockable;
		const unsigned long usage;

		Direct3DResource8 *resource;
	};
}

#endif // D3D8_Direct3DVolume8_hpp
