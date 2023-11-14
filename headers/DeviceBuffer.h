#include <utility>

#include "Tools.h"
#include "ClContextHelper.h"

#ifndef RC4GPU_SRC_DEVICEBUFFER_H_
#define RC4GPU_SRC_DEVICEBUFFER_H_
namespace clExtendedApi {
    template<typename T>
    class DeviceBuffer {
      private:
        cl::Buffer d_buffer_;
        size_t elements_count_ = 0;
        size_t size_ = 0;
        cl_mem_flags cl_mem_flags_;

        ClContextHelper *const context_helper_;

      public:
        DeviceBuffer(ClContextHelper *context_helper, cl_mem_flags cl_mem_flag)
            : context_helper_(context_helper) {
            cl_mem_flags_ = cl_mem_flag;
        }

        DeviceBuffer(ClContextHelper *context_helper, cl_mem_flags cl_mem_flag, size_t elements_count)
            : context_helper_(context_helper) {
            cl_mem_flags_ = cl_mem_flag;
            Resize(elements_count);
        }

        [[nodiscard]] const cl::Buffer &GetBuffer() const {
            return d_buffer_;
        }

        void Resize(size_t req_elements_count) {
            if (elements_count_ == req_elements_count && d_buffer_() != nullptr) {
                return;
            }

            cl::Buffer new_buffer(context_helper_->GetContext(), cl_mem_flags_, req_elements_count * sizeof(T));

            d_buffer_ = new_buffer;
            elements_count_ = req_elements_count;
            size_ = req_elements_count * sizeof(T);
        }

        void ReadTo(T *host) {
            cl::copy(context_helper_->GetCommandQueue(), d_buffer_, host, host + elements_count_);
        }
        void ReadTo(T &host) {
            cl::copy(context_helper_->GetCommandQueue(), d_buffer_, &host, (&host) + elements_count_);
        }

        void WriteFrom(const T *host) {
            cl::copy(context_helper_->GetCommandQueue(), host, host + elements_count_, d_buffer_);
        }

        void WriteFrom(const T &host) {
            cl::copy(context_helper_->GetCommandQueue(), &host, (&host) + elements_count_, d_buffer_);
        }

        void MemSetZeros() {
            unsigned char pattern = 0;
            context_helper_->GetCommandQueue().enqueueFillBuffer(d_buffer_, pattern, 0, size_, nullptr, nullptr);
        }

        ~DeviceBuffer() = default;
    };
}

#endif //RC4GPU_SRC_DEVICEBUFFER_H_
