/*
Declares the VirtualMachine implementation class for the NetBSD Virtual Machine
Monitor platform adapter.
-------------------------------------------------------------------------------
MIT License

Copyright (c) 2019 Ivan Roberto de Oliveira

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#pragma once

#include "virt86/vm/vm.hpp"
#include "virt86/nvmm/nvmm_platform.hpp"

namespace virt86::nvmm {

class NVMMVirtualMachine : public VirtualMachine {
public:
    NVMMVirtualMachine(NVMMPlatform& platform, const VMSpecifications& specifications);  // TODO: modify the constructor to pass down handles or file descriptors as needed
    ~NVMMVirtualMachine() noexcept final;

    // Prevent copy construction and copy assignment
    NVMMVirtualMachine(const NVMMVirtualMachine&) = delete;
    NVMMVirtualMachine& operator=(const NVMMVirtualMachine&) = delete;

    // Prevent move construction and move assignment
    NVMMVirtualMachine(NVMMVirtualMachine&&) = delete;
    NVMMVirtualMachine&& operator=(NVMMVirtualMachine&&) = delete;

    // Disallow taking the address
    NVMMVirtualMachine *operator&() = delete;

    bool Initialize();

protected:
    // TODO: UnmapGuestMemoryImpl, SetGuestMemoryFlagsImpl and the dirty page
    // tracking operations are optional and may be removed if NVMM doesn't
    // support them
    MemoryMappingStatus MapGuestMemoryImpl(const uint64_t baseAddress, const uint64_t size, const MemoryFlags flags, void *memory) noexcept override;
    MemoryMappingStatus UnmapGuestMemoryImpl(const uint64_t baseAddress, const uint64_t size) noexcept override;
    MemoryMappingStatus SetGuestMemoryFlagsImpl(const uint64_t baseAddress, const uint64_t size, const MemoryFlags flags) noexcept override;

    DirtyPageTrackingStatus QueryDirtyPagesImpl(const uint64_t baseAddress, const uint64_t size, uint64_t *bitmap, const size_t bitmapSize) noexcept override;
    DirtyPageTrackingStatus ClearDirtyPagesImpl(const uint64_t baseAddress, const uint64_t size) noexcept override;

private:
    NVMMPlatform& m_platform;

    // Allow NVMMPlatform to access the constructor and Initialize()
    friend class NVMMPlatform;
};

}
