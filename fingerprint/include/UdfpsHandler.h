/*
 * Copyright (C) 2022 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>
#include "fingerprint.h"

typedef enum udfpshandler_msg_type {
    UDFPSHANDLER_MSG_FINGER_DOWN,
    UDFPSHANDLER_MSG_FINGER_UP,
    UDFPSHANDLER_MSG_ACQUIRED,
    UDFPSHANDLER_MSG_CANCEL,
} udfpshandler_msg_type_t;

typedef struct udfpshandler_finger_down_msg {
    uint32_t x;
    uint32_t y;
    float minor;
    float major;
} udfpshandler_finger_down_msg_t;

typedef struct udfpshandler_acquired_msg {
    int32_t result;
    int32_t vendor;
} udfpshandler_acquired_msg_t;

typedef struct udfpshandler_msg {
    udfpshandler_msg_type_t type;
    union {
        udfpshandler_finger_down_msg finger_down_msg;
        udfpshandler_acquired_msg acquired_msg;
    } data;
} udfpshandler_msg_t;

class UdfpsHandler {
  public:
    virtual ~UdfpsHandler() = default;

    virtual void init(fingerprint_device_t* device) = 0;
    virtual void notify(udfpshandler_msg_t msg) = 0;
};

struct UdfpsHandlerFactory {
    UdfpsHandler* (*create)();
    void (*destroy)(UdfpsHandler* handler);
};

UdfpsHandlerFactory* getUdfpsHandlerFactory();
