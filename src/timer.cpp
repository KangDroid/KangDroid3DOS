/**
 * Copyright (C) 2019, Jason HW Kang(Aka. KangDroid, Hyun Woo Kang)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * If any violation of this project found, please contact to kangdroid@konkuk.ac.kr
 */

#include "main.h"

#define BCM2708_ST_BASE 0x3F003000 /* BCM 2835 System Timer */

static volatile unsigned *TIMER_registers;

static void *TIMER_map;

void Timer::sleep_kangdroid(unsigned int usleep) {
    unsigned int st_time, ed_time;
    st_time = TIMER_GetSysTick();
    while (1) {
        ed_time = TIMER_GetSysTick();
        if (ed_time - st_time >= usleep) {
            break;
        }
    }
}

unsigned int Timer::TIMER_GetSysTick() {
    return TIMER_registers[1];
}

void Timer::TIMER_Del() {
    if (TIMER_map != nullptr) {
        munmap(TIMER_map, 4096);
    }
}

void Timer::TIMER_Init() {
    /* open /dev/mem */
    int TIMER_memFd;
    if ((TIMER_memFd = open("/dev/mem", O_RDWR/*|O_SYNC*/) ) < 0)
    {
        printf("can't open /dev/mem - need root ?\n");
        exit(-1);
    }

    /* mmap BCM System Timer */
    TIMER_map = mmap(
        NULL,
        4096, /* BLOCK_SIZE */
        PROT_READ /*|PROT_WRITE*/,
        MAP_SHARED,
        TIMER_memFd,
        BCM2708_ST_BASE
    );

    close(TIMER_memFd);

    if (TIMER_map == MAP_FAILED)
    {
        printf("mmap error %d\n", (int)TIMER_map);
        exit(-1);
    }
    TIMER_registers = (volatile unsigned *)TIMER_map;
}
