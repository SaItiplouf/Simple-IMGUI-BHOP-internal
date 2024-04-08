#pragma once

#define BHOP_H

#include <windows.h>
#include <cstdint>
#include <chrono>
#include <thread>

namespace offsets
{
    constexpr std::ptrdiff_t dwLocalPlayer = 0x8E3620;
    constexpr std::ptrdiff_t dwForceJump = 0x9D3450;

    constexpr std::ptrdiff_t m_iHealth = 0xc8;
    constexpr std::ptrdiff_t m_fFlags = 0x440;

    constexpr std::ptrdiff_t dwEntityList = 0x905BB8;
    constexpr std::ptrdiff_t m_iTeamNum = 0xd4;
    constexpr std::ptrdiff_t m_vecOrigin = 0x428;
}

namespace BHop {

    void BunnyHop(const HMODULE instance) noexcept {
        std::uintptr_t client = reinterpret_cast<std::uintptr_t>(GetModuleHandle("client.dll"));
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        while (true) {
            if (!GetAsyncKeyState(VK_SPACE)) 
                continue;

            // get local ply
            const auto localPlayer = *reinterpret_cast<std::uintptr_t*>(client + offsets::dwLocalPlayer);

            if (!localPlayer)
                continue;

            const auto health = *reinterpret_cast<std::uintptr_t*>(localPlayer + offsets::m_iHealth);

            if (!health)
                continue;

            const auto flags = *reinterpret_cast<std::uintptr_t*>(localPlayer + offsets::m_fFlags);

            if (flags & (1 << 0)) {
                *reinterpret_cast<std::uintptr_t*>(client + offsets::dwForceJump) = 6;
            }
            else {
                *reinterpret_cast<std::uintptr_t*>(client + offsets::dwForceJump) = 4;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // éviter la surcharge du processeur
        }
    }

}

