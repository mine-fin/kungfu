//
// Created by Keren Dong on 2019-05-16.
//

#ifndef KUNGFU_PASSIVE_H
#define KUNGFU_PASSIVE_H

#include <spdlog/spdlog.h>
#include <nn.hpp>
#include <nanomsg/pipeline.h>
#include <nanomsg/pubsub.h>

#include <kungfu/yijinjing/comman.h>
#include <kungfu/yijinjing/nanomsg/socket.h>

YJJ_NAMESPACE_START

namespace passive
{
    #define MAC_MSG_LENGTH 256 * 1024
    #define DEFAULT_NOTICE_TIMEOUT 1000

    class nn_socket_holder {
    protected:
        nn_socket_holder(int protocol, std::string url);
        nanomsg::socket socket_;
    };

    class emitter: nn_socket_holder {
    public:
        emitter(): nn_socket_holder(NN_PUSH, KFS_EMITTER_URL) {}
        void poke();
        void emit(const std::string& msg);
    private:
        std::string default_msg_ = "{}";
    };

    class notice: nn_socket_holder {
    public:
        notice(): notice(DEFAULT_NOTICE_TIMEOUT) {}
        notice(int timeout);
        bool wait();
        const std::string& last_message();
    private:
        int timeout_;
        char buf_[MAC_MSG_LENGTH];
        std::string message_;
    };
}

YJJ_NAMESPACE_END

#endif //KUNGFU_PASSIVE_H
