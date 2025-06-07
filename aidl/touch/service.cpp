/*
 * SPDX-FileCopyrightText: 2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "vendor.lineage.touch-service.oplus"

#include "HighTouchPollingRate.h"
#include "KeyDisabler.h"
#include "KeySwapper.h"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

using aidl::vendor::lineage::touch::HighTouchPollingRate;
using aidl::vendor::lineage::touch::KeyDisabler;
using aidl::vendor::lineage::touch::KeySwapper;

int main() {
    binder_status_t status = STATUS_OK;

    ABinderProcess_setThreadPoolMaxThreadCount(0);

#if ENABLE_HTPR
    std::shared_ptr<HighTouchPollingRate> htpr = ndk::SharedRefBase::make<HighTouchPollingRate>();
    const std::string htpr_instance = std::string(HighTouchPollingRate::descriptor) + "/default";
    status = AServiceManager_addService(htpr->asBinder().get(), htpr_instance.c_str());
    if (status != STATUS_OK) {
        LOG(WARNING) << "Can't register IHighTouchPollingRate/default";
    }
#endif

#if ENABLE_KD
    std::shared_ptr<KeyDisabler> kd = ndk::SharedRefBase::make<KeyDisabler>();
    const std::string kd_instance = std::string(KeyDisabler::descriptor) + "/default";
    status = AServiceManager_addService(kd->asBinder().get(), kd_instance.c_str());
    if (status != STATUS_OK) {
        LOG(WARNING) << "Can't register IKeyDisabler/default";
    }
#endif

#if ENABLE_KS
    std::shared_ptr<KeySwapper> ks = ndk::SharedRefBase::make<KeySwapper>();
    const std::string ks_instance = std::string(KeySwapper::descriptor) + "/default";
    status = AServiceManager_addService(ks->asBinder().get(), ks_instance.c_str());
    if (status != STATUS_OK) {
        LOG(WARNING) << "Can't register IKeySwapper/default";
    }
#endif

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reach
}
