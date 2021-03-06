// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#include <ReactWindowsCore/BatchingMessageQueueThread.h>
#include <winrt/Windows.UI.Core.h>

namespace react {
namespace uwp {

// Executes the function on the provided UI Dispatcher
class BatchingUIMessageQueueThread : public facebook::react::BatchingMessageQueueThread {
 public:
  BatchingUIMessageQueueThread() = delete;
  BatchingUIMessageQueueThread(const BatchingUIMessageQueueThread &other) = delete;

  BatchingUIMessageQueueThread(winrt::Windows::UI::Core::CoreDispatcher dispatcher);
  virtual ~BatchingUIMessageQueueThread();

  virtual void runOnQueue(std::function<void()> &&func);
  virtual void runOnQueueSync(std::function<void()> &&func);
  virtual void quitSynchronous();

  void onBatchComplete() override;

 private:
  void ensureQueue();
  void threadCheck();

 private:
  winrt::Windows::UI::Core::CoreDispatcher m_uiDispatcher{nullptr};

  typedef std::vector<std::function<void()>> WorkItemQueue;
  std::shared_ptr<WorkItemQueue> m_queue;

#if DEBUG
  DWORD m_expectedThreadId = 0;
#endif
};

} // namespace uwp
} // namespace react
