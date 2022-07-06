#include "hlRenderer.hpp"

#include "hlPipeline.hpp"

namespace Helios {
    
void HlRenderer::createCommandBuffers() {
  m_CommandBuffers.resize(m_CommandBuffersCount);

  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = m_Device.getCommandPool();
  allocInfo.commandBufferCount = static_cast<uint32_t>(m_CommandBuffers.size());

  if (vkAllocateCommandBuffers(m_Device.device(), &allocInfo, m_CommandBuffers.data()) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to allocate command buffers!");
  }
}

void HlRenderer::freeCommandBuffers() {
  vkFreeCommandBuffers(
      m_Device.device(),
      m_Device.getCommandPool(),
      static_cast<uint32_t>(m_CommandBuffers.size()),
      m_CommandBuffers.data());
  m_CommandBuffers.clear();
}

VkCommandBuffer HlRenderer::beginFrame() {
  assert(!m_IsFrameStarted && "Can't call beginFrame while already in progress");

  auto result = m_SwapChain->acquireNextImage(&m_CurrentImageIndex);
  if (result == VK_ERROR_OUT_OF_DATE_KHR) {
    recreateSwapChain();
    return nullptr;
  }

  if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
    throw std::runtime_error("failed to acquire swap chain image!");
  }

  m_IsFrameStarted = true;

  auto commandBuffer = getCurrentCommandBuffer();
  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = 0;
  beginInfo.pInheritanceInfo = nullptr;

  if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
    throw std::runtime_error("failed to begin recording command buffer!");
  }
  return commandBuffer;
}

void HlRenderer::endFrame() {
  assert(m_IsFrameStarted && "Can't call endFrame while frame is not in progress");
  auto commandBuffer = getCurrentCommandBuffer();
  if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
    throw std::runtime_error("failed to record command buffer!");
  }

  auto result = m_SwapChain->submitCommandBuffers(&commandBuffer, &m_CurrentImageIndex);
  if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_Window.wasWindowResized()) {
    m_Window.resetWindowResizedFlag();
    recreateSwapChain();
  } 
  else if (result != VK_SUCCESS) {
    throw std::runtime_error("failed to present swap chain image!");
  }

  m_IsFrameStarted = false;
  m_CurrentFrameIndex = (m_CurrentFrameIndex + 1) % HlSwapChain::MAX_FRAMES_IN_FLIGHT;
}

void HlRenderer::beginSwapChainRenderPass(VkCommandBuffer commandBuffer) {
  assert(m_IsFrameStarted && "Can't call beginSwapChainRenderPass if frame is not in progress");
  assert(
      commandBuffer == getCurrentCommandBuffer() &&
      "Can't begin render pass on command buffer from a different frame");

  VkRenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = m_SwapChain->getRenderPass();
  renderPassInfo.framebuffer = m_SwapChain->getFrameBuffer(m_CurrentImageIndex);

  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = m_SwapChain->getSwapChainExtent();

  std::array<VkClearValue, 2> clearValues{};
  clearValues[0].color = {0.01f, 0.01f, 0.01f, 1.0f};
  clearValues[1].depthStencil = {1.0f, 0};
  renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
  renderPassInfo.pClearValues = clearValues.data();

  vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = static_cast<float>(m_SwapChain->getSwapChainExtent().width);
  viewport.height = static_cast<float>(m_SwapChain->getSwapChainExtent().height);
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  VkRect2D scissor{{0, 0}, m_SwapChain->getSwapChainExtent()};
  vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
  vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}

void HlRenderer::endSwapChainRenderPass(VkCommandBuffer commandBuffer) {
  assert(m_IsFrameStarted && "Can't call endSwapChainRenderPass if frame is not in progress");
  assert(
      commandBuffer == getCurrentCommandBuffer() &&
      "Can't end render pass on command buffer from a different frame");
  vkCmdEndRenderPass(commandBuffer);
}

}