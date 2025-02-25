#pragma once

#ifdef RCT_NEW_ARCH_ENABLED
#include <react/fabric/JFabricUIManager.h>
#include <react/jni/JRuntimeExecutor.h>
#include <react/renderer/scheduler/Scheduler.h>
#endif // RCT_NEW_ARCH_ENABLED

#include <ReactCommon/CallInvokerHolder.h>
#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <react/jni/CxxModuleWrapper.h>
#include <react/jni/JMessageQueueThread.h>
#include <react/jni/WritableNativeMap.h>

#include <worklets/NativeModules/WorkletsModuleProxy.h>

#include <memory>
#include <string>

namespace worklets {

using namespace facebook;
using namespace facebook::jni;

class WorkletsModule : public jni::HybridClass<WorkletsModule> {
 public:
  static auto constexpr kJavaDescriptor =
      "Lcom/swmansion/worklets/WorkletsModule;";

  static jni::local_ref<jhybriddata> initHybrid(
      jni::alias_ref<jhybridobject> jThis,
      jlong jsContext,
      const std::string &valueUnpackerCode,
      jni::alias_ref<JavaMessageQueueThread::javaobject> messageQueueThread);

  static void registerNatives();

  inline std::shared_ptr<WorkletsModuleProxy> getWorkletsModuleProxy() {
    return workletsModuleProxy_;
  }

 private:
  friend HybridBase;
  jni::global_ref<WorkletsModule::javaobject> javaPart_;
  jsi::Runtime *rnRuntime_;
  std::shared_ptr<WorkletsModuleProxy> workletsModuleProxy_;

  explicit WorkletsModule(
      jni::alias_ref<WorkletsModule::jhybridobject> jThis,
      jsi::Runtime *rnRuntime,
      const std::string &valueUnpackerCode,
      jni::alias_ref<JavaMessageQueueThread::javaobject> messageQueueThread);
};

} // namespace worklets
