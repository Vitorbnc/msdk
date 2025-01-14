/******************************************************************************
 * Copyright (C) 2023 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 ******************************************************************************/

#include "uart.h"
#include "mxc_device.h"
#include "mxc_pins.h"
#include "mxc_assert.h"
#include "uart_reva.h"
#include "uart_common.h"
#include "dma.h"

void MXC_UART_DMACallback(int ch, int error)
{
    MXC_UART_RevA_DMACallback(ch, error);
}

void MXC_UART_AsyncCallback(mxc_uart_regs_t *uart, int retVal)
{
    MXC_UART_RevA_AsyncCallback((mxc_uart_reva_regs_t *)uart, retVal);
}

void MXC_UART_TxAsyncCallback(mxc_uart_regs_t *uart, int retVal)
{
    MXC_UART_RevA_TxAsyncCallback((mxc_uart_reva_regs_t *)uart, retVal);
}

void MXC_UART_RxAsyncCallback(mxc_uart_regs_t *uart, int retVal)
{
    MXC_UART_RevA_RxAsyncCallback((mxc_uart_reva_regs_t *)uart, retVal);
}

void MXC_UART_AsyncStop(mxc_uart_regs_t *uart)
{
    MXC_UART_RevA_AsyncStop((mxc_uart_reva_regs_t *)uart);
}

void MXC_UART_TxAsyncStop(mxc_uart_regs_t *uart)
{
    MXC_UART_RevA_TxAsyncStop((mxc_uart_reva_regs_t *)uart);
}

void MXC_UART_RxAsyncStop(mxc_uart_regs_t *uart)
{
    MXC_UART_RevA_RxAsyncStop((mxc_uart_reva_regs_t *)uart);
}

int MXC_UART_Init(mxc_uart_regs_t *uart, unsigned int baud, sys_map_t map)
{
#ifndef MSDK_NO_GPIO_CLK_INIT
    int retval;

    retval = MXC_UART_Shutdown(uart);

    if (retval) {
        return retval;
    }

    switch (MXC_UART_GET_IDX(uart)) {
    case 0:
        if (map == MAP_A) {
            MXC_GPIO_Config(&gpio_cfg_uart0a);
        } else {
            MXC_GPIO_Config(&gpio_cfg_uart0b);
        }
        MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_UART0);
        break;

    case 1:
        if (map == MAP_A) {
            MXC_GPIO_Config(&gpio_cfg_uart1a);
        } else {
            MXC_GPIO_Config(&gpio_cfg_uart1b);
        }
        MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_UART1);
        break;

    case 2:
        if (map == MAP_A) {
            MXC_GPIO_Config(&gpio_cfg_uart2a);
        } else {
            MXC_GPIO_Config(&gpio_cfg_uart2b);
        }
        MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_UART2);
        break;
    }
#else
    (void)map;
#endif // MSDK_NO_GPIO_CLK_INIT

    return MXC_UART_RevA_Init((mxc_uart_reva_regs_t *)uart, baud);
}

int MXC_UART_Shutdown(mxc_uart_regs_t *uart)
{
    switch (MXC_UART_GET_IDX(uart)) {
    case 0:
        MXC_SYS_Reset_Periph(MXC_SYS_RESET_UART0);
        MXC_SYS_ClockDisable(MXC_SYS_PERIPH_CLOCK_UART0);
        break;

    case 1:
        MXC_SYS_Reset_Periph(MXC_SYS_RESET_UART1);
        MXC_SYS_ClockDisable(MXC_SYS_PERIPH_CLOCK_UART1);
        break;

    case 2:
        MXC_SYS_Reset_Periph(MXC_SYS_RESET_UART2);
        MXC_SYS_ClockDisable(MXC_SYS_PERIPH_CLOCK_UART2);
        break;
    }

    return E_NO_ERROR;
}

int MXC_UART_ReadyForSleep(mxc_uart_regs_t *uart)
{
    return MXC_UART_RevA_ReadyForSleep((mxc_uart_reva_regs_t *)uart);
}

int MXC_UART_SetFrequency(mxc_uart_regs_t *uart, unsigned int baud)
{
    return MXC_UART_RevA_SetFrequency((mxc_uart_reva_regs_t *)uart, baud);
}

int MXC_UART_GetFrequency(mxc_uart_regs_t *uart)
{
    return MXC_UART_RevA_GetFrequency((mxc_uart_reva_regs_t *)uart);
}

int MXC_UART_SetDataSize(mxc_uart_regs_t *uart, int dataSize)
{
    return MXC_UART_RevA_SetDataSize((mxc_uart_reva_regs_t *)uart, dataSize);
}

int MXC_UART_SetStopBits(mxc_uart_regs_t *uart, mxc_uart_stop_t stopBits)
{
    return MXC_UART_RevA_SetStopBits((mxc_uart_reva_regs_t *)uart, stopBits);
}

int MXC_UART_SetParity(mxc_uart_regs_t *uart, mxc_uart_parity_t parity)
{
    return MXC_UART_RevA_SetParity((mxc_uart_reva_regs_t *)uart, parity);
}

int MXC_UART_SetFlowCtrl(mxc_uart_regs_t *uart, mxc_uart_flow_t flowCtrl, int rtsThreshold,
                         sys_map_t map)
{
    switch (MXC_UART_GET_IDX(uart)) {
    case 0:
        if (map == MAP_A) {
            MXC_GPIO_Config(&gpio_cfg_uart0a_flow);
        } else {
            MXC_GPIO_Config(&gpio_cfg_uart0b_flow);
        }
        break;

    case 1:
        if (map == MAP_A) {
            MXC_GPIO_Config(&gpio_cfg_uart1a_flow);
        } else {
            MXC_GPIO_Config(&gpio_cfg_uart1b_flow);
        }
        break;

    case 2:
        if (map == MAP_A) {
            MXC_GPIO_Config(&gpio_cfg_uart2a_flow);
        } else {
            MXC_GPIO_Config(&gpio_cfg_uart2b_flow);
        }
        break;
    }

    return MXC_UART_RevA_SetFlowCtrl((mxc_uart_reva_regs_t *)uart, flowCtrl, rtsThreshold);
}

int MXC_UART_SetClockSource(mxc_uart_regs_t *uart, int usePCLK)
{
    return MXC_UART_RevA_SetClockSource((mxc_uart_reva_regs_t *)uart, usePCLK);
}

int MXC_UART_SetNullModem(mxc_uart_regs_t *uart, int nullModem)
{
    return MXC_UART_RevA_SetNullModem((mxc_uart_reva_regs_t *)uart, nullModem);
}

int MXC_UART_SendBreak(mxc_uart_regs_t *uart)
{
    return MXC_UART_RevA_SendBreak((mxc_uart_reva_regs_t *)uart);
}

int MXC_UART_GetActive(mxc_uart_regs_t *uart)
{
    return MXC_UART_RevA_GetActive((mxc_uart_reva_regs_t *)uart);
}

int MXC_UART_AbortTransmission(mxc_uart_regs_t *uart)
{
    return MXC_UART_RevA_AbortTransmission((mxc_uart_reva_regs_t *)uart);
}

int MXC_UART_ReadCharacterRaw(mxc_uart_regs_t *uart)
{
    return MXC_UART_RevA_ReadCharacterRaw((mxc_uart_reva_regs_t *)uart);
}

int MXC_UART_WriteCharacterRaw(mxc_uart_regs_t *uart, uint8_t character)
{
    return MXC_UART_RevA_WriteCharacterRaw((mxc_uart_reva_regs_t *)uart, character);
}

int MXC_UART_ReadCharacter(mxc_uart_regs_t *uart)
{
    return MXC_UART_Common_ReadCharacter(uart);
}

int MXC_UART_WriteCharacter(mxc_uart_regs_t *uart, uint8_t character)
{
    return MXC_UART_Common_WriteCharacter(uart, character);
}

int MXC_UART_Read(mxc_uart_regs_t *uart, uint8_t *buffer, int *len)
{
    return MXC_UART_RevA_Read((mxc_uart_reva_regs_t *)uart, buffer, len);
}

int MXC_UART_Write(mxc_uart_regs_t *uart, uint8_t *byte, int *len)
{
    return MXC_UART_RevA_Write((mxc_uart_reva_regs_t *)uart, byte, len);
}

unsigned int MXC_UART_ReadRXFIFO(mxc_uart_regs_t *uart, unsigned char *bytes, unsigned int len)
{
    return MXC_UART_RevA_ReadRXFIFO((mxc_uart_reva_regs_t *)uart, bytes, len);
}

int MXC_UART_ReadRXFIFODMA(mxc_uart_regs_t *uart, mxc_dma_regs_t *dma, unsigned char *bytes,
                           unsigned int len, mxc_uart_dma_complete_cb_t callback)
{
    mxc_dma_config_t config;

    if (MXC_DMA_GET_IDX(dma) == -1) {
        return E_BAD_PARAM;
    }

    int uart_num = MXC_UART_GET_IDX(uart);
    switch (uart_num) {
    case 0:
        config.reqsel = MXC_DMA_REQUEST_UART0RX;
        break;

    case 1:
        config.reqsel = MXC_DMA_REQUEST_UART1RX;
        break;

    case 2:
        config.reqsel = MXC_DMA_REQUEST_UART2RX;
        break;

    default:
        return E_BAD_PARAM;
        break;
    }

    return MXC_UART_RevA_ReadRXFIFODMA((mxc_uart_reva_regs_t *)uart, dma, bytes, len, callback,
                                       config);
}

unsigned int MXC_UART_GetRXFIFOAvailable(mxc_uart_regs_t *uart)
{
    return MXC_UART_RevA_GetRXFIFOAvailable((mxc_uart_reva_regs_t *)uart);
}

unsigned int MXC_UART_WriteTXFIFO(mxc_uart_regs_t *uart, unsigned char *bytes, unsigned int len)
{
    return MXC_UART_RevA_WriteTXFIFO((mxc_uart_reva_regs_t *)uart, bytes, len);
}

int MXC_UART_WriteTXFIFODMA(mxc_uart_regs_t *uart, mxc_dma_regs_t *dma, unsigned char *bytes,
                            unsigned int len, mxc_uart_dma_complete_cb_t callback)
{
    mxc_dma_config_t config;

    if (MXC_DMA_GET_IDX(dma) == -1) {
        return E_BAD_PARAM;
    }

    int uart_num = MXC_UART_GET_IDX(uart);
    switch (uart_num) {
    case 0:
        config.reqsel = MXC_DMA_REQUEST_UART0TX;
        break;

    case 1:
        config.reqsel = MXC_DMA_REQUEST_UART1TX;
        break;

    case 2:
        config.reqsel = MXC_DMA_REQUEST_UART2TX;
        break;

    default:
        return E_BAD_PARAM;
        break;
    }

    return MXC_UART_RevA_WriteTXFIFODMA((mxc_uart_reva_regs_t *)uart, dma, bytes, len, callback,
                                        config);
}

unsigned int MXC_UART_GetTXFIFOAvailable(mxc_uart_regs_t *uart)
{
    return MXC_UART_RevA_GetTXFIFOAvailable((mxc_uart_reva_regs_t *)uart);
}

void MXC_UART_ClearRXFIFO(mxc_uart_regs_t *uart)
{
    MXC_UART_RevA_ClearRXFIFO((mxc_uart_reva_regs_t *)uart);
}

void MXC_UART_ClearTXFIFO(mxc_uart_regs_t *uart)
{
    MXC_UART_RevA_ClearTXFIFO((mxc_uart_reva_regs_t *)uart);
}

int MXC_UART_SetRXThreshold(mxc_uart_regs_t *uart, unsigned int numBytes)
{
    return MXC_UART_RevA_SetRXThreshold((mxc_uart_reva_regs_t *)uart, numBytes);
}

unsigned int MXC_UART_GetRXThreshold(mxc_uart_regs_t *uart)
{
    return MXC_UART_RevA_GetRXThreshold((mxc_uart_reva_regs_t *)uart);
}

int MXC_UART_SetTXThreshold(mxc_uart_regs_t *uart, unsigned int numBytes)
{
    return MXC_UART_RevA_SetTXThreshold((mxc_uart_reva_regs_t *)uart, numBytes);
}

unsigned int MXC_UART_GetTXThreshold(mxc_uart_regs_t *uart)
{
    return MXC_UART_RevA_GetTXThreshold((mxc_uart_reva_regs_t *)uart);
}

unsigned int MXC_UART_GetFlags(mxc_uart_regs_t *uart)
{
    return MXC_UART_RevA_GetFlags((mxc_uart_reva_regs_t *)uart);
}

void MXC_UART_ClearFlags(mxc_uart_regs_t *uart, unsigned int flags)
{
    MXC_UART_RevA_ClearFlags((mxc_uart_reva_regs_t *)uart, flags);
}

void MXC_UART_EnableInt(mxc_uart_regs_t *uart, unsigned int intEn)
{
    MXC_UART_RevA_EnableInt((mxc_uart_reva_regs_t *)uart, intEn);
}

void MXC_UART_DisableInt(mxc_uart_regs_t *uart, unsigned int intDis)
{
    MXC_UART_RevA_DisableInt((mxc_uart_reva_regs_t *)uart, intDis);
}

unsigned int MXC_UART_GetStatus(mxc_uart_regs_t *uart)
{
    return MXC_UART_RevA_GetStatus((mxc_uart_reva_regs_t *)uart);
}

int MXC_UART_Transaction(mxc_uart_req_t *req)
{
    return MXC_UART_RevA_Transaction((mxc_uart_reva_req_t *)req);
}

int MXC_UART_TransactionAsync(mxc_uart_req_t *req)
{
    return MXC_UART_RevA_TransactionAsync((mxc_uart_reva_req_t *)req);
}

int MXC_UART_TransactionDMA(mxc_uart_req_t *req, mxc_dma_regs_t *dma)
{
    if (MXC_DMA_GET_IDX(dma) == -1) {
        return E_BAD_PARAM;
    }

    return MXC_UART_RevA_TransactionDMA((mxc_uart_reva_req_t *)req, dma);
}

void MXC_UART_AbortAsync(mxc_uart_regs_t *uart)
{
    MXC_UART_RevA_AbortAsync((mxc_uart_reva_regs_t *)uart);
}

void MXC_UART_TxAbortAsync(mxc_uart_regs_t *uart)
{
    MXC_UART_RevA_TxAbortAsync((mxc_uart_reva_regs_t *)uart);
}

void MXC_UART_RxAbortAsync(mxc_uart_regs_t *uart)
{
    MXC_UART_RevA_RxAbortAsync((mxc_uart_reva_regs_t *)uart);
}

void MXC_UART_AsyncHandler(mxc_uart_regs_t *uart)
{
    MXC_UART_RevA_AsyncHandler((mxc_uart_reva_regs_t *)uart);
}

uint32_t MXC_UART_GetAsyncTXCount(mxc_uart_req_t *req)
{
    return req->txCnt;
}

uint32_t MXC_UART_GetAsyncRXCount(mxc_uart_req_t *req)
{
    return req->rxCnt;
}
