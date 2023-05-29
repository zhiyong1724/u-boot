#!/bin/bash
openocd -f ./cmsis-dap.cfg -f ./stm32h7x.cfg -c "program u-boot.bin 0x8000000 verify reset exit"